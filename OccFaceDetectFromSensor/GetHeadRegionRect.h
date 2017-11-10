#include <opencv2/opencv.hpp>


bool B_FORGROUND = false;
bool B_LOCATE_HEAD = false;
bool B_REGISTER = false;

float GF_SCALE = 0.5;

/*
double gWarp[] = {	0.928764,			-0.0790137,			-0.585636,		
								-0.0436254,			0.947218,			-0.623276,		
								-0.000121214,		-0.000322128,		1					};
*/

double gWarp[] = {	1.36788,				0.138139,			-112.907,		
								0.0304907,			1.43976,				-76.9039,	
								9.79889e-005,		0.000453478,		1				};


//���ݲ���fScale������ͼ��srcImg��������
//����ֵΪ���ź��ͼ��
IplImage* resizeImage(IplImage *srcImg, float fScale)
{
	int w = srcImg->width*fScale;
	int h = srcImg->height*fScale;
	IplImage *dstImg = cvCreateImage(cvSize(w, h), srcImg->depth, srcImg->nChannels);
	cvResize(srcImg, dstImg, CV_INTER_LINEAR);  
	return dstImg;
}

//�����ͼ��depthIpl�ж�λ��ͷ���򣬲�����������ڲ���headRect��
//�Բ�ɫͼ��colorIpl������׼
//����ֵΪ��׼��Ĳ�ɫͼ��
//����bShowMidImg���ڿ����Ƿ���ʾ�м���
IplImage* GetHeadRegionRect(IplImage *depthIpl, IplImage *colorIpl, CvRect &headRect, bool bShowMidImg)
{
	//�����ͼ���еõ�ǰ��Ŀ����Ĥͼ��
	IplImage *maskIpl = getForegroundMask(depthIpl, B_FORGROUND);
	if(maskIpl==NULL)
		return NULL;

	//����ɫͼ����׼�����ͼ��
	CvMat homography = cvMat( 3, 3, CV_64FC1, gWarp);
	IplImage *regColorIpl = RegisterColor2Depth(colorIpl, &homography);
	////����ɫͼ��ͻҶ�ͼ�������ͬһ������ϵ��
	////��������ʾ�м�������ʵ�������ã���ɾ��
	//for (int i = 0; i < maskIpl->height; i++) {
	//	for(int j = 0; j < maskIpl->width; j++) {
	//		int pixVal = ((uchar *)(maskIpl->imageData+i*maskIpl->widthStep))[j];
	//		if (pixVal < 128) {
	//			//��δ��׼ͼ���ϱ��
	//			((uchar*)(colorIpl->imageData+i*colorIpl->widthStep))[j*colorIpl->nChannels+0] = 0; 
	//			((uchar*)(colorIpl->imageData+i*colorIpl->widthStep))[j*colorIpl->nChannels+1] = 0; 
	//			((uchar*)(colorIpl->imageData+i*colorIpl->widthStep))[j*colorIpl->nChannels+2] = 0; 
	//			//������׼ͼ���ϱ��
	//			((uchar*)(regColorIpl->imageData+i*regColorIpl->widthStep))[j*regColorIpl->nChannels+0] = 0; 
	//			((uchar*)(regColorIpl->imageData+i*regColorIpl->widthStep))[j*regColorIpl->nChannels+1] = 0; 
	//			((uchar*)(regColorIpl->imageData+i*regColorIpl->widthStep))[j*regColorIpl->nChannels+2] = 0; 
	//		}
	//	}
	//}
	//if(bShowMidImg) {
	//	//07��ʾ��׼ǰ��Ĳ�ɫͼ��
	//	cvShowImage("δ��׼�Ĳ�ɫͼ��", colorIpl);
	//	cvShowImage("����׼�Ĳ�ɫͼ��", regColorIpl);
	//}

	if(bShowMidImg) {
		//06��ʾ��ȷ��ǰ��ͼ
		cvShowImage("��ȷ��ǰ��ͼ��", depthIpl);
	}

	//����Ĥͼ������²����������д�뾶��ֵ�˲�
	IplImage *smallMaskIpl = resizeImage(maskIpl, GF_SCALE);		
	cvReleaseImage(&maskIpl);
	cvSmooth(smallMaskIpl, smallMaskIpl, CV_MEDIAN, 7); //19
	if(bShowMidImg) {
		cvShowImage("��Ĥͼ����ֵ�˲����", smallMaskIpl);
	}

	//����ֵ�˲������Ĥͼ���ж�λ��ͷ��λ��
	headRect = LocateHeadRegionRoughly(smallMaskIpl, B_LOCATE_HEAD);
	if(headRect.width == -1) {
		cvReleaseImage(&regColorIpl);
		cvReleaseImage(&smallMaskIpl);
		return NULL;
	}

	////��������ʾ�м�������ʵ�������ã���ɾ��
	//if (bShowMidImg) {
	//	CvRect &rct = headRect;
	//	cvRectangle(smallMaskIpl, cvPoint(rct.x, rct.y), cvPoint(rct.x+rct.width, rct.y+rct.height), CV_RGB(0,0,128), 1);
	//	cvShowImage("С��ͷ��λ���", smallMaskIpl);
	//}
	cvReleaseImage(&smallMaskIpl);
	return regColorIpl;
}