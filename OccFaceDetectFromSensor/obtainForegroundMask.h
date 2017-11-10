#include <opencv2/opencv.hpp>
#include "BlobResult.h"
#include "blob.h"
#include "kMeansClustering.h"


//����Ĥͼ��maskIpl��Ѱ�����������ͨ�򣬷��ر��ͼ��
IplImage* findMaxObject(IplImage *maskIpl)
{
	CBlobResult blobs;
	CBlob *currentBlob;

	IplImage *blobRGB = cvCreateImage(cvGetSize(maskIpl), IPL_DEPTH_8U, 3);
	blobs = CBlobResult(maskIpl, NULL, 0);
	blobs.Filter( blobs, B_EXCLUDE, CBlobGetArea(), B_LESS, 20);
	cvMerge(maskIpl,  maskIpl,  maskIpl, NULL, blobRGB);

	int blobNumber = 0;
	for (int j = 0; j < blobs.GetNumBlobs(); j++)
	{
		currentBlob = blobs.GetBlob(j);
		CvRect rct = currentBlob->GetBoundingBox();
		int wi = rct.width;
		int he = rct.height;
		int Height = maskIpl->height;
		int Width = maskIpl->width;
		if (wi*he > Width*Height/20)			
		{
			currentBlob->FillBlob(maskIpl, CV_RGB(0, 0, 255));
			currentBlob->FillBlob( blobRGB, CV_RGB(0, 0, 255));
			cvRectangle(blobRGB, cvPoint(rct.x, rct.y), cvPoint(rct.x+rct.width, rct.y+rct.height), cvScalar(0, 255, 0), 1);
			blobNumber++;
		}
		else
			currentBlob->FillBlob(maskIpl, CV_RGB(0, 0, 0));
	}

	if (blobNumber==0)
	{
		cvReleaseImage(&blobRGB);
		return NULL;
	}
	return blobRGB;
}

//�����ͼ����Ѱ��ǰ��Ŀ��
IplImage* getForegroundMask(IplImage *depthIpl, bool bShowMidImg)
{
	//�������ֵ�����ͼ����о��࣬��Ĥ������maskIpl��������������clusteredIpl
	int w = depthIpl->width;
	int h = depthIpl->height;
	IplImage *clusteredIpl = cvCreateImage(cvSize(w, h), 8, 3);
	IplImage *maskIpl = kMeansClustering(depthIpl, clusteredIpl);
	if(bShowMidImg) {
		//02��ʾ������ͼ
		cvShowImage("���ͼ�������ͼ", clusteredIpl);
		cvShowImage("��ԭʼ����Ĥͼ��", maskIpl);
	}
	cvReleaseImage(&clusteredIpl);

	//����Ĥͼ����б����㣬�����׶�
	IplImage *temp = cvCreateImage(cvSize(w, h), 8, 1);
	cvMorphologyEx(maskIpl, maskIpl, temp, NULL, CV_MOP_CLOSE, 10);
	cvReleaseImage(&temp);
	if(bShowMidImg) {
		//03��ʾ��Ĥͼ��
		cvShowImage("��̬ѧ��������Ĥͼ��", maskIpl);
	}

	//����Ĥͼ����Ѱ�����������ͨ��ͬʱ������Ĥ
	IplImage *blobIpl = findMaxObject(maskIpl);
	if(blobIpl == NULL)	
	{
		cvReleaseImage(&maskIpl);
		return NULL;
	}
	//04��ʾ��Ĥͼ��������ͨ����ȡ���
	if(bShowMidImg)	
		cvShowImage("��Ĥͼ��������ͨ��", blobIpl);
	cvReleaseImage(&blobIpl);

	//������ĤmaskIpl��ԭʼ���ͼ��depthIpl��þ�ȷ��ǰ��ͼ�񣬱��浽depthIpl
	for (int i = 0; i < depthIpl->height; i++)
	{
		for (int j = 0; j < depthIpl->width; j++)
		{
			int maskVal = ((uchar *)(maskIpl->imageData+i*maskIpl->widthStep))[j];
			int pixVal = ((uchar *)(depthIpl->imageData+i*depthIpl->widthStep))[j];
			if (maskVal < 32)	//exactly when maskVal == 0 
				((uchar *)(depthIpl->imageData+i*depthIpl->widthStep))[j] = 0;
			else if (pixVal > 160 || pixVal < 32)	//eliminate the effect of over-morphology
			{
				((uchar *)(depthIpl->imageData+i*depthIpl->widthStep))[j] = 0;
				//modify mask image
				//��ʱע�͵����, ʵ�����mask����Ҫ̫��ȷ��ֻҪ����������!
				//ע����2015-11-12
				//((uchar *)(maskIpl->imageData+i*maskIpl->widthStep))[j] = 0;
			}
		}
	}
	//05��ʾ������ľ�ȷǰ����Ĥ
	if(bShowMidImg){
		cvShowImage("��ȷ����Ĥͼ��", maskIpl);
	}

	return maskIpl;
}