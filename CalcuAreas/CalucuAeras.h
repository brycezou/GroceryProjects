class __declspec(dllexport) ImageProcess
{
public:
	static int m_Width;
	static int m_Height;
	double m_Aera;					// ��ʵ���
	static bool m_bSuccessful;	// ��ȡͼ���Ƿ�ɹ�
	static bool m_bProcessing;
	unsigned char *m_ImageData;			// ԭʼͼ��
	unsigned char * m_DstImage;			// ���ͼ��
	static BLOBREGION * m_blobregions;
private:
	 static int m_ImgSize;				// ͼ��ߴ�				
	 unsigned char * m_GrayImage;		// �Ҷ�ͼ��
	 unsigned char * m_BinImage;		// ��ֵͼ��
	 unsigned char * m_ConImage;		// ��ʱͼ��				
public:
	ImageProcess();
	~ImageProcess();
	void LoadImageFromFile_2Threshold(char *filePath);
	void BinaryImage_2Threshold(float ratio, char *strUnit, char *strPrefix, int lowT, int highT);
	void ReleaseImages();
};


__declspec(dllexport) ImageProcess gIp;
__declspec(dllexport) bool loadImage_2Threshold(char *filePath);
__declspec(dllexport) void binaryImage_2Threshold(float ratio, char *strUnit, char *strPrefix, int lowT, int highT);
__declspec(dllexport) void releaseImage();
__declspec(dllexport) void setText_2Threshold(char *strPrefix, float len, bool bLeft, int x1, int y1, int x2, int y2);
__declspec(dllexport) unsigned char* getSrcImage();
__declspec(dllexport) unsigned char* getDstImage();
__declspec(dllexport) int getWidth();
__declspec(dllexport) int getHeight();
__declspec(dllexport) double getAera();
