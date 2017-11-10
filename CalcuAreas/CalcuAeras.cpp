#include <iostream>
# include "viLib.h" // 包含头文件
# include "viImage.h"

# pragma comment( lib, "viLib.lib" ) // 包含viLib.lib库
# pragma comment( lib, "viImage.lib" ) // 包含viImage.lib库
#include "CalucuAeras.h"

using namespace std;

int ImageProcess::m_Width = 0;
int ImageProcess::m_Height = 0;
int ImageProcess::m_ImgSize = 0;
bool ImageProcess::m_bSuccessful = false;
bool ImageProcess::m_bProcessing = false;
BLOBREGION * ImageProcess::m_blobregions = NULL;

ImageProcess::ImageProcess()
{
	m_ImageData = NULL;
	m_DstImage = NULL;
	m_GrayImage = NULL;
	m_BinImage = NULL;
	m_ConImage = NULL;
}

ImageProcess::~ImageProcess()
{
	if (m_bSuccessful)
	{
		m_bSuccessful = false;
		if (m_ImageData != NULL)
		{
			delete []m_ImageData;
			m_ImageData = NULL;
		}
		if (m_DstImage != NULL)
		{
			delete []m_DstImage;
			m_DstImage = NULL;
		}
		if (m_GrayImage != NULL )
		{
			delete []m_GrayImage;
			m_GrayImage = NULL;
		}
		if (m_BinImage != NULL)
		{
			delete []m_BinImage;
			m_BinImage = NULL;
		}
		if (m_ConImage != NULL)
		{
			delete []m_ConImage;
			m_ConImage = NULL;
		}
	}
}

void ImageProcess::LoadImageFromFile_2Threshold(char *filePath)
{
	m_bProcessing = false;
	m_bSuccessful = true;
	int returnvalue = viGetImageWH( filePath, m_Width, m_Height ); // 获得图像尺寸
	if ( returnvalue == 0 ) 
		m_bSuccessful = false;
	if (m_bSuccessful)
	{
		m_ImgSize = m_Width * m_Height;
		int nTotal = 3 * m_ImgSize;
		m_ImageData = new unsigned char [ nTotal ];
		m_DstImage  = new unsigned char [ nTotal ];
		m_GrayImage = new unsigned char [ m_ImgSize ];
		m_BinImage = new unsigned char [ m_ImgSize ];
		m_ConImage = new unsigned char [ m_ImgSize ];
		viReadImageFile( filePath, m_ImageData, m_Width, m_Height, 24 );	// 读入图像数据
		memcpy(m_DstImage, m_ImageData, sizeof(unsigned char)*nTotal);
		viColor24toGray8(m_ImageData, m_Width, m_Height, 1, m_GrayImage);
	}
}

void ImageProcess::BinaryImage_2Threshold(float ratio, char *strUnit, char *strPrefix, int lowT, int highT)
{
	if (m_bProcessing)
		return;
	m_bProcessing = true;
	for (int i = 0; i < m_ImgSize; i++)
	{
		if (m_GrayImage[i] < lowT)
			m_BinImage[i] = 255;
		else if(m_GrayImage[i] > highT)
			m_BinImage[i] = 255;
		else
			m_BinImage[i] = 0;
	}
	// 形态学闭运算，补空洞
	unsigned char sComponentE[25] = { 0 };	
	unsigned char sComponentD[25] = { 0 };
	for ( int i = 0; i < 25; i++ )
	{
		sComponentE[i] = 1;
		if ( i == 2 || ( i > 5 && i < 9) || ( i > 9 && i < 15) || ( i > 15 && i < 19) || i == 22 )
			sComponentD[i] = 1;
	}
	viBinaryClose( m_BinImage, m_Width, m_Height, sComponentE, 5, 5, sComponentD, 5, 5, m_ConImage );
	//viShowImage( "闭运算结果", m_ConImage, m_Width, m_Height, 8, 0 );

	// 进行团块分析
	int NumRegion = 0;		// 团块个数
	NumRegion = viBlobExtract2( m_ConImage, m_Width, m_Height, 1, & m_blobregions ); // 对目标做标记
	if (NumRegion < 1 || NumRegion > 30)
	{
		m_bProcessing = false;
		viFreeBlobRegion( &m_blobregions, NumRegion );
		m_blobregions = NULL;
		return;
	}

	int threshLow = m_ImgSize/500;		// 面积滤波的阈值
	int threshHigh = m_ImgSize/2;   
	memset( m_BinImage, 0, m_ImgSize*sizeof(unsigned char));
	unsigned long maxArea = 1;
	int index = 1;
	bool bIllegal = false;
	for ( int k = 1; k <= NumRegion; k++ )
	{
		int ww = m_blobregions[k].w;
		int hh = m_blobregions[k].h;
		unsigned long area = ww * hh;
		if ( area >= threshLow && area <= threshHigh && ww > 0 && ww < m_Width && hh > 0 && hh < m_Height )
		{
			if (area >= maxArea)
			{
				maxArea = area;
				index = k;
				bIllegal = true;
			}
		}
	}
	if (bIllegal)
		viPasteImage( m_BinImage, m_Width, m_Height, 8, m_blobregions[index].top, m_blobregions[index].left, m_blobregions[index].BlobImage, m_blobregions[index].w, m_blobregions[index].h );
	else
	{
		m_bProcessing = false;
		viFreeBlobRegion( &m_blobregions, NumRegion );
		m_blobregions = NULL;
		return;
	}
	viFreeBlobRegion( &m_blobregions, NumRegion );
	m_blobregions = NULL;
	//viShowImage( "面积滤波结果", m_BinImage, m_Width, m_Height, 8, 0 );

	// 计算面积
	int AreaCounter = 0;
	float Ratio = ratio; // 参数：面积定标
	for ( int i = 0; i < m_ImgSize; i++ )
	{
		m_BinImage[i] > 0 ? AreaCounter++ : AreaCounter;
	}

	// 绘制和显示轮廓
	viContour4( m_BinImage, m_Width, m_Height, m_ConImage );
	memcpy( m_DstImage, m_ImageData, sizeof(unsigned char)*m_ImgSize*3 );
	for ( int i = 0; i < m_ImgSize; i++ )
	{
		if ( m_ConImage[i] == 255 ) // 把轮廓以红色叠加在原始图像上
		{
			m_DstImage[i*3] = 255;
			m_DstImage[i*3+1] = 0;
			m_DstImage[i*3+2] = 0;
		}
	}

	char Text[100];
	m_Aera = AreaCounter*Ratio;
	sprintf( Text, "%s%7.2f %s",  strPrefix, m_Aera, strUnit);
	//viDrawText( m_DstImage, m_Width, m_Height, m_PixelFormat, 25, 25, Text, 24, 48, 0x00ffffff, 0, 0.9f, 0 );
	if (m_Height >= 500)
		viDrawText( m_DstImage, m_Width, m_Height, 24, m_Height/15, m_Height/15, Text, m_Height/20, m_Height/15, 0x00ffffff, 0, 0.9f, 0 );
	else
		viDrawText( m_DstImage, m_Width, m_Height, 24, m_Height/10, m_Height/10, Text, m_Height/15, m_Height/10, 0x00ffffff, 0, 0.9f, 0 );
	m_bProcessing = false;
}

