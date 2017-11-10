
// GetCharacterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetCharacter.h"
#include "GetCharacterDlg.h"
#include "afxdialogex.h"
#include "json.h"
#include <fstream>
#include "CvvImage.h"
#include "opencv2/opencv.hpp"

using namespace cv;



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGetCharacterDlg �Ի���

CGetCharacterDlg::CGetCharacterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetCharacterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strImageName = _T("");
	m_strTxtFileName = _T("");
	dstImage = NULL;
}

void CGetCharacterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IMAGE_NAME, m_strImageName);
	DDX_Text(pDX, IDC_EDIT_SEQUENCE_FILE_NAME, m_strTxtFileName);
}

BEGIN_MESSAGE_MAP(CGetCharacterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CGetCharacterDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CGetCharacterDlg ��Ϣ�������

CGetCharacterDlg *pDlg;

BOOL CGetCharacterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	pDlg=this;
	this->m_strImageName="IMG_name";
	this->m_strTxtFileName="TXT_name";
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	this->UpdateData(FALSE);
	OnOpenRecvSocket(51113);	//�򿪷�����������51113�˿�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGetCharacterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGetCharacterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


typedef struct CIntPoint
{
	int x;
	int y;
}CIntPoint;		//�������ݵ�ṹ��
 UINT *pOneDrawLength=NULL;				//�洢ÿһ���������ĵ����Ŀ
 int gUintDrawTimes=0;									//�洢���ֵ��ܱʻ���Ŀ
 CPtrArray gPointList;									//�洢ÿһ���������ĵ������
Mat gImage;													//�洢�������ͼ��
bool isCreatedProcess=false;

#define RECV_BUFFER_SIZE		1023			//��Ϊ�Ƕ��ֽ����Լ�, ����һ��ҪΪ3�ı���


//clearn a specified Mat
void cvMySetMatEmpty(Mat &image)
{
	for (int i=0; i<image.rows; i++)
	{
		uchar *depthhead = image.ptr<uchar>(i);//point of the row i , one uchar indicates one color
		for (int j=0; j<image.cols; j++)
		{
			depthhead[3*j] = 0;
			depthhead[3*j+1] = 0;
			depthhead[3*j+2] = 0;
		}
	}
}

//draw the dynamic hand pos trajectory
void drawTrajectory(Mat &image, int gUintDrawTimes)
{
	CIntPoint *pCIp;
	for(int i=0; i<gUintDrawTimes; i++)	
	{
		UINT length=pOneDrawLength[i];
		pCIp=(CIntPoint*)gPointList.GetAt(i);		
		for (UINT j=0; j<length-2; j++)						//�� i ���ϵĵ� j ����
		{
			line(image, cvPoint(pCIp[j].x, pCIp[j].y), cvPoint(pCIp[j+1].x, pCIp[j+1].y), cvScalar(255, 0, 255), 6); 
		}
	}
}

char RecvBuffer[RECV_BUFFER_SIZE];			//���ݽ��ջ�����
DWORD WINAPI OnRecvData(LPVOID lpParam)
{
	isCreatedProcess=true;
	SOCKET sockRecv=(int)lpParam;

	CString strRecvdChars="";									//�洢���յ�������
	int intRecvdLength=-1;
	do 
	{
		memset(RecvBuffer, 0, RECV_BUFFER_SIZE);
		intRecvdLength=recv(sockRecv, RecvBuffer, RECV_BUFFER_SIZE, 0);
		Sleep(20);
		strRecvdChars+=RecvBuffer;
	} while (intRecvdLength==RECV_BUFFER_SIZE);

	//AfxMessageBox(strRecvdChars);
	gUintDrawTimes=0;

	if (strRecvdChars.GetLength()<5)
	{
		pDlg->GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
		isCreatedProcess=false;
		return -1;
	}

	json_value *val=json_parse(strRecvdChars);		//�Խ��յ������ݽ���Json����
	if(val->type!=json_object)
	{
		AfxMessageBox("�Ƿ���Json����!");
		pDlg->GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
		isCreatedProcess=false;
		return -1;
	}
	else
	{
		if (pOneDrawLength)		
		{
			delete []pOneDrawLength;
		}
		gPointList.RemoveAll();																//�������Ϊ�洢������׼��
		int minX=50000, minY=50000, maxX=-1, maxY=-1;						//��ʼ��ͼ���ļ��ı߽�λ��

		gUintDrawTimes = val->u.object.length;										//�õ����ֵ��ܱʻ���Ŀ
		pOneDrawLength = new UINT[gUintDrawTimes];						//����һ���������洢ÿһ���������ĵ����Ŀ

		for(int i=0; i<gUintDrawTimes; i++)											//add data to list and find the boundary of the character
		{
			UINT length=val->u.object.values[i].value->u.array.length;		//��ȡ�� i ���������ĵ����Ŀ
			pOneDrawLength[i]=length;
			CIntPoint *pIntPoint=new CIntPoint[length];							//�����������洢ÿһ���������ĵ������
			for(UINT j=0; j<length; j++)													//add data to list and find the boundary of the character
			{
				int intX=atoi(val->u.object.values[i].value->u.array.values[j]->u.object.values[0].name);			//X����
				int intY=val->u.object.values[i].value->u.array.values[j]->u.object.values[0].value->u.integer;	//Y����
				pIntPoint[j].x=intX;
				pIntPoint[j].y=intY;															//���õ� i �ʵĵ� j ���������

				if (intX<minX)	minX=intX;
				if (intY<minY)	minY=intY;
				if (intX>maxX)	maxX=intX;
				if (intY>maxY)	maxY=intY;												//find the boundary
			}
			gPointList.Add(pIntPoint);														//�洢�� i ���������ĵ����������
		}

		CIntPoint *pCIp;
		for(int i=0; i<gUintDrawTimes; i++)											//add the normalized data to the new list
		{
			UINT length=pOneDrawLength[i];
			pCIp=(CIntPoint*)gPointList.GetAt(i);
			for (UINT j=0; j<length; j++)
			{
				pCIp[j].x=pCIp[j].x-minX;													//�޳���Чͼ��Χ����ĵ�
				pCIp[j].y=pCIp[j].y-minY;
			}
		}

		gImage.create(maxY-minY+1, maxX-minX+1, CV_8UC3); 
		cvMySetMatEmpty(gImage);
		drawTrajectory(gImage, gUintDrawTimes);								//���ݵ����ݻ�������ͼ��
		IplImage ipl_image=gImage;

		cvReleaseImage(&pDlg->dstImage);
		pDlg->dstImage=cvCreateImage(cvSize(256, 256), (&ipl_image)->depth, (&ipl_image)->nChannels);	//������С���Ŀ��ͼ��
		cvResize(&ipl_image, pDlg->dstImage, CV_INTER_LINEAR);
		pDlg->OnShowImage(pDlg->dstImage, IDC_RESULT_IMAGE);
		pDlg->GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);

		gImage.release();
	}

	isCreatedProcess=false;
	return 0;
}

