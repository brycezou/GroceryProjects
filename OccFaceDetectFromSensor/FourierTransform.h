#include <opencv2/opencv.hpp>


#define PI		3.14159

//��Ĥͼ��߽������
CvPoint *pContoursList = NULL;

//�õ���Ĥͼ��maskIpl�������㣬��������ͼ��
IplImage* findMaxContours(const IplImage *maskIpl)
{
	IplImage *tempIpl = cvCloneImage(maskIpl);
	int maxTotal = -1;
	IplImage *counterIpl = cvCreateImage(cvGetSize(tempIpl), IPL_DEPTH_8U, 3);
	cvMerge(tempIpl,  tempIpl,  tempIpl, NULL, counterIpl);
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *cnters = 0, *pCnters = 0;
	cvFindContours (tempIpl, storage, &cnters, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	pCnters = cnters;
	for ( ; pCnters != 0; pCnters = pCnters->h_next)
	{
		if (pCnters->total > maxTotal)
			maxTotal = pCnters->total;
	}

	if (pContoursList != NULL)
	{
		delete []pContoursList;
		pContoursList = NULL;
	}
	pCnters = cnters;
	for ( ; pCnters != 0; pCnters = pCnters->h_next)
	{
		if (pCnters->total == maxTotal)
		{
			pContoursList = new CvPoint[maxTotal+1];
			pContoursList[0] = cvPoint(maxTotal, 0);		//��һ��λ�ô������������
			for (int i = 0; i < pCnters->total; i++)
			{
				CvPoint *pt = (CvPoint*)cvGetSeqElem(pCnters, i); 
				pContoursList[i+1] = cvPoint(pt->x, pt->y);
			}
			cvDrawContours(counterIpl, pCnters, cvScalar(0, 0, 255), cvScalar(255, 0, 0), 1, 1, 8);
			break;
		}
	}

	cvReleaseMemStorage(&storage);
	cvReleaseImage(&tempIpl);
	return counterIpl;
}

//������Ĥͼ��߽��ĸ���Ҷ������
CvPoint2D64f* calcuFourierFactor()
{
	int array_size = pContoursList[0].x;
	CvPoint2D64f *pResult = new CvPoint2D64f[array_size];	//����Ҷ�任����
	for(int u = 0; u < array_size; u++)	//����߽��ĸ���Ҷ�任
	{
		double sum_real = 0;
		double sum_image = 0;
		for (int k = 0; k < array_size; k++)
		{
			double theta = 2*PI*u*k/array_size;
			double sin_theta = sin(theta);
			double cos_theta = cos(theta);
			int x_k = pContoursList[k+1].x;
			int y_k = pContoursList[k+1].y;
			sum_real += x_k*cos_theta+y_k*sin_theta;
			sum_image += y_k*cos_theta-x_k*sin_theta;
		}
		//pResult[u].x = sum_real;
		//pResult[u].y = sum_image;
		pResult[u].x = sum_real/array_size;
		pResult[u].y = sum_image/array_size;
	}
	return pResult;
}

//������Ĥͼ��߽��ĸ���Ҷ������fourierFactor
//�ع�����Ĥͼ��ı߽�㣬���������൱��ƽ��ȥ��
void invrsFourierTransform(CvPoint2D64f *fourierFactor)
{
	int array_size = pContoursList[0].x;
	int PLENGTH = array_size;
	for(int k = 0; k < array_size; k++)	//����߽��ĸ���Ҷ�任
	{
		double sum_real = 0;
		double sum_image = 0;
		for (int u = 0; u < PLENGTH; u++)
		{
			double theta = 2*PI*u*k/PLENGTH;
			double sin_theta = sin(theta);
			double cos_theta = cos(theta);
			int x_u = fourierFactor[u].x;
			int y_u = fourierFactor[u].y;
			sum_real += x_u*cos_theta-y_u*sin_theta;
			sum_image += y_u*cos_theta+x_u*sin_theta;
		}
		//pContoursList[k+1].x = (int)(sum_real/array_size);
		//pContoursList[k+1].y = (int)(sum_image/array_size);
		pContoursList[k+1].x = (int)(sum_real);
		pContoursList[k+1].y = (int)(sum_image);
	}
}


