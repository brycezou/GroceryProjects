#include <opencv2/opencv.hpp>
#include <NuiApi.h>
#include <iostream>

using namespace std;
using namespace cv;


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