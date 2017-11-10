#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <NuiApi.h>

using namespace std;
using namespace cv;


//����ԭʼ������ݵ�����
int *gDepthArray = NULL;
bool gbExit = false;


//��ʼ��Kinect
bool InitializeKinect(HANDLE &depthEvent, HANDLE &depthStreamHandle, HANDLE &colorEvent, HANDLE &colorStreamHandle)
{
	//����NUI��ʼ��������ָ������ʹ�õ��������ݣ���ID��ȣ�
	HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_COLOR);   
	if( hr != S_OK )   
	{   
		cout<<"NuiInitialize failed"<<endl; 
		return false; 
	}

	//NuiImageStreamOpen ���ڴ�Kinect�������� 
	//���������ͣ�ͼ��ֱ��ʣ�NULL�������Ļ�����������Ϊ4������Kinect�Ƿ���Զ�ȡ��һ֡�ľ�����������ݵľ��
	hr = NuiImageStreamOpen(	NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, 
		NUI_IMAGE_RESOLUTION_640x480, NULL, 2, 
		depthEvent, &depthStreamHandle); 
	if( hr != S_OK )   
	{   
		cout<<"Open depth Stream failed"<<endl; 
		NuiShutdown(); 
		return false; 
	}

	// �򿪲�ɫ������
	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 
		NULL, 4, colorEvent, &colorStreamHandle); 
	if( hr != S_OK )   
	{
		cout<<"Open color Stream failed"<<endl; 
		NuiShutdown(); 
		return false; 
	} 

	//����KinectΪ����ģʽ
	hr = NuiImageStreamSetImageFrameFlags(depthStreamHandle, NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE); 
	if( hr != S_OK )   
	{   
		cout<<"Open near mode failed"<<endl; 
		NuiShutdown(); 
		return false;   
	}

	return true;
}

//��Kinect��ȡ������ID�����ͼ��
bool getDepthImage(HANDLE &depthEvent, HANDLE &depthStreamHandle, Mat &depthMat) 
{ 
	//���ͼ��֡
	const NUI_IMAGE_FRAME *depthFrame = NULL;
	//���Դ��������������еõ�����
	HRESULT hr = NuiImageStreamGetNextFrame(depthStreamHandle, 0, &depthFrame); 
	if (FAILED(hr))
	{
		cout<<"NuiImageStreamGetNextFrame failed once"<<endl;
		return false;
	}

	//INuiFrameTexture�ӿڣ�����ͼ�����ݵĶ���
	INuiFrameTexture *depthTexture = depthFrame->pFrameTexture;   
	//��ȡ����֡��depthLockedRect������������
	NUI_LOCKED_RECT depthLockedRect; 
	depthTexture->LockRect(0, &depthLockedRect, NULL, 0);   

	//LochedRect����������Kinect���ݵĶ���pitchΪÿ���ֽ�����pBitsΪ��һ���ֽڵ�ַ
	if(depthLockedRect.Pitch != 0) 
	{ 
		for(int i = 0; i < depthMat.rows; i++) 
		{ 
			//��i�е�ָ�룬һ���ֽ�uchar����һ����ɫ��Ϣ
			uchar *depthhead = depthMat.ptr<uchar>(i); 
			uchar *depthBuffer = (uchar*)(depthLockedRect.pBits) + i * depthLockedRect.Pitch;
			//��ID�����ͼ��ÿ�����������ֽ�16λ��ʾ����3λ������ID����13λ�Ǿ�����Ϣ
			USHORT *depthBufferRun = (USHORT*) depthBuffer; 
			for (int j = 0; j < depthMat.cols; j++) 
			{ 
				int personID = depthBufferRun[j]&7;						//��ȡ��3λ����ID
				int depthData = (depthBufferRun[j]&0xfff8) >> 3; //��ȡ��13λ������Ϣ

				gDepthArray[i*depthMat.cols+j] = depthData;		//����ԭʼ���ͼ��
				uchar zData = /*255-*/(uchar)(256*depthData/0x0fff);		//������Ϊ0-255
				depthhead[j] = zData; 
			} 
		} 
	} 
	else 
		cout << "Get depth data failed" << endl; 

	//��֡�����Ѵ�����ʽ���
	depthTexture->UnlockRect(0); 
	//�ͷű�֡���ݣ�׼��ӭ����һ֡
	NuiImageStreamReleaseFrame(depthStreamHandle, depthFrame);  
	return true;
} 

//��Kinect��ȡ��ɫͼ��
bool getColorImage(HANDLE &colorEvent, HANDLE &colorStreamHandle, Mat &colorMat) 
{ 
	//��ɫͼ��֡
	const NUI_IMAGE_FRAME *colorFrame = NULL;
	//���ԴӲ�ɫ����������еõ�����
	HRESULT hr = NuiImageStreamGetNextFrame(colorStreamHandle, 0, &colorFrame);
	if (FAILED(hr))
	{
		cout<<"NuiImageStreamGetNextFrame failed once"<<endl;
		return false;
	}
	// INuiFrameTexture�ӿڣ�����ͼ�����ݵĶ���
	INuiFrameTexture *colorTexture = colorFrame->pFrameTexture;   

	// ��ȡ����֡��colorLockedRect������������
	NUI_LOCKED_RECT colorLockedRect; 
	colorTexture->LockRect(0, &colorLockedRect, NULL, 0);   

	// ���ˣ�LochedRect����������Kinect���ݵĶ���pitchΪÿ���ֽ�����pBitsΪ��һ���ֽڵ�ַ
	if(colorLockedRect.Pitch != 0) 
	{ 
		for (int i=0; i<colorMat.rows; i++) 
		{
			//��i�е�ָ�룬һ���ֽ�uchar����һ����ɫ��Ϣ
			uchar *colorhead = colorMat.ptr<uchar>(i);
			uchar *colorBuffer = (uchar*)(colorLockedRect.pBits) + i * colorLockedRect.Pitch;
			for (int j=0; j<colorMat.cols; j++) 
			{ 
				// Kinect�ڲ�������4���ֽڣ�0-1-2��BGR����4������δʹ��
				colorhead[3*j] = colorBuffer[4*j];   
				colorhead[3*j+1] = colorBuffer[4*j+1]; 
				colorhead[3*j+2] = colorBuffer[4*j+2]; 
			} 
		} 
	} 
	else 
		cout<<"Get color data failed"<<endl; 

	//��֡�����Ѵ�����ʽ���
	colorTexture->UnlockRect(0); 
	//�ͷű�֡���ݣ�׼��ӭ����һ֡
	NuiImageStreamReleaseFrame(colorStreamHandle, colorFrame);
	return true;
} 


