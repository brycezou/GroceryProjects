#include <opencv2/opencv.hpp>


//����ȡsmallMaskIpl������,
//�ٽ��и���Ҷ�任����任, ����ƽ��
void FindContours(const IplImage *smallMaskIpl, bool bShowMidImg)
{
	//�õ���Ĥͼ��smallMaskIpl��������
	IplImage *counterIpl = findMaxContours(smallMaskIpl);
	//09��ʾ��Ĥͼ�����������
	if(bShowMidImg)
		cvShowImage("��Ĥͼ���������", counterIpl);
	//for (int i = 0; i < pContoursList[0].x; i++)
	//	cout<<pContoursList[i+1].x<<", "<<pContoursList[i+1].y<<endl;

	//������Ĥͼ��߽��pContoursList�ĸ���Ҷ������fourierFactor
	//�ع���õ�ƽ���ı߽������ߣ�������pContoursList��
	CvPoint2D64f *fourierFactor = calcuFourierFactor();
	invrsFourierTransform(fourierFactor);
	delete []fourierFactor;

	if(bShowMidImg) {
		for (int i = 0; i < pContoursList[0].x-1; i++)
			cvLine(counterIpl, cvPoint(pContoursList[i+1].x, pContoursList[i+1].y),cvPoint(pContoursList[i+2].x, pContoursList[i+2].y), CV_RGB(0,0,255), 1);
		//10��ʾƽ�������Ĥͼ����������
		cvShowImage("ƽ�����������", counterIpl);
	}

	cvReleaseImage(&counterIpl);
}
