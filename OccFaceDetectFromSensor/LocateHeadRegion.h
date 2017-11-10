#include <opencv2/opencv.hpp>
#include "TwoClassOTSU.h"
#include <fstream>
#include <iostream>
using namespace std;


#define BOTTOM_FILTER_SIZE	20 
#define CORRECT_DRIFT_LENGTH	2
#define OUT_FILE_NAME ("out.txt")

//�Զ����Ŀ�꺯���Ĳ���
typedef struct ParaArea
{
	int s1;
	int s2;
	int s3;
	int s4;
}ParaArea;

//����ֵ�˲����maskͼ��maskIpl�У�
//ʹ��˫��ͶӰ����λ��ͷ����
CvRect LocateHeadRegionRoughly(const IplImage *maskIpl, bool bShowMidImg) 
{
	int nVerticalProjImageWidth = maskIpl->width;		//��ֱͶӰͼ��Ŀ��
	int  *verticalProjHist = new int[nVerticalProjImageWidth];	//��ֱͶӰֱ��ͼ
	memset(verticalProjHist, 0, nVerticalProjImageWidth*sizeof(int));
	int nMaxVal = -1;		//��ֱͶӰֱ��ͼ�����ֵ
	for (int j = 0; j < maskIpl->width; j++) 
	{
		for (int i = 0; i < maskIpl->height; i++) {
			int pixVal = ((uchar *)(maskIpl->imageData+i*maskIpl->widthStep))[j];
			verticalProjHist[j] += pixVal > 128 ? 1 : 0;
		}
		if(verticalProjHist[j] > nMaxVal)	
			nMaxVal = verticalProjHist[j];
	}
	//��ֱͶӰͼ��ĸ߶�
	int nVerticalProjImageHeight = nMaxVal;

	//��ֱͶӰͼ��
	IplImage *verticalProjIplImage = cvCreateImage(cvSize(nVerticalProjImageWidth, nVerticalProjImageHeight), 8, 1);
	cvZero(verticalProjIplImage);
	for (int i = 0; i < nVerticalProjImageWidth; i++) {
		//cvLine(verticalProjIplImage, cvPoint(i, 0), cvPoint(i, verticalProjHist[i]-1), CV_RGB(0,0,255), 1);
		cvLine(verticalProjIplImage, cvPoint(i, nVerticalProjImageHeight-1), cvPoint(i, nVerticalProjImageHeight-verticalProjHist[i]), CV_RGB(0,0,255), 1);
	}
	if(bShowMidImg) {
		cvShowImage("��ֱͶӰͼ��", verticalProjIplImage);
	}
	delete []verticalProjHist;

	int nHorizentalProjImageHeight = nMaxVal;	//ˮƽͶӰͼ��ĸ߶�
	int  *horizontalProjHist = new int[nHorizentalProjImageHeight];		//ˮƽͶӰֱ��ͼ
	memset(horizontalProjHist, 0, nHorizentalProjImageHeight*sizeof(int));
	nMaxVal = -1;		//ˮƽͶӰֱ��ͼ�����ֵ
	for (int i = 0; i < verticalProjIplImage->height; i++) 
	{
		for (int j = 0; j < verticalProjIplImage->width; j++) {
			int pixVal = ((uchar *)(verticalProjIplImage->imageData+i*verticalProjIplImage->widthStep))[j];
			horizontalProjHist[i] += pixVal > 128 ? 1 : 0;
		}
		if(horizontalProjHist[i] > nMaxVal)
			nMaxVal = horizontalProjHist[i];
	}
	//ˮƽͶӰͼ��Ŀ��
	int nHorizentalProjImageWidth = nMaxVal;

	//�˳��ײ����ܴ��ڵĸ�������
	nHorizentalProjImageHeight = nHorizentalProjImageHeight-BOTTOM_FILTER_SIZE;
	if(nHorizentalProjImageHeight < BOTTOM_FILTER_SIZE)
	{
		delete []horizontalProjHist;
		cvReleaseImage(&verticalProjIplImage);
		return cvRect(-1, -1, -1, -1);
	}

	//ˮƽͶӰͼ��
	IplImage *horizontalProjIplImage = cvCreateImage(cvSize(nHorizentalProjImageWidth, nHorizentalProjImageHeight), 8, 1);
	cvZero(horizontalProjIplImage);
	for (int i = 0; i < nHorizentalProjImageHeight; i++) {
		cvLine(horizontalProjIplImage, cvPoint(0, i), cvPoint(horizontalProjHist[i]-1, i), CV_RGB(0,0,255), 1);
	}
	if (bShowMidImg) {
		cvShowImage("ˮƽͶӰͼ��", horizontalProjIplImage);
	}
	
	//�����������
	int *projIntegral = new int[nHorizentalProjImageHeight];
	projIntegral[0] = horizontalProjHist[0];
	for (int i = 1; i < nHorizentalProjImageHeight; i++) {
		projIntegral[i] = projIntegral[i-1]+horizontalProjHist[i];
	}

	//�Զ���Ŀ�꺯����ÿһ������Ҫ�Ĳ���
	ParaArea *paraArea = new ParaArea[nHorizentalProjImageHeight];
	//�Զ���Ŀ�꺯����ÿһ���ȡֵ
	double *ratio = new double[nHorizentalProjImageHeight];
	double maxRatio = 0;
	int maxIndex = 0;
	//����Ŀ�꺯����ֵ, ���ڷ�������ֵ�ı仯���
	//ofstream ofile(OUT_FILE_NAME);

	for (int i = 1; i < nHorizentalProjImageHeight-1; i++)
	{
		paraArea[i].s1 = projIntegral[i];
		paraArea[i].s2 = (i+1)*horizontalProjHist[i]-paraArea[i].s1;
		paraArea[i].s3 = projIntegral[nHorizentalProjImageHeight-1]-paraArea[i].s1;
		paraArea[i].s4 = (nHorizentalProjImageHeight-i)*horizontalProjHist[nHorizentalProjImageHeight-1]-paraArea[i].s3;
		ratio[i] = (paraArea[i].s1/1.0/paraArea[i].s2)*(paraArea[i].s1/1.0/paraArea[i].s2)*(paraArea[i].s3/1.0/paraArea[i].s4);
		//ofile<<ratio[i]<<endl;		//���Ŀ�꺯��ֵ
	}
	delete []paraArea;
	delete []projIntegral;

	int thresh = TwoClassOTSU(ratio, BOTTOM_FILTER_SIZE/2, nHorizentalProjImageHeight-BOTTOM_FILTER_SIZE/2, ADV_OPT);
	for (int i = 1; i < nHorizentalProjImageHeight-1; i++) {
		if (i >= thresh)	break;
		//����i > thresh/2Լ����2015-11-12
		if (ratio[i] > maxRatio && i > thresh/2) {
			maxRatio = ratio[i];
			maxIndex = i;
		}
	}
	
	int nFaceWidth = horizontalProjHist[maxIndex];
	int nFaceHeight = maxIndex;
	//ofile<<nFaceHeight<<endl;
	//ofile.close();
	delete []ratio;
	delete []horizontalProjHist;

	if(bShowMidImg) {
		cvLine(horizontalProjIplImage, cvPoint(0, nFaceHeight), cvPoint(nHorizentalProjImageWidth-1, nFaceHeight), CV_RGB(0,0,128), 1);
		cvShowImage("ȷ���߶ȿ��_��ˮƽͶӰͼ����", horizontalProjIplImage);
	}
	cvReleaseImage(&horizontalProjIplImage);
	
	//�Դ˷���Ѱ����ͷ�������߽�, �ұ߽�, ���߽�͵ױ߽�
	int leftBorder = 0, rightBorder = 0, topBorder = 0, counter = 0, maxCounter = 0;
	for (int j = 1; j < verticalProjIplImage->width; j++) {
		//�ڵױ߽�maxIndex��Ѱ����߽�
		int preVal = ((uchar *)(verticalProjIplImage->imageData+maxIndex*verticalProjIplImage->widthStep))[j-1];
		int curVal = ((uchar *)(verticalProjIplImage->imageData+maxIndex*verticalProjIplImage->widthStep))[j];
		if(preVal < 128 && curVal >128) {
			counter = 1;
		} else if(preVal > 128 && curVal >128) {
			counter++;
		} else if(preVal > 128 && curVal < 128) {
			if(counter > maxCounter) {
				maxCounter = counter;
				rightBorder = j;	
			}
		}
	}

	nFaceWidth = maxCounter*11/10;
	rightBorder = rightBorder + maxCounter/20;
	leftBorder = rightBorder - maxCounter*21/20;

	if (bShowMidImg) {
		cvLine(verticalProjIplImage, cvPoint(leftBorder, 0), cvPoint(leftBorder, nVerticalProjImageHeight-1), CV_RGB(0,0,128), 1);
		cvLine(verticalProjIplImage, cvPoint(rightBorder, 0), cvPoint(rightBorder, nVerticalProjImageHeight-1), CV_RGB(0,0,128), 1);
		cvLine(verticalProjIplImage, cvPoint(0, nFaceHeight), cvPoint(nVerticalProjImageWidth-1, nFaceHeight), CV_RGB(0,0,128), 1);
		cvShowImage("ȷ�����ұ߽�_�ڴ�ֱͶӰͼ����", verticalProjIplImage);
	}

	topBorder = maskIpl->height-(nHorizentalProjImageHeight+BOTTOM_FILTER_SIZE);
	CvRect rct = cvRect(leftBorder-CORRECT_DRIFT_LENGTH, topBorder, nFaceWidth-1, nFaceHeight);

	cvReleaseImage(&verticalProjIplImage);
	return rct;
}