void ImageProcess::ReleaseImages()
{
	if (m_bSuccessful)
	{
		m_bSuccessful = false;
		if (m_ImageData != NULL)
		{
			delete []m_ImageData;
			m_ImageData = NULL;
		}
		if (m_DstImage != NULL)
		{
			delete []m_DstImage;
			m_DstImage = NULL;
		}
		if (m_GrayImage != NULL )
		{
			delete []m_GrayImage;
			m_GrayImage = NULL;
		}
		if (m_BinImage != NULL)
		{
			delete []m_BinImage;
			m_BinImage = NULL;
		}
		if (m_ConImage != NULL)
		{
			delete []m_ConImage;
			m_ConImage = NULL;
		}
	}
}


bool loadImage_2Threshold(char *filePath)
{
	gIp.LoadImageFromFile_2Threshold(filePath);
	return gIp.m_bSuccessful;
}

void binaryImage_2Threshold(float ratio, char *strUnit, char *strPrefix, int lowT, int highT)
{
	if (gIp.m_bSuccessful)
	{
		gIp.BinaryImage_2Threshold(ratio, strUnit, strPrefix, lowT, highT);
	}
}

void releaseImage()
{
	gIp.ReleaseImages();
}

void setText_2Threshold(char *strPrefix, float len, bool bLeft, int x1, int y1, int x2, int y2)
{
	if (gIp.m_bSuccessful)
	{
		char Text[100];
		sprintf( Text, "%s: %7.2f ",  strPrefix, len);
		int height = gIp.m_Height;
		int width = gIp.m_Width;
		viDrawLine(gIp.m_DstImage, width, height, 24, x1, y1, x2, y2, 0x0000ff00);
		viDrawEllipse(gIp.m_DstImage, width, height, 24, x1, y1, 20, 20, 0, 1, 0x00ff00ff);
		viDrawEllipse(gIp.m_DstImage, width, height, 24, x2, y2, 20, 20, 0, 1, 0x00ff00ff);
		if (bLeft)
		{
			viDrawText(gIp.m_DstImage, width, height, 24, y1, x1, "1", 14, 14, 0x00ffff00, 0, 0.9f, 0);
			viDrawText(gIp.m_DstImage, width, height, 24, y2, x2, "1", 14, 14, 0x00ffff00, 0, 0.9f, 0);
			if (height >= 500)
				viDrawText(gIp.m_DstImage, width, height, 24, height-10*height/45, height/15, Text, height/20, height/15, 0x00ffffff, 0, 0.9f, 0);
			else
				viDrawText(gIp.m_DstImage, width, height, 24, height-3*height/10, height/10, Text, height/15, height/10, 0x00ffffff, 0, 0.9f, 0);
		}
		else
		{
			viDrawText(gIp.m_DstImage, width, height, 24, y1, x1, "2", 14, 14, 0x00ffff00, 0, 0.9f, 0);
			viDrawText(gIp.m_DstImage, width, height, 24, y2, x2, "2", 14, 14, 0x00ffff00, 0, 0.9f, 0);
			if (height >= 500)
				viDrawText(gIp.m_DstImage, width, height, 24, height-2*height/15, height/15, Text, height/20, height/15, 0x00ffffff, 0, 0.9f, 0);
			else
				viDrawText(gIp.m_DstImage, width, height, 24, height-2*height/10, height/10, Text, height/15, height/10, 0x00ffffff, 0, 0.9f, 0);
		}
	}
}

unsigned char* getSrcImage()
{
	if (gIp.m_bSuccessful)
	{
		return gIp.m_ImageData;
	}
	else 
		return NULL;
}

unsigned char* getDstImage()
{
	if (gIp.m_bSuccessful)
	{
		return gIp.m_DstImage;
	}
	else 
		return NULL;
}

int getWidth()
{
	return gIp.m_Width;
}

int getHeight()
{
	return gIp.m_Height;
}

double getAera()
{
	return gIp.m_Aera;
}
