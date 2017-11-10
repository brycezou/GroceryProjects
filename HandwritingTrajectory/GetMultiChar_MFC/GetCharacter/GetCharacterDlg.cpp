
// GetCharacterDlg.cpp : 实现文件
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


// CGetCharacterDlg 对话框

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


// CGetCharacterDlg 消息处理程序

CGetCharacterDlg *pDlg;

BOOL CGetCharacterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	pDlg=this;
	this->m_strImageName="IMG_name";
	this->m_strTxtFileName="TXT_name";
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	this->UpdateData(FALSE);
	OnOpenRecvSocket(51113);	//打开服务器，监听51113端口

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetCharacterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetCharacterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


typedef struct CIntPoint
{
	int x;
	int y;
}CIntPoint;		//整型数据点结构体
 UINT *pOneDrawLength=NULL;				//存储每一笔所经过的点的数目
 int gUintDrawTimes=0;									//存储文字的总笔画数目
 CPtrArray gPointList;									//存储每一笔所经过的点的坐标
Mat gImage;													//存储待保存的图像
bool isCreatedProcess=false;

#define RECV_BUFFER_SIZE		1023			//因为是多字节语言集, 所以一定要为3的倍数


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
		for (UINT j=0; j<length-2; j++)						//第 i 笔上的第 j 个点
		{
			line(image, cvPoint(pCIp[j].x, pCIp[j].y), cvPoint(pCIp[j+1].x, pCIp[j+1].y), cvScalar(255, 0, 255), 6); 
		}
	}
}

char RecvBuffer[RECV_BUFFER_SIZE];			//数据接收缓冲区
DWORD WINAPI OnRecvData(LPVOID lpParam)
{
	isCreatedProcess=true;
	SOCKET sockRecv=(int)lpParam;

	CString strRecvdChars="";									//存储接收到的数据
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

	json_value *val=json_parse(strRecvdChars);		//对接收到的数据进行Json解析
	if(val->type!=json_object)
	{
		AfxMessageBox("非法的Json对象!");
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
		gPointList.RemoveAll();																//清除链表，为存储新数据准备
		int minX=50000, minY=50000, maxX=-1, maxY=-1;						//初始化图像文件的边界位置

		gUintDrawTimes = val->u.object.length;										//得到文字的总笔画数目
		pOneDrawLength = new UINT[gUintDrawTimes];						//创建一个数组来存储每一笔所经过的点的数目

		for(int i=0; i<gUintDrawTimes; i++)											//add data to list and find the boundary of the character
		{
			UINT length=val->u.object.values[i].value->u.array.length;		//获取第 i 笔所经过的点的数目
			pOneDrawLength[i]=length;
			CIntPoint *pIntPoint=new CIntPoint[length];							//创建数组来存储每一笔所经过的点的坐标
			for(UINT j=0; j<length; j++)													//add data to list and find the boundary of the character
			{
				int intX=atoi(val->u.object.values[i].value->u.array.values[j]->u.object.values[0].name);			//X坐标
				int intY=val->u.object.values[i].value->u.array.values[j]->u.object.values[0].value->u.integer;	//Y坐标
				pIntPoint[j].x=intX;
				pIntPoint[j].y=intY;															//设置第 i 笔的第 j 个点的坐标

				if (intX<minX)	minX=intX;
				if (intY<minY)	minY=intY;
				if (intX>maxX)	maxX=intX;
				if (intY>maxY)	maxY=intY;												//find the boundary
			}
			gPointList.Add(pIntPoint);														//存储第 i 笔所经过的点的所有坐标
		}

		CIntPoint *pCIp;
		for(int i=0; i<gUintDrawTimes; i++)											//add the normalized data to the new list
		{
			UINT length=pOneDrawLength[i];
			pCIp=(CIntPoint*)gPointList.GetAt(i);
			for (UINT j=0; j<length; j++)
			{
				pCIp[j].x=pCIp[j].x-minX;													//剔除有效图像范围以外的点
				pCIp[j].y=pCIp[j].y-minY;
			}
		}

		gImage.create(maxY-minY+1, maxX-minX+1, CV_8UC3); 
		cvMySetMatEmpty(gImage);
		drawTrajectory(gImage, gUintDrawTimes);								//根据点数据绘制文字图像
		IplImage ipl_image=gImage;

		cvReleaseImage(&pDlg->dstImage);
		pDlg->dstImage=cvCreateImage(cvSize(256, 256), (&ipl_image)->depth, (&ipl_image)->nChannels);	//构造缩小后的目标图象
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

//打开服务器，监听51113端口
bool CGetCharacterDlg::OnOpenRecvSocket(int recvport)
{
	WSADATA wsadata;
	SOCKET sockRecv;
	if(WSAStartup(MAKEWORD(2, 2), &wsadata)!=0)
	{
		AfxMessageBox(_T("WSAStartup 失败!"));
		return FALSE;
	}
	sockRecv=socket(AF_INET, SOCK_STREAM, 0);
	while(sockRecv==INVALID_SOCKET)
	{
		if(AfxMessageBox(_T("SockRecv 初始化失败!\n重试?"), MB_YESNO)==IDNO)
			return false;
	}

	sockaddr_in sin;
	sin.sin_port=htons(recvport);
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=0;
	while(bind(sockRecv, (sockaddr*)&sin, sizeof(sockaddr))==SOCKET_ERROR)
	{
		if(AfxMessageBox(_T("Bind 失败!\n重试?"), MB_YESNO)==IDNO)
			return false;
	}
	listen(sockRecv, 1);

	HANDLE handle=CreateThread(NULL, 0, OnListingAccept, (void*)sockRecv, 0, 0);
	if(!handle)
		MessageBox(_T("创建 Accept 线程失败!"), 0, 0);

	CloseHandle(handle);

	return true;
}

//将图像img显示在控件ID上
void CGetCharacterDlg::OnShowImage(IplImage* img, UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();   // 获得显示控件的DC
	HDC hdc = pDC->GetSafeHdc(); // 获取 HDC(设备句柄) 来进行绘图操作
	CRect rect;
	GetDlgItem(ID)->GetClientRect( &rect );
	CvvImage cimg;
	cimg.CopyOf( img );                // 复制图片
	cimg.DrawToHDC( hdc, &rect );  // 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
	cimg.Destroy();
}

//保存按钮的触发事件
void CGetCharacterDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	CString strImageName=m_strImageName;			//获取图像文件名
	CString strTxtFileName=m_strTxtFileName;		//获取文本文件名
	if (strImageName.IsEmpty() || strTxtFileName.IsEmpty())
	{
		AfxMessageBox("请输入文件名!");
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
		AfxMessageBox("您还未作任何新的输入!");
		return;
	}

	cvSaveImage(pImageName, dstImage);				//保存图像文件
	cvReleaseImage(&dstImage);

	std::ofstream outxt;
	outxt.open(pTxtFileName, std::ios::app);
	outxt<<"# "<<gUintDrawTimes<<'\n';					//先输出总笔画数目

	CIntPoint *pCIp;
	for(int i=0; i<gUintDrawTimes; i++)
	{
		UINT length=pOneDrawLength[i];					//再输出第 i 笔经过的点数
		outxt<<i<<" : "<<length<<"\n";

		pCIp=(CIntPoint*)gPointList.GetAt(i);	
		for (UINT j=0; j<length; j++)
		{
			outxt<<pCIp[j].x<<" "<<pCIp[j].y<<"  ";		//输出第 i 笔的第 j 个点的坐标
		}
		outxt<<"\n\n";
	}
	outxt<<"\n\n\n\n";

	outxt.close();

	AfxMessageBox("保存成功!");
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
}