DWORD WINAPI handleThread(LPVOID lpParam)
{
	gbExit = false;
	//����ʹ�����ȡ��һ֡���ź��¼����������KINECT�Ƿ���Կ�ʼ��ȡ��һ֡�������
	HANDLE depthEvent = CreateEvent( NULL, TRUE, FALSE, NULL ); 
	//����ʹ�����ȡ��һ֡���ź��¼����������KINECT�Ƿ���Կ�ʼ��ȡ��һ֡��ɫ����
	HANDLE colorEvent = CreateEvent( NULL, TRUE, FALSE, NULL ); 
	//�������ͼ���������ľ����������ȡ����
	HANDLE depthStreamHandle = NULL; 
	//�����ɫͼ���������ľ����������ȡ����
	HANDLE colorStreamHandle = NULL; 
	if(!InitializeKinect(depthEvent, depthStreamHandle, colorEvent, colorStreamHandle))
	{
		gbExit = true;
		return -1;
	}

	//��ʼ��ԭʼ���ͼ������
	gDepthArray = new int[640*480];
	//����ͳ�ʼ�����ͼ��
	Mat depthMat(480, 640, CV_8UC1);
	IplImage *depthIpl = cvCreateImage(cvSize(640, 480), 8, 1); 
	//����ͳ�ʼ����ɫͼ��
	Mat colorMat(480, 640, CV_8UC3);
	IplImage *colorIpl = cvCreateImage(cvSize(640, 480), 8, 3); 
	bool bSaveVideo = false;
	bool bFinished = false;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	char strDepthName[] = "depth.avi";
	char strColorName[] = "color.avi";
	CvVideoWriter* wrVideo_depth = cvCreateVideoWriter(strDepthName, CV_FOURCC('M','J','P','G'), 30, cvSize(640, 480), 0);
	CvVideoWriter* wrVideo_color = cvCreateVideoWriter(strColorName, CV_FOURCC('M','J','P','G'), 30, cvSize(640, 480));
	///////////////////////////////////////////////////////////////////////////////////////////////////

	while(true)
	{ 
		// ���޵ȴ��µ����ݣ��ȵ���WaitForSingleObjectΪ0���򷵻�
		if(WAIT_OBJECT_0 == WaitForSingleObject(depthEvent, INFINITE)) 
		{
			if (WAIT_OBJECT_0 == WaitForSingleObject(colorEvent, INFINITE))
			{
				if(getDepthImage(depthEvent, depthStreamHandle, depthMat))
				{
					if (getColorImage(colorEvent, colorStreamHandle, colorMat))
					{
						depthIpl->imageData = (char *)depthMat.data;
						cvShowImage("depthImage", depthIpl);
						colorIpl->imageData = (char *)colorMat.data;
						cvShowImage("colorImage", colorIpl);
						if (cvWaitKey(1)=='s')
							bSaveVideo = true;
						else if (cvWaitKey(1)=='e')
							bFinished = true;
						if (bSaveVideo)
						{
							cout<<"saving..."<<endl;
							cvWriteFrame(wrVideo_depth, depthIpl);
							cvWriteFrame(wrVideo_color, colorIpl);
						}
						if (bFinished)
						{
							bSaveVideo = false;
							cout<<"finish"<<endl;
							break;
						}
					}
					else
					{
						NuiShutdown(); 
						if(!InitializeKinect(depthEvent, depthStreamHandle, colorEvent, colorStreamHandle))
						{
							cvReleaseVideoWriter(&wrVideo_color);
							cvReleaseVideoWriter(&wrVideo_depth);
							cvReleaseImage(&colorIpl);
							cvReleaseImage(&depthIpl);
							delete []gDepthArray;
							gbExit = true;
							return -1;
						}
					}
				}
				else
				{
					NuiShutdown(); 
					if(!InitializeKinect(depthEvent, depthStreamHandle, colorEvent, colorStreamHandle))
					{
						cvReleaseVideoWriter(&wrVideo_color);
						cvReleaseVideoWriter(&wrVideo_depth);
						cvReleaseImage(&colorIpl);
						cvReleaseImage(&depthIpl);
						delete []gDepthArray;
						gbExit = true;
						return -1;
					}
				}
			}
		}

		if(cvWaitKey(1) == 27) 
			break; 
	} 

	cvReleaseVideoWriter(&wrVideo_color);
	cvReleaseVideoWriter(&wrVideo_depth);
	cvReleaseImage(&colorIpl);
	cvReleaseImage(&depthIpl);
	delete []gDepthArray;
	NuiShutdown(); 
	gbExit = true;
	return 0;
}


int main(int argc, char *argv[])
{
	HANDLE handle = CreateThread(NULL, 0, handleThread, NULL, 0, 0);
	if(!handle)
		cout<<"Creating handleThread failed!"<<endl;

	while (!gbExit)
		Sleep(100);

	return 0; 
}