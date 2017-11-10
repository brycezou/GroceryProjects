#include <opencv2/opencv.hpp>
#include <NuiApi.h>
#include <iostream>

using namespace std;
using namespace cv;


//初始化Kinect
bool InitializeKinect(HANDLE &depthEvent, HANDLE &depthStreamHandle, HANDLE &colorEvent, HANDLE &colorStreamHandle)
{
	//调用NUI初始化函数，指定即将使用的数据内容（带ID深度）
	HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_COLOR);   
	if( hr != S_OK )   
	{   
		cout<<"NuiInitialize failed"<<endl; 
		return false; 
	}

	//NuiImageStreamOpen 用于打开Kinect的数据流 
	//数据流类型，图像分辨率，NULL，建立的缓冲个数，最大为4，控制Kinect是否可以读取下一帧的句柄，保存数据的句柄
	hr = NuiImageStreamOpen(	NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, 
		NUI_IMAGE_RESOLUTION_640x480, NULL, 2, 
		depthEvent, &depthStreamHandle); 
	if( hr != S_OK )   
	{   
		cout<<"Open depth Stream failed"<<endl; 
		NuiShutdown(); 
		return false; 
	}

	// 打开彩色数据流
	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 
		NULL, 4, colorEvent, &colorStreamHandle); 
	if( hr != S_OK )   
	{
		cout<<"Open color Stream failed"<<endl; 
		NuiShutdown(); 
		return false; 
	} 

	//设置Kinect为近景模式
	hr = NuiImageStreamSetImageFrameFlags(depthStreamHandle, NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE); 
	if( hr != S_OK )   
	{   
		cout<<"Open near mode failed"<<endl; 
		NuiShutdown(); 
		return false;   
	}

	return true;
}

//从Kinect获取带人物ID的深度图像
bool getDepthImage(HANDLE &depthEvent, HANDLE &depthStreamHandle, Mat &depthMat) 
{ 
	//深度图像帧
	const NUI_IMAGE_FRAME *depthFrame = NULL;
	//尝试从深度数据流句柄中得到数据
	HRESULT hr = NuiImageStreamGetNextFrame(depthStreamHandle, 0, &depthFrame); 
	if (FAILED(hr))
	{
		cout<<"NuiImageStreamGetNextFrame failed once"<<endl;
		return false;
	}

	//INuiFrameTexture接口，容纳图像数据的对象
	INuiFrameTexture *depthTexture = depthFrame->pFrameTexture;   
	//提取数据帧到depthLockedRect，并锁定数据
	NUI_LOCKED_RECT depthLockedRect; 
	depthTexture->LockRect(0, &depthLockedRect, NULL, 0);   

	//LochedRect是真正保存Kinect数据的对象，pitch为每行字节数，pBits为第一个字节地址
	if(depthLockedRect.Pitch != 0) 
	{ 
		for(int i = 0; i < depthMat.rows; i++) 
		{ 
			//第i行的指针，一个字节uchar代表一个颜色信息
			uchar *depthhead = depthMat.ptr<uchar>(i); 
			uchar *depthBuffer = (uchar*)(depthLockedRect.pBits) + i * depthLockedRect.Pitch;
			//带ID的深度图中每个像素由两字节16位表示，低3位是人物ID，高13位是距离信息
			USHORT *depthBufferRun = (USHORT*) depthBuffer; 
			for (int j = 0; j < depthMat.cols; j++) 
			{ 
				int personID = depthBufferRun[j]&7;						//提取低3位人物ID
				int depthData = (depthBufferRun[j]&0xfff8) >> 3; //提取高13位距离信息
				uchar zData = /*255-*/(uchar)(256*depthData/0x0fff);		//归整化为0-255
				depthhead[j] = zData; 
			} 
		} 
	} 
	else 
		cout << "Get depth data failed" << endl; 

	//本帧数据已处理完故解锁
	depthTexture->UnlockRect(0); 
	//释放本帧数据，准备迎接下一帧
	NuiImageStreamReleaseFrame(depthStreamHandle, depthFrame);  
	return true;
} 

//从Kinect获取彩色图像
bool getColorImage(HANDLE &colorEvent, HANDLE &colorStreamHandle, Mat &colorMat) 
{ 
	//彩色图像帧
	const NUI_IMAGE_FRAME *colorFrame = NULL;
	//尝试从彩色数据流句柄中得到数据
	HRESULT hr = NuiImageStreamGetNextFrame(colorStreamHandle, 0, &colorFrame);
	if (FAILED(hr))
	{
		cout<<"NuiImageStreamGetNextFrame failed once"<<endl;
		return false;
	}
	// INuiFrameTexture接口，容纳图像数据的对象
	INuiFrameTexture *colorTexture = colorFrame->pFrameTexture;   

	// 提取数据帧到colorLockedRect，并锁定数据
	NUI_LOCKED_RECT colorLockedRect; 
	colorTexture->LockRect(0, &colorLockedRect, NULL, 0);   

	// 至此，LochedRect是真正保存Kinect数据的对象，pitch为每行字节数，pBits为第一个字节地址
	if(colorLockedRect.Pitch != 0) 
	{ 
		for (int i=0; i<colorMat.rows; i++) 
		{
			//第i行的指针，一个字节uchar代表一个颜色信息
			uchar *colorhead = colorMat.ptr<uchar>(i);
			uchar *colorBuffer = (uchar*)(colorLockedRect.pBits) + i * colorLockedRect.Pitch;
			for (int j=0; j<colorMat.cols; j++) 
			{ 
				// Kinect内部数据是4个字节，0-1-2是BGR，第4个现在未使用
				colorhead[3*j] = colorBuffer[4*j];   
				colorhead[3*j+1] = colorBuffer[4*j+1]; 
				colorhead[3*j+2] = colorBuffer[4*j+2]; 
			} 
		} 
	} 
	else 
		cout<<"Get color data failed"<<endl; 

	//本帧数据已处理完故解锁
	colorTexture->UnlockRect(0); 
	//释放本帧数据，准备迎接下一帧
	NuiImageStreamReleaseFrame(colorStreamHandle, colorFrame);
	return true;
} 