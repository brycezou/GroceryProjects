#include <opencv2/opencv.hpp>


//maximum iterations for K-Means clustering
#define MAX_ITERATIONS	10

//class centers
int gClassCenters[4] = {500, 0, 0, -1};

//K-Means�����ڶԸ������������dpData����
//����ֵΪ����ǩ
int getClassLabel(int dpData)
{
	int mindist = 500, result;
	for (int i = 0; i < 4; i++)
	{
		int dst = abs(gClassCenters[i]-dpData);
		if (dst < mindist)
		{
			mindist = dst;
			result = i;
		}
	}
	return result;
}

//�õ����ͼ���е����ֵ����Сֵ�����ڳ�ʼ��k-Means�����㷨
void getMaxAndMinValue(const IplImage *depthImg)
{
	gClassCenters[0] = 500;
	gClassCenters[3] = -1;
	for (int i = 0; i < depthImg->height; i++)
	{
		for(int j = 0; j < depthImg->width; j++)
		{
			int pixVal = ((uchar *)(depthImg->imageData+i*depthImg->widthStep))[j];
			if (pixVal > gClassCenters[3])
				gClassCenters[3] = pixVal;
			if (pixVal < gClassCenters[0])
				gClassCenters[0] = pixVal;
		}
	}
}

//ʹ��K-Means����������ݽ���ͼ��ָ�
//����Ϊ���ͼ��depthImg
//���Ϊ���ڷָ������ӻ���ͼ��resultImage
IplImage* kMeansClustering(const IplImage *depthImg, IplImage *resultImage)
{
	//initial class centers
	getMaxAndMinValue(depthImg);
	int dst = (gClassCenters[3]-gClassCenters[0])/3;
	gClassCenters[1] = gClassCenters[0]+dst;
	gClassCenters[2] = gClassCenters[1]+dst;

	//create class label image
	int size = depthImg->width*depthImg->height;
	int *labelImage = new int[size];
	memset(labelImage, 0, sizeof(int)*size);

	//kmeans clustering iterations
	//update class centers and class labels in each iteration for every pixel
	for (int kkk = 0; kkk < MAX_ITERATIONS; kkk++)
	{
		unsigned int Sum4NewCenters[4];
		unsigned int Num4NewCenters[4];
		int NewClassCenters[4];
		memset(Sum4NewCenters, 0, sizeof(unsigned int)*4);
		memset(Num4NewCenters, 0, sizeof(unsigned int)*4);
		memset(NewClassCenters, 0, sizeof(int)*4);

		//update class label for each pixel
		for (int i = 0; i < depthImg->height; i++)
		{
			for(int j = 0; j < depthImg->width; j++)
			{
				int pixVal = ((uchar *)(depthImg->imageData+i*depthImg->widthStep))[j];
				int label = getClassLabel(pixVal);
				labelImage[i*depthImg->width+j] = label;
				Sum4NewCenters[label] += pixVal;
				Num4NewCenters[label]++;
			}
		}

		//get new class centers
		for (int i = 0; i < 4; i++)
		{
			NewClassCenters[i] = Sum4NewCenters[i]/(Num4NewCenters[i]+1);
		}

		//finish iterations or update class centers
		if (NewClassCenters[0] == gClassCenters[0] && NewClassCenters[1] == gClassCenters[1] &&
			NewClassCenters[2] == gClassCenters[2] && NewClassCenters[3] == gClassCenters[3])
		{
			break;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				gClassCenters[i] = NewClassCenters[i];
			}
		}
	}

	IplImage *maskImg = cvCloneImage(depthImg);
	//update visualization image according to class label image
	for (int i = 0; i < resultImage->height; i++)
	{
		for (int j = 0; j < resultImage->width; j++)
		{
			switch (labelImage[i*resultImage->width+j])
			{
			case 0:
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+0] = 0; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+1] = 0; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+2] = 0; 
				((uchar *)(maskImg->imageData+i*maskImg->widthStep))[j] = 0;
				break;			
			case 1:
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+0] = 0; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+1] = 255; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+2] = 0; 
				((uchar *)(maskImg->imageData+i*maskImg->widthStep))[j] = 255;
				break;
			case 2:
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+0] = 128; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+1] = 128; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+2] = 128; 
				((uchar *)(maskImg->imageData+i*maskImg->widthStep))[j] = 0;
				break;
			case 3:
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+0] = 255; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+1] = 255; 
				((uchar*)(resultImage->imageData+i*resultImage->widthStep))[j*resultImage->nChannels+2] = 255; 
				((uchar *)(maskImg->imageData+i*maskImg->widthStep))[j] = 0;
				break;
			}
		}
	}

	//std::cout<<gClassCenters[1]<<std::endl;
	delete []labelImage;
	return maskImg;
}