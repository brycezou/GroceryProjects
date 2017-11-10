#include <opencv2/opencv.hpp>


//���ݲ���homography������Ĳ�ɫͼ��srcColor���б任
//����ֵΪ�任���ͼ����ߴ�������ͼ��srcColor��ͬ
IplImage* RegisterColor2Depth(IplImage *srcColor, CvMat *homography)
{
	int width = srcColor->width;
	int height = srcColor->height;
	IplImage *tmpRgb = cvCreateImage(cvSize(width*1.5, height*1.5), srcColor->depth, srcColor->nChannels);
	cvWarpPerspective(srcColor, tmpRgb, homography);
	cvSetImageROI(tmpRgb, cvRect(1, 1, width, height));
	IplImage *dstColor = cvCloneImage(srcColor);
	cvCopy(tmpRgb, dstColor);
	cvResetImageROI(tmpRgb);
	cvReleaseImage(&tmpRgb);
	return dstColor;
}