DWORD WINAPI OnListingAccept(LPVOID lpParam)
{
	SOCKET temp, socket;
	socket=(int)lpParam;
	while(true)
	{
		temp=accept(socket, NULL, NULL);
		if (!isCreatedProcess)
		{
			CreateThread(NULL, 0, OnRecvData, (void*)temp, 0, 0);
		}
	}
	return 0;
}

//�򿪷�����������51113�˿�
bool CGetCharacterDlg::OnOpenRecvSocket(int recvport)
{
	WSADATA wsadata;
	SOCKET sockRecv;
	if(WSAStartup(MAKEWORD(2, 2), &wsadata)!=0)
	{
		AfxMessageBox(_T("WSAStartup ʧ��!"));
		return FALSE;
	}
	sockRecv=socket(AF_INET, SOCK_STREAM, 0);
	while(sockRecv==INVALID_SOCKET)
	{
		if(AfxMessageBox(_T("SockRecv ��ʼ��ʧ��!\n����?"), MB_YESNO)==IDNO)
			return false;
	}

	sockaddr_in sin;
	sin.sin_port=htons(recvport);
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=0;
	while(bind(sockRecv, (sockaddr*)&sin, sizeof(sockaddr))==SOCKET_ERROR)
	{
		if(AfxMessageBox(_T("Bind ʧ��!\n����?"), MB_YESNO)==IDNO)
			return false;
	}
	listen(sockRecv, 1);

	HANDLE handle=CreateThread(NULL, 0, OnListingAccept, (void*)sockRecv, 0, 0);
	if(!handle)
		MessageBox(_T("���� Accept �߳�ʧ��!"), 0, 0);

	CloseHandle(handle);

	return true;
}

//��ͼ��img��ʾ�ڿؼ�ID��
void CGetCharacterDlg::OnShowImage(IplImage* img, UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();   // �����ʾ�ؼ���DC
	HDC hdc = pDC->GetSafeHdc(); // ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(ID)->GetClientRect( &rect );
	CvvImage cimg;
	cimg.CopyOf( img );                // ����ͼƬ
	cimg.DrawToHDC( hdc, &rect );  // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC( pDC );
	cimg.Destroy();
}

//���水ť�Ĵ����¼�
void CGetCharacterDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	CString strImageName=m_strImageName;			//��ȡͼ���ļ���
	CString strTxtFileName=m_strTxtFileName;		//��ȡ�ı��ļ���
	if (strImageName.IsEmpty() || strTxtFileName.IsEmpty())
	{
		AfxMessageBox("�������ļ���!");
		return;
	}
	strImageName+=".jpg";
	strTxtFileName+=".txt";
	char *pImageName=new char[strImageName.GetLength()+1];
	char *pTxtFileName=new char[strTxtFileName.GetLength()+1];
	for(int i=0; i<strImageName.GetLength(); i++)
	{
		pImageName[i]=strImageName.GetAt(i);
	}
	pImageName[strImageName.GetLength()]='\0';

	for(int i=0; i<strTxtFileName.GetLength(); i++)
	{
		pTxtFileName[i]=strTxtFileName.GetAt(i);
	}
	pTxtFileName[strTxtFileName.GetLength()]='\0';

	if (gUintDrawTimes==0)
	{
		AfxMessageBox("����δ���κ��µ�����!");
		return;
	}

	cvSaveImage(pImageName, dstImage);				//����ͼ���ļ�
	cvReleaseImage(&dstImage);

	std::ofstream outxt;
	outxt.open(pTxtFileName, std::ios::app);
	outxt<<"# "<<gUintDrawTimes<<'\n';					//������ܱʻ���Ŀ

	CIntPoint *pCIp;
	for(int i=0; i<gUintDrawTimes; i++)
	{
		UINT length=pOneDrawLength[i];					//������� i �ʾ����ĵ���
		outxt<<i<<" : "<<length<<"\n";

		pCIp=(CIntPoint*)gPointList.GetAt(i);	
		for (UINT j=0; j<length; j++)
		{
			outxt<<pCIp[j].x<<" "<<pCIp[j].y<<"  ";		//����� i �ʵĵ� j ���������
		}
		outxt<<"\n\n";
	}
	outxt<<"\n\n\n\n";

	outxt.close();

	AfxMessageBox("����ɹ�!");
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
}
