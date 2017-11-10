# ifndef _VIIMAGEAPI_
# define _VIIMAGEAPI_

# define VIIMAGE_API  extern "C" __declspec(dllexport)

//////////////////////////////////////////////////////////////////////////
/* ����һЩ���ݽṹ */

/* �����ֵĿ������ݽṹ */
# ifndef __BLOBREGION
# define __BLOBREGION

typedef struct _BlobRegion  // Blob����Ķ���
{
	int top, left;  // ��������Ͻ�����
	int w, h;       // �����͸�
	int tag;        // ������tagλ�������ڱ�ǻ����ܳ������������
	unsigned char * BlobImage;  // ������ͼ���ָ�룬��ߴ�Ϊwxh����Ӧ�ó���������ͷŸ�ͼ���ڴ�
} BLOBREGION;

# endif

/* �����������ݽṹ */
typedef struct _ChainContourObj 
{
	bool IsOutContour;         // �������ͣ�true:������; false:������
	//	char Type;                 // �������ͣ�8���뻹��4���루8��4��
	int x0, y0;                // ������ʼλ�ã�(x,y)
	int ChainLength;           // ����ĳ���
	unsigned char * Chain;      // ����������룬��ʱ�뷽��8��ͨ
	struct _ChainContourObj * Next;   // ��һ��������Ŀ��ָ��
	int Area;                   // �������ֵ
	int Perimeter;              // �ܳ�����ֵ
	int Left, Right, Top, Bottom;     // ��Ӿ��Σ���ֵ
	int tag;                    // ����δ�õı�������ֵ
	int Xc, Yc;                 // �����Χ������������(������������)����ֵ
	double Theta;               // �봹ֱ����ļнǣ�˳ʱ��Ϊ��
	int a, b;                   // ��С�����Բ�İ볤��Ͱ����
} ChainContourObj;   // ����Ŀ�����

//////////////////////////////////////////////////////////////////////////

/* 1 �����źŴ����� */

/************************************************************************/
/*  ��������	viMSE
*	���ܣ�		����ͼ���MSE��Mean Squared Error��
*	��ڲ�����	unsigned char * InData��    ԭʼ����ͼ������
*               unsigned char * OutData��   �����㺬��ͼ������
*               int Width, int Height��     ͼ��Ŀ�͸�
*               int PixelFormat��           ��������24��8
*	����ֵ��	double��                    MSE
*/
/************************************************************************/
VIIMAGE_API double __stdcall viMSE( unsigned char * InData, unsigned char * OutData, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  ��������	viPSNR
*	���ܣ�		����ͼ��ķ�ֵ����ȣ�PSNR��
*	��ڲ�����	unsigned char * InData��    ԭʼ����ͼ������
*               unsigned char * OutData��   �����㺬��ͼ������
*               int Width, int Height��     ͼ��Ŀ�͸�
*               int PixelFormat��           ��������24��8
*	����ֵ��	double��                    PSNR
*/
/************************************************************************/
VIIMAGE_API double __stdcall viPSNR( unsigned char * InData, unsigned char * OutData, int Width, int Height, 
									 int PixelFormat );

/************************************************************************/
/*  ��������	viSNR
*	���ܣ�		����ͼ�������ȣ�SNR��
*	��ڲ�����	unsigned char * InData��    ԭʼ����ͼ������
*               unsigned char * OutData��   �����㺬��ͼ������
*               int Width, int Height��     ͼ��Ŀ�͸�
*               int PixelFormat��           ��������24��8
*	����ֵ��	double��                    SNR
*/
/************************************************************************/
VIIMAGE_API double __stdcall viSNR( unsigned char * InData, unsigned char * OutData, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  ��������	viSaltPepperNoise
*	���ܣ�		����Salt&Pepper����
*	��ڲ�����	unsigned char * InData��    ԭʼ����ͼ������
*               int Width, int Height��     ͼ��Ŀ�͸�
*               int PixelFormat��           ��������24��8
*               float percentage��          0---100֮���һ���ٷֱ�ֵ�����������İٷֱ�
*   ���ڲ�����  unsigned char * OutData��   ����ͼ������
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSaltPepperNoise( unsigned char * InData, int Width, int Height, int PixelFormat, 
											  unsigned char * OutData, float percentage );

/************************************************************************/
/*  ��������	viGaussianNoise
*	���ܣ�		����Gaussian����
*	��ڲ�����	unsigned char * InData��    ԭʼ����ͼ������
*               int Width, int Height��     ͼ��Ŀ�͸�
*               int PixelFormat��           ��������24��8
*               float u, sigma��            ��̬�ֲ��ľ�ֵ�ͷ���(��һ����)
*   ���ڲ�����  unsigned char * OutData��   ����ͼ������
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianNoise( unsigned char * InData, int Width, int Height, int PixelFormat, 
											unsigned char * OutData, float u, float sigma );

/************************************************************************/
/*  ��������	viMeanAndVariance
*	���ܣ�		�������ͼ��ľ�ֵ�ͷ���
*	��ڲ�����	unsigned char * InData��    ͼ������
*               int Width, int Height��     ͼ��Ŀ�͸�
*               int PixelFormat��           ��������24��8
*   ���������  double u, sigma��           ͼ��ľ�ֵ�ͷ���
*	����ֵ��	��
*   ע�⣺ ��ͼ��Ϊ8λ�Ҷ�ͼʱ���ú����������һ��ͼ��ķ������ֵ��
*          ��ͼ��Ϊ24λ��ɫͼʱ�������������R��G��B��ͨ���ķ������ֵ
*          ��Ҫ�õ�R��G��B����ͨ���ľ�ֵ�뷽��ɽ�ͼ���Ϊ3��λƽ�浥������
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMeanAndVariance( unsigned char * InData, int Width, int Height, int PixelFormat, 
											  double &u, double &sigma );

/* 2 ����ͼ��������ͼ��ļ��α任 */

/************************************************************************/
/*  ��������	viCalcuIntegralImageI
*	���ܣ�		����Ҷ�ͼ��Ļ���ͼ����������棩
*   ����ͼ����Ϊ��
*    ii(x,y) = sum_{x'<=x,y'<=y} i(x',y')
*
*   ����ͼ�Ŀ���ʵ��Ϊ��
*    s(x,y) = s(x, y-1)+i(x,y)
*    ii(x,y) = ii(x-1,y)+s(x,y)
*   �˴���s(x,y)�ǵ�y�е��ۼӺͣ�����s(x,-1) = 0����ii(-1,y)=0. 
*   ii(x,y)��Ϊ����ͼ��i(x,y)Ϊԭʼͼ��
*  
*	��ڲ�����	unsigned char * Image��      �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            �������ͣ�����Ϊ8����256���Ҷ�ͼ��
*   ���������  long * IntegralImage:        ���ͼ����Ϊlong�ͻ��ֻҶ�ͼ��
*	����ֵ��	1 --- �ɹ���-1 --- ���㲻�ɹ������صĻ���ͼ��Ч
*/
/************************************************************************/
VIIMAGE_API int __stdcall viCalcuIntegralImageI( unsigned char * Image, int Width, int Height, int PixelFormat,
												 long * IntegralImage );

/************************************************************************/
/*  �꺯������	viIntegralRegionArea
*	���ܣ�		ͨ������ͼ���ĳ������ĻҶ�ֵ��
*	��ڲ�����	long * IntegralImage:        ���ͼ����Ϊlong�ͻ��ֻҶ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int x1, y1, x2, y2��         ����ͼ������Ϻ���������
*	����ֵ��	�ɹ�: ��ѡ�������; ʶ��: -1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIntegralRegionArea( long * IntegralImage, int Width, int Height, 
											    int x1, int y1, int x2, int y2 );

/************************************************************************/
/*  ��������	viResize
*	���ܣ�		�ı�ͼ��ĳߴ�
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               PixelFormat:      PixelFormatΪͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*               rImage:           �ߴ��޸ĺ��ͼ�����ݿ�
*               rWidth, rHeight:  �޸ĺ��ͼ����
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*                                 2 --- �����Բ�ֵ
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viResize( unsigned char * Image, int Width, int Height, int PixelFormat,
									 unsigned char * rImage, int rWidth, int rHeight, int Type );

/************************************************************************/
/*  ��������	viResizeBinary
*	���ܣ�		�ı��ֵͼ��ĳߴ�
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               rImage:           �ߴ��޸ĺ��ͼ�����ݿ�
*               rWidth, rHeight:  �޸ĺ��ͼ����
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*	����ֵ��	��
*   ע�⣺ԭʼͼ��Ϊ��ֵͼ��0��������255����ǰ����ȱʡ��ֵ����Ϊ1
*/
/************************************************************************/
VIIMAGE_API void __stdcall viResizeBinary( unsigned char * Image, int Width, int Height,
										   unsigned char * rImage, int rWidth, int rHeight, int Type );

/************************************************************************/
/*  ��������	viAffineTransform
*	���ܣ�		����任�������任�������£�
*               x'      a11   a12     x     b1
*                   =              *     +  
*               y'      a21   a22     y     b2
*               ��������ӳ�䣺
*               x        1     a22  -a12    x'-b1
*                   =   --- *            * 
*               y        d    -a21   a11    y'-b2
*
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               PixelFormat:      ����λ����8����24
*               rImage:           �任���ͼ�����ݿ�
*               rWidth, rHeight:  Ϊ�任���ͼ����
*               a:                �任������(Ϊ6��������˳��Ϊa11, a12, b1, a21, a22, b2)
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*	����ֵ��	��
*   ע�⣺      �˺����ĸ��ַ���任�������ĵ㣨Width/2, Height/2��Ϊԭ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAffineTransform( unsigned char * Image, int Width, int Height, int PixelFormat,
											  unsigned char * rImage, int rWidth, int rHeight, double * a, int Type );

/************************************************************************/
/*  ��������	viAffineTransformBinary
*	���ܣ�		�Զ�ֵͼ��ķ���任�������任�������£�
*               x'      a11   a12     x     b1
*                   =              *     +  
*               y'      a21   a22     y     b2
*               ��������ӳ�䣺
*               x        1     a22  -a12    x'-b1
*                   =   --- *            * 
*               y        d    -a21   a11    y'-b2
*
*	��ڲ�����	Image:            ԭʼͼ�����ݿ飨0---������255---ǰ����
*               Width, Height:    Ϊͼ����
*               rImage:           �任���ͼ�����ݿ�
*               rWidth, rHeight:  Ϊ�任���ͼ����
*               a:                �任������(Ϊ6��������˳��Ϊa11, a12, b1, a21, a22, b2)
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*	����ֵ��	��
*   ע�⣺      �˺����ĸ��ַ���任�������ĵ㣨Width/2, Height/2��Ϊԭ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAffineTransformBinary( unsigned char * Image, int Width, int Height, unsigned char * rImage, 
												    int rWidth, int rHeight, double * a, int Type );

/************************************************************************/
/*  ��������	viRotate
*	���ܣ�		��ͼ����תһ���Ƕ�
*
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               PixelFormat:      ����λ����8����24
*               rImage:           �任���ͼ�����ݿ�
*               rWidth, rHeight:  Ϊ�任���ͼ����
*               Theta:            ��ת�Ƕȣ��Ƕ�Ϊ��λ����y�᷽��нǣ�˳ʱ��Ϊ����
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*	����ֵ��	��
*   ע�⣺      �˺����ĸ��ַ���任�������ĵ㣨Width/2, Height/2��Ϊԭ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRotate( unsigned char * Image, int Width, int Height, int PixelFormat,
									 unsigned char * rImage, int rWidth, int rHeight, double Theta, int Type );

/************************************************************************/
/*  ��������	viRotateBinary
*	���ܣ�		�Զ�ֵͼ����תһ���Ƕ�
*
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               rImage:           �任���ͼ�����ݿ�
*               rWidth, rHeight:  Ϊ�任���ͼ����
*               Theta:            ��ת�Ƕȣ��Ƕ�Ϊ��λ����y�᷽��нǣ�˳ʱ��Ϊ����
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*	����ֵ��	��
*   ע�⣺      �˺����ĸ��ַ���任�������ĵ㣨Width/2, Height/2��Ϊԭ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRotateBinary( unsigned char * Image, int Width, int Height,
										   unsigned char * rImage, int rWidth, int rHeight, double Theta, int Type );

/************************************************************************/
/*  ��������	viSkew
*	���ܣ�		��ͼ��ĳ������תһ���Ƕ�
*
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               PixelFormat:      ����λ����8����24
*               rImage:           �任���ͼ�����ݿ�
*               rWidth, rHeight:  Ϊ�任���ͼ����
*               Theta:            ��ת�Ƕȣ��Ƕ�Ϊ��λ����y/x�᷽��нǣ�˳ʱ��Ϊ����
*               axis:             0 --- x�ᣬ1 --- y��
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*	����ֵ��	��
*   ע�⣺      �˺����ĸ��ַ���任�������ĵ㣨Width/2, Height/2��Ϊԭ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSkew( unsigned char * Image, int Width, int Height, int PixelFormat,
								   unsigned char * rImage, int rWidth, int rHeight, double Theta, 
								   int axis, int Type );

/************************************************************************/
/*  ��������	viSkewBinary
*	���ܣ�		�Զ�ֵͼ����ĳ������תһ���Ƕ�
*
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               rImage:           �任���ͼ�����ݿ�
*               rWidth, rHeight:  Ϊ�任���ͼ����
*               Theta:            ��ת�Ƕȣ��Ƕ�Ϊ��λ����y/x�᷽��нǣ�˳ʱ��Ϊ����
*               axis:             0 --- x�ᣬ1 --- y��
*               Type:             ͼ���ֵ���ͣ�0 --- ����ڲ�ֵ�� 1 --- ˫���Բ�ֵ��
*	����ֵ��	��
*   ע�⣺      �˺����ĸ��ַ���任�������ĵ㣨Width/2, Height/2��Ϊԭ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSkewBinary( unsigned char * Image, int Width, int Height, 
										 unsigned char * rImage, int rWidth, int rHeight, double Theta, 
										 int axis, int Type );

/************************************************************************/
/*  ��������	viClipImage
*	���ܣ�		��ȡͼ��һ����
*	��ڲ�����	Image:            ԭʼͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               PixelFormat:      PixelFormatΪͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*               cImage:           ��ȡ���ͼ�����ݿ�
*               int top, left:    ��ȡ���ͼ�������
*               int bottom,right: ��������
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viClipImage( unsigned char * Image, int Width, int Height, int PixelFormat,
									    unsigned char * cImage, int top, int left, int bottom, int right );

/************************************************************************/
/*  ��������	viPasteImage
*	���ܣ�		��һ��ͼ��ճ������һ��ͼ����ȥ
*	��ڲ�����	Image:            ��ճ����ͼ�����ݿ�
*               Width, Height:    ��ճ��ͼ����
*               PixelFormat:      PixelFormatΪͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*                                 ��ճ����ճ��ͼ������ɫλ��һ��
*               int top, left:    ճ������ʼλ��
*               pImage:           ճ��ͼ�����ݿ�
*               int W, H:         ճ��ͼ��Ŀ��
*	����ֵ��	��
*   ˵����      ��pImageճ����Image��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viPasteImage( unsigned char * Image, int Width, int Height, int PixelFormat, 
										 int top, int left, unsigned char * pImage, int W, int H );

/* 3 ����ͼ�������������ֵ������ */

/************************************************************************/
/*  ��������	viOtsuThreshold
*	���ܣ�		Otsu����ͼ�������ֵ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*   ���������  unsigned char * OutImage:    ��ֵ�����ͼ��Ϊ������ʾ��ֵΪ0��255��
*               int &threshold��             ѡ����������ֵ
*                                            ע��: ���ͼ����Ϊ256���Ҷ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viOtsuThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
										    unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  ��������	viKSWThreshold
*	���ܣ�		KSW����ͼ�������ֵ��(����ط�)
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*   ���������  unsigned char * OutImage:    ��ֵ�����ͼ��Ϊ������ʾ��ֵΪ0��255��
*               int &threshold��             ѡ����������ֵ
*                                            ע��: ���ͼ����Ϊ256���Ҷ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viKSWThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
										   unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  ��������	viMeanThreshold
*	���ܣ�		ƽ��ֵ����ͼ�������ֵ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*   ���������  unsigned char * OutImage:    ��ֵ�����ͼ��Ϊ������ʾ��ֵΪ0��255��
*               int &threshold��             ѡ����������ֵ
*                                            ע��: ���ͼ����Ϊ256���Ҷ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMeanThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
										    unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  ��������	viIterateThreshold
*	���ܣ�		��������ͼ�������ֵ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*   ���������  unsigned char * OutImage:    ��ֵ�����ͼ��Ϊ������ʾ��ֵΪ0��255��
*               int &threshold��             ѡ����������ֵ
*                                            ע��: ���ͼ����Ϊ256���Ҷ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viIterateThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  ��������	viBinary
*	���ܣ�		�˹�ѡ����ֵ��ͼ����ж�ֵ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int threshold��              �趨����ֵ
*               int Type��                   ��ɫͼ���Ҷ�ͼ�񷽷�
*                                            0 --- ƽ����1 --- �Ӿ����Լ�Ȩ
*   ���������  unsigned char * OutImage:    ��ֵ�����ͼ��Ϊ������ʾ��ֵΪ0��255��
*                                            ע��: ���ͼ����Ϊ256���Ҷ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinary( unsigned char * InImage, int Width, int Height, int PixelFormat,
									 unsigned char * OutImage, int threshold, int Type );

/************************************************************************/
/*  ��������	viDynamicThreshold
*	���ܣ�		��̬��ֵ����ͼ����ж�ֵ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int w,h��                    �ֲ������ڵĿ�͸�
*               int Type��                   ȫ����ֵ���ķ�����0 -- Otsu��1 -- KSW��
*                                                              2 -- ������3 -- ƽ��ֵ��
*   ���������  unsigned char * OutImage:    ��ֵ�����ͼ��Ϊ������ʾ��ֵΪ0��255��
*                                            ע��: ���ͼ����Ϊ256���Ҷ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viDynamicThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   int w, int h, int Type, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viAdaptiveThreshold
*	���ܣ�		����Ӧ��ֵ����ͼ����ж�ֵ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int NWid��                   ��ȷ���ָ�Ŀ�����һ����4-12��ȱʡΪ8��
*               float T��                    Ŀ��ռС����İٷֱȣ�һ����-0.3 --- 0.3��ȱʡ0.15��
*                                            ʵ���������ǰ��Ŀ��Ϊ��ɫ������Ϊ��ɫʱ��ȡ��ֵ����֮����ֵ
*   ���������  unsigned char * OutImage:    ��ֵ�����ͼ��Ϊ������ʾ��ֵΪ0��255��
*                                            ע��: ���ͼ����Ϊ256���Ҷ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAdaptiveThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
											    int NWid, float T, unsigned char * OutImage );

/* 4 ����ͼ�������������ֵͼ���� */

/************************************************************************/
/*  ��������	viBlobExtract
*	���ܣ�		���ֵͼ��ĸ���Blob�������ȡ255����
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  BLOBREGION blobregions[256]��ÿ��blob������Ͻ�����Ϳ���(��Ч������1��ʼ��
*                                            blobregions[0]δ��)
*	����ֵ��    Ѱ�ҵ�������������˳�����blobregions�����У����Ϊ255����
*               ��ֵ��ʾ��ȡ����
*/
/************************************************************************/
VIIMAGE_API int __stdcall viBlobExtract( unsigned char * bImage, int Width, int Height, 
										 BLOBREGION blobregions[256] );

/************************************************************************/
/*  ��������	viLabelImage
*	���ܣ�		��Ƕ�ֵͼ��ĸ�����ͨ��
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  unsigned int * LaImage��     ���ͼ��ͼ��0Ϊ������Ŀ������1��ʼ���
*	����ֵ��    Ѱ�ҵ���������������ֵ��ʾ��ȡ����
*/
/************************************************************************/
VIIMAGE_API int __stdcall viLabelImage( unsigned char * bImage, int width, int height, 
									    unsigned int * LaImage );

/************************************************************************/
/*  ��������	viBlobExtract2
*	���ܣ�		һ�����ܸ����Ƶ����ֵͼ���Blob�ĺ���
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               bool IfCopy��                �Ƿ�ÿ��Blob���򿽱���BLOBREGION��BlobImage��(trueΪ����)
*   ���������  BLOBREGION **blobregions��   ÿ��blob������Ͻ�����Ϳ���(��Ч������1��ʼ��
*                                            blobregions[0]δ��)
*	����ֵ��    Ѱ�ҵ�������������˳�����blobregions�����У�
*               ��ֵ��ʾ��ȡ����
*   ʹ�÷�����
*      ��1����������һ��ָ�룺BLOBREGION * blobregions;
*	   ��2�����ñ�������        viBlobExtract2( bImage, Width, Height, &blobregions );
*	   ��3�������������ͷ��ڴ棺viFreeBlobRegion( &blobregions );
*   ˵����
*               �ú�������û��blob���������ƣ�����Ϊ2^31��blob��    
*/
/************************************************************************/
VIIMAGE_API int __stdcall viBlobExtract2( unsigned char * bImage, int Width, int Height, bool IfCopy, 
										  BLOBREGION ** blobregions );

/************************************************************************/
/*  ��������	viFreeBlobRegion
*	���ܣ�		�ͷ�BlobRegion������ڴ�
*	��ڲ�����	BLOBREGION ** blobregions��  ÿ��blob������Ͻ�����Ϳ���(��Ч������1��ʼ��
*                                            blobregions[0]δ��)
*               int BlobNum��                blobregions��ά����Ϊblob�����+1��0δ�ã�
*	����ֵ��    ��   
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFreeBlobRegion( BLOBREGION ** blobregions, int BlobNum );

/************************************************************************/
/*  ��������	viConnectComponent
*	���ܣ�		һ�����ֵͼ����������ĺ���
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  int * lImage��               �������������ľ�����ߴ���ͼ����ͬ
*                                            (��Ч������1��ʼ��0Ϊ�������)
*	����ֵ��    �����������ֵ��ʾ��ȡ����
*   ˵����
*               �ú�������û��blob���������ƣ�����Ϊ2^31��blob��
*               ���ǣ�ÿ��blob��С����̫��Blob��С������Ϊ��ջ�ߴ磬ĿǰΪ32K 
*               ��һ��256x128�Ŀ������ȷ��ǣ����ڴ˳ߴ�������ȷ��   
*/
/************************************************************************/
VIIMAGE_API int __stdcall viConnectComponent( unsigned char * bImage, int Width, int Height, 
											  int * lImage );

/************************************************************************/
/*  ��������	viColorRegions
*	���ܣ�		��α��ɫ��ǳ�����Blob��
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               BLOBREGION blobregions[256]��ÿ��blob������Ͻ�����Ϳ���(��Ч������1��ʼ��
*                                            blobregions[0]δ��)
*               int RegionNum��              ��ǳ���blob��ĸ���
*   ���������  unsigned char * pImage��     ���24λɫα��ɫͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColorRegions( unsigned char * bImage, int Width, int Height, 
										   BLOBREGION * blobregions, int RegionNum, unsigned char * pImage );

/************************************************************************/
/*  ��������	viColorRegions2
*	���ܣ�		��α��ɫ��Ǹ�����ͨ�����
*	��ڲ�����	unsigned int * LaImage��     ������ͼ������0Ϊ������
*                                            ��������Ϊ˳���ǵ�Ŀ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  unsigned char * pImage��     ���24λɫα��ɫͼ��
*	����ֵ��    ��
*   ע�⣺LaImage���ֵ��Ϊ���������0Ϊ���������������1��ʼ
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColorRegions2( unsigned int * LaImage, int Width, int Height, 
										    unsigned char * pImage );

/************************************************************************/
/*  ��������	viMinBoundingBox
*	���ܣ�		��ȡĿ�����С�ȼ���Բ
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  double Xc, Yc��              Ŀ�������
*               double l, w��                Ŀ��İ볤��Ͱ����
*               double Theta��               Ŀ����y������(�Ƕ�Ϊ��λ)��˳ʱ��Ϊ��
*	����ֵ��    > 0 ��ȷ��< 0 �������
*/
/************************************************************************/
VIIMAGE_API int __stdcall viMinBoundingBox( unsigned char * bImage, int Width, int Height,
										    double & Xc, double & Yc, double & l, double & w, double & Theta );

/************************************************************************/
/*  ��������	viMinBoundingRectangle
*	���ܣ�		��ȡĿ�����С��Ӿ���
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  double Xc, Yc��              Ŀ�������(ע�⣬����һ����Ŀ������м�)
*               double l, w��                Ŀ��ĳ��Ϳ�
*               double Theta��               Ŀ����y������(�Ƕ�Ϊ��λ)��˳ʱ��Ϊ��
*               double xt, yt, xr, yr��      ��Ӿ����ĸ����㣬��(xt, yt)Ϊ���
*               double xb, yb, xl, yl��      ��˳ʱ������
*	����ֵ��    > 0 ��ȷ��< 0 �������
*/
/************************************************************************/
VIIMAGE_API int __stdcall viMinBoundingRectangle( unsigned char * bImage, int Width, int Height,
												  double & Xc, double & Yc, double & l, double & w, double & Theta,
												  double & xt, double & yt, double & xr, double & yr,
												  double & xb, double & yb, double & xl, double & yl );

/************************************************************************/
/*  ��������	viWHRatioFilter
*	���ܣ�		�Զ�ֵͼ����п�߱��˲�
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               BLOBREGION * blobregions��   ÿ��blob������Ͻ�����Ϳ���(��Ч������1��ʼ��
*                                            blobregions[0]δ��)
*               int RegionNum��              �������
*               double MaxWHRatio, MinWHRatio��  �����С��߱ȣ����������е�������
*	����ֵ��    �˲����������������ֵ��ʾ��ȡ����
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWHRatioFilter( unsigned char * bImage, int Width, int Height, 
										   BLOBREGION * blobregions, int RegionNum, 
										   double MaxWHRatio, double MinWHRatio );

/************************************************************************/
/*  ��������	viAreaFilter
*	���ܣ�		�Զ�ֵͼ���������˲�
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ�����а׵�Ϊ255���ڵ�Ϊ0��
*                                            �׵�ΪҪ���Ŀ�����Ķ�ֵͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               BLOBREGION * blobregions��   ÿ��blob������Ͻ�����Ϳ���(��Ч������1��ʼ��
*                                            blobregions[0]δ��)
*               int RegionNum��              �������
*               int MaxArea, MinArea��       �����С�����������������е�������
*	����ֵ��    �˲����������������ֵ��ʾ��ȡ����
*/
/************************************************************************/
VIIMAGE_API int __stdcall viAreaFilter( unsigned char * bImage, int Width, int Height,
									    BLOBREGION * blobregions, int RegionNum, 
										int MaxArea, int MinArea );

/************************************************************************/
/*  ��������	viThinning
*	���ܣ�		�Զ�ֵͼ�����ϸ��
*	��ڲ�����	unsigned char * bImage��     �����ֵͼ������0���ڣ���������
*                                            255���ף�����ǰ�����׵�ΪҪ���Ŀ�ꡣ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  unsigned char * rImage��     �����������Ķ�ֵͼ��0Ϊ������255Ϊǰ����
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viThinning( unsigned char * bImage, int Width, int Height,
									   unsigned char * rImage );

/************************************************************************/
/*  ��������	viFloodFill4
*	���ܣ�		����Flood Fill�㷨(4����)
*	��ڲ�����	unsigned char * Image��    �����ͼ������(Ҫ��Ϊ�Ҷ�ͼ��)��
*               int Width��                ͼ���������
*               int Height��               ͼ��ߣ�������
*               int x��                    ���ӵ��x����
*               int y��                    ���ӵ��y����
*               unsigned char newColor��   ����ɫ
*               unsigned char oldColor��   ����ɫ
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFloodFill4( unsigned char * Image, int Width, int Height, 
										 int x, int y, unsigned char newColor, unsigned char oldColor );

/************************************************************************/
/*  ��������	viContour8
*	���ܣ�		�����ֵͼ���������8�����б�
*	��ڲ�����	unsigned char * BinImage��   ����Ķ�ֵͼ�����ݣ�Ŀ����255��ǣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  unsigned char * ConImage��   ����ͼ��
*	����ֵ��	��
*   ˵����
*               ����ͼ��ֻ��Ϊ��ֵͼ��255ΪĿ�꣬0Ϊ������
*/
/************************************************************************/
VIIMAGE_API void __stdcall viContour8( unsigned char * BinImage, int Width, int Height, 
									   unsigned char * ConImage );

/************************************************************************/
/*  ��������	viContour4
*	���ܣ�		�����ֵͼ���������4�����б�
*	��ڲ�����	unsigned char * BinImage��   ����Ķ�ֵͼ�����ݣ�Ŀ����255��ǣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  unsigned char * ConImage��   ����ͼ��
*	����ֵ��	��
*   ˵����
*               ����ͼ��ֻ��Ϊ��ֵͼ��255ΪĿ�꣬0Ϊ������
*/
/************************************************************************/
VIIMAGE_API void __stdcall viContour4( unsigned char * BinImage, int Width, int Height, 
									   unsigned char * ConImage );

/************************************************************************/
/*  ��������	viTraceContour8
*	���ܣ�		���һ��������8�����б�
*	��ڲ�����	unsigned char * ConImage��   ����Ķ�ֵ����ͼ��������255��ǣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  int ** Contour��             ��������
*	����ֵ��	�����������ߵĵ���N(��ʼ���2��)��N = 0��ʾδ���ٵ�������ͼ����û��������
*   ˵����
*               1��*Contour��ά��Ϊ2Nά��ż��λ�ô�x���꣬����λ�ô�y����
*               2��������������*Contour�ڴ棨������ָ���ָ�룩��ʹ��viFreeContour()�����ͷ��ڴ�
*               3������һ�α������ɻ��һ��������ͬʱ���ڶ�ֵ����ͼ��ConImage�н������������
*                  �Ա��ڼ������ñ���������������������ˣ���Ҫ��ö������������ε��ñ�
*                  ������ֱ������ֵΪ0�����⣬���ñ�������Ӱ��ConImage�е����ݡ�
*               4���������ɸ��ٷǷ�����ߣ����ڷǷ�����ߣ������߱����ؼ�¼��
*               5�����������������ܱ߽��ϵĵ㣬����߽�����Ŀ��㣬�ɲ��ö����ܱ߽���������ͼ��
*               6��ÿ��������ʼ�㱣�����Σ���ʹ���߷�գ�����(x0,y0)->(x1,y1)->...->(xn,yn)->(x0,y0)
*/
/************************************************************************/
VIIMAGE_API int __stdcall viTraceContour8( unsigned char * ConImage, int Width, int Height,
										   int ** Contour );

/************************************************************************/
/*  ��������	viTraceContour4
*	���ܣ�		���һ��������4�����б�
*	��ڲ�����	unsigned char * ConImage��   ����Ķ�ֵ����ͼ��������255��ǣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  int ** Contour��             ��������
*	����ֵ��	�����������ߵĵ���N(��ʼ���2��)��N = 0��ʾδ���ٵ�������ͼ����û��������
*   ˵����
*               1��*Contour��ά��Ϊ2Nά��ż��λ�ô�x���꣬����λ�ô�y����
*               2��������������*Contour�ڴ棨������ָ���ָ�룩��ʹ��viFreeContour()�����ͷ��ڴ�
*               3������һ�α������ɻ��һ��������ͬʱ���ڶ�ֵ����ͼ��ConImage�н������������
*                  �Ա��ڼ������ñ���������������������ˣ���Ҫ��ö������������ε��ñ�
*                  ������ֱ������ֵΪ0�����⣬���ñ�������Ӱ��ConImage�е����ݡ�
*               4���������ɸ��ٷǷ�����ߣ����ڷǷ�����ߣ������߱����ؼ�¼��
*               5�����������������ܱ߽��ϵĵ㣬����߽�����Ŀ��㣬�ɲ��ö����ܱ߽���������ͼ��
*               6��ÿ��������ʼ�㱣�����Σ���ʹ���߷�գ�����(x0,y0)->(x1,y1)->...->(xn,yn)->(x0,y0)
*/
/************************************************************************/
VIIMAGE_API int __stdcall viTraceContour4( unsigned char * ConImage, int Width, int Height, 
										   int ** Contour );

/************************************************************************/
/*  ��������	viFreeContour
*	���ܣ�		�ͷ�����������ռ�ڴ�
*	��ڲ�����	int ** Contour��             ��������
*	����ֵ��	��
*   ˵����
*               �ͷ�viTraceContour4()��viTraceContour8()��������������ڴ档
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFreeContour( int ** Contour );

/************************************************************************/
/*  ��������	viTraceContour
*	���ܣ�		���ٵ�����������������
*	��ڲ�����	unsigned char * Img��     ����ͼ��Ϊ��ֵͼ��
*               int Width, Height��       ͼ���͸�
*               int x, int y��            �����ʼ�㣨������ʼ�㣩
*               unsigned char * codebuf�� ���루1�ֽ�һ�����룩
*               int bufsize��             ����Buffer����
*               bool isOut��              �Ƿ�Ϊ��������1Ϊ��������0Ϊ��������
*	����ֵ��	���볤��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viTraceContour( unsigned char * Img, int Width, int Height, int x, int y, 
										  unsigned char * codebuf, int bufsize, bool isOut );

/************************************************************************/
/*  ��������	viFindContours
*	���ܣ�		��ö�ֵĿ��Ķ�����������
*	��ڲ�����	unsigned char * bImage��     ����Ķ�ֵͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int MiniP��                  ��С�ܳ�������Ϊ��λ��
*               int MiniS��                  ��С���������Ϊ��λ��
*               int ChainType:               ����������ͣ�1 --- ���������٣�
*                                            2 --- ���������٣�3 --- ��������������
*   ���ֵ��    int ObjectNum:               ���ٵ���Ŀ�����
*	����ֵ��	����ָ�룬��δ�ҵ����룬�򷵻�NULL
*   ˵����      �ڸ���������Ѿ���������������Ŀ�������������������ܳ�
*/
/************************************************************************/
VIIMAGE_API ChainContourObj * __stdcall viFindContours( unsigned char * bImage, int Width, int Height,
													    int MiniP, int MiniS, int ChainType, int &ObjectNum );

/************************************************************************/
/*  ��������	viFreeChainContourObj
*	���ܣ�		�ͷ�Ŀ������
*	��ڲ�����	ChainContourObj * all_Contours�� Ŀ����������ͷָ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFreeChainContourObj( ChainContourObj * all_Contours );

/************************************************************************/
/*  ��������	viFillingContour
*	���ܣ�		������������һ�����������ɫ���
*	��ڲ�����	unsigned char * gImage��     ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int x0, y0��                 �������
*               unsigned char * code��       �������
*               int N:                       ���볤��
*               boo fillEdge��               �Ƿ�����Ե
*               unsigned char nonc��         �߽���ɫ������յ㣩
*                                           ����������һ��δ�ù����м�ֵ��������м�������������߽磩
*               unsigned char fillc��        �����ɫ�������㣩
*   ���ֵ��    unsigned char * gImage��     Ŀ�������ͼ������
*	����ֵ��	��䷽��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viFillingContour( unsigned char * gImage, int Width, int Height,
										    int x0, int y0, unsigned char * code, int N,
										    bool fillEdge, unsigned char nonc, unsigned char fillc );

/************************************************************************/
/*  ��������	viMarkChainWithColor
*	���ܣ�		�������ǵ�Ŀ��������һ�ֻҶ�
*	��ڲ�����  unsigned char * gImage:      �Ҷ�ͼ��
*               int Width, Height:           ͼ����
*               int x, y:                    ������ʼ����
*               unsigned char * Code:        �������
*               int N:                       ���볤��
*               unsigned char Color:         ���Ƶ���ɫ��0-255
*   ���������  unsigned char * gImage:      ��Ǻ�Ŀ��ĻҶ�ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMarkChainWithColor( unsigned char * gImage, int Width, int Height, 
												 int x, int y, unsigned char * Code, int N, unsigned char Color );

/************************************************************************/
/*  ��������	viAreaAndPerimeterPixel
*	���ܣ�		��������������������ܳ�(�����ľ������صĸ����������Ǳ߽�ռ�ı���)
*	��ڲ�����	unsigned char * code�� Ŀ����������ͷָ��
*               int N��                ���볤��
*   ���������  int * Area��           �������Ŀ�����
*               int * Perimeter��      �������Ŀ���ܳ�
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAreaAndPerimeterPixel( unsigned char * code, int N, int * Area, int * Perimeter );

/************************************************************************/
/*  ��������	viAreaAndPerimeter
*	���ܣ�		��������������������ܳ�
*               (������ʽ���㣬8�����б�������sqrt(2)�����أ�������ƫ��)
*	��ڲ�����	unsigned char * Code:   �������
*               int N:                  ���볤��
*   ���������  int * Area:             Ŀ�����
*               int * Perimeter:        Ŀ���ܳ�
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAreaAndPerimeter( unsigned char * Code, int N, int * Area, int * Perimeter );

/************************************************************************/
/*  ��������	viCentroidAndBoundingBox
*	���ܣ�		��������������������ܳ�
*               (������ʽ���㣬8�����б�������sqrt(2)�����أ�������ƫ��)
*	��ڲ�����	int x0, y0:             �������(x0,y0)
*               unsigned char * Code:   �������
*               int N:                  ���볤��
*   ���������  int * Left, * Top:      Ŀ�����ҡ��ϡ��±߽�
*               int * Right, * Bottom:
*               int * Xc, * Yc:         Ŀ������
*               double * Theta:         ��y�����ǣ�˳ʱ��Ϊ�����Ƕȵ�λ
*               int * l, * w:           �볤�ᡢ����
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viCentroidAndBoundingBox( int x0, int y0, unsigned char * Code, int N, int * Left, int * Top, 
													 int * Right, int * Bottom, int * Xc, int * Yc, double * Theta, int * l, int * w );
													
/************************************************************************/
/*  ��������	viCalcuContourObj
*	���ܣ�		����Ŀ�������������ܳ�����Ӿ��ο��ߡ����������
*	��ڲ�����	ChainContourObj * all_Contours�� Ŀ����������ͷָ��
*	����ֵ��	Ŀ��ĸ���
*/
/************************************************************************/
VIIMAGE_API int __stdcall viCalcuContourObj( ChainContourObj * all_Contours );

/************************************************************************/
/*  ��������	viLineFitting
*	���ܣ�		��ֱ�� y = bx + a ���һ��㣨xi,yi��
*	��ڲ�����	int * xi:         x����
*               int * yi:         y����
*               int N:            ������������ >=2
*   ���������  double alpha:     ��x��нǣ��Ƕ�Ϊ��λ��˳ʱ��Ϊ����b = tan( alpha )
*               double a:         ֱ�߽ؾ�(��alpha = 90ʱ��aΪ����)
*	����ֵ��	0 --- ���㲻�ɹ��� 1 --- ����ɹ�
*/
/************************************************************************/
VIIMAGE_API int __stdcall viLineFitting( int * xi, int * yi, int N, double & alpha, double & a );

/************************************************************************/
/*  ��������	viHuMoments
*	���ܣ�		�����ֵͼ���7��Hu�����
*	��ڲ�����	unsigned char * BinImage��   ����Ķ�ֵͼ�����ݣ�Ŀ����255��ǣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*   ���������  int Xc, Yc��                 Ŀ�������
*               double & phi1 - phi7��       7��Hu�����
*	����ֵ��	��
*   ˵����
*               ����ͼ��ֻ��Ϊ��ֵͼ��255ΪĿ�꣬0Ϊ������
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHuMoments( unsigned char * BinImage, int Width, int Height, int & Xc, int & Yc,
									    double & phi1, double & phi2, double & phi3, double & phi4, 
									    double & phi5, double & phi6, double & phi7 );

/************************************************************************/
/*  ��������	viEllipticFD
*	���ܣ�		����Elliptic Fourier Descriptor�����ֵͼ����������Ҷ������
*	��ڲ�����	int * Contour��              ������������
*               N��                          �������ݵ���
*               int M��                      ����Ҷ�����ӵĸ���
*   ���������  double * FD��                ����Ҷ����������
*	����ֵ��	��
*   ˵����
*               �������ݵ���ΪN������Contour�ĳ���Ϊ2N��ż��λ�ô�x���꣬
*               ����λ�ô�y���ꡣContourΪ�������������β�νӣ���1�㱣�����Σ�
*               MΪ�������Ҷ�����ӵĸ�����M�����˿��������ϵĵ�ĳ��������
*               �������Ϊround( N/M )
*/
/************************************************************************/
VIIMAGE_API void __stdcall viEllipticFD( int * Contour, int N, int M, double * FD );

/* 5 ����ͼ��������ͼ��㴦�� */

/************************************************************************/
/*  ��������	viImageInvert
*	���ܣ�		ͼ��ȡ������
*	��ڲ�����	unsigned char * Image��      ����ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ͼ�����ظ�ʽ��24��8
*   ���������  unsigned char * rImage��     ���ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viImageInvert( unsigned char * Image, int Width, int Height, int PixelFormat,
										  unsigned char * rImage );

/************************************************************************/
/*  ��������	viAlphaFusion
*	���ܣ�		������ɫͼ��Alpha�ϳ�
*	��ڲ�����	unsigned char * Image1��     �����1����ɫͼ��
*               int Width��                  ��1��ͼ���������
*               int Height��                 ��1��ͼ��ߣ�������
*               int PixelFormat��            ��1��ͼ�����ظ�ʽ������Ϊ24λ���ɫ
*               double Alpha��               ��1��ͼ���Alphaֵ
*               unsigned char * Image2��     �����2��ͼ��
*               int Width2��                 ��2��ͼ���
*               int Height2��                ��2��ͼ���
*               int PixelFormat2��           ��2��ͼ�����ظ�ʽ��24��8
*   ���������  unsigned char * rImage��     ���ͼ�񣬳ߴ����1��ͼ��һ������Ϊ24λ���ɫ
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAlphaFusion( unsigned char * Image1, int Width, int Height, int PixelFormat,
										  double Alpha, unsigned char * Image2, int Width2, int Height2,
										  int PixelFormat2, unsigned char * rImage );

/* 6 ����ͼ����������̬ѧ���� */

/************************************************************************/
/*  ��������	viBinaryErosion
*	���ܣ�		��ֵͼ��ĸ�ʴ����
*	��ڲ�����	unsigned char * bImage��     ����ͼ�񣬱���Ϊ��ֵͼ��
*                                            0���ڣ���������255���ף�����ǰ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*   ���������  unsigned char * rImage��     ��ʴ�����Ķ�ֵͼ��0Ϊ������255Ϊǰ����
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryErosion( unsigned char * bImage, int Width, int Height,
										    unsigned char * sComponent, int w, int h,
											unsigned char * rImage );

/************************************************************************/
/*  ��������	viBinaryDilation
*	���ܣ�		��ֵͼ�����������
*	��ڲ�����	unsigned char * bImage��     ����ͼ�񣬱���Ϊ��ֵͼ��
*                                            0���ڣ���������255���ף�����ǰ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*   ���������  unsigned char * rImage��     ���������Ķ�ֵͼ��0Ϊ������255Ϊǰ����
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryDilation( unsigned char * bImage, int Width, int Height,
										     unsigned char * sComponent, int w, int h,
											 unsigned char * rImage );

/************************************************************************/
/*  ��������	viBinaryOpen
*	���ܣ�		��ֵͼ��Ŀ�����
*	��ڲ�����	unsigned char * bImage��     ����ͼ�񣬱���Ϊ��ֵͼ��
*                                            0���ڣ���������255���ף�����ǰ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponentE����ʴ�ṹԪ��(ԭ����[w/2,h/2]��)
*               int wE,hE��                  ��ʴ�ṹԪ�صĿ�͸�
*               unsigned char * sComponentD�����ͽṹԪ��(ԭ����[w/2,h/2]��)
*               int wD,hD��                  ���ͽṹԪ�صĿ�͸�
*   ���������  unsigned char * rImage��     ���������Ķ�ֵͼ��0Ϊ������255Ϊǰ����
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryOpen( unsigned char * bImage, int Width, int Height,
										 unsigned char * sComponentE, int wE, int hE,
										 unsigned char * sComponentD, int wD, int hD,
										 unsigned char * rImage );

/************************************************************************/
/*  ��������	viBinaryClose
*	���ܣ�		��ֵͼ��ı�����
*	��ڲ�����	unsigned char * bImage��     ����ͼ�񣬱���Ϊ��ֵͼ��
*                                            0���ڣ���������255���ף�����ǰ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponentE����ʴ�ṹԪ��(ԭ����[w/2,h/2]��)
*               int wE,hE��                  ��ʴ�ṹԪ�صĿ�͸�
*               unsigned char * sComponentD�����ͽṹԪ��(ԭ����[w/2,h/2]��)
*               int wD,hD��                  ���ͽṹԪ�صĿ�͸�
*   ���������  unsigned char * rImage��     ���������Ķ�ֵͼ��0Ϊ������255Ϊǰ����
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryClose( unsigned char * bImage, int Width, int Height,
										  unsigned char * sComponentE, int wE, int hE,
										  unsigned char * sComponentD, int wD, int hD,
										  unsigned char * rImage );

/************************************************************************/
/*  ��������	viMorphContour
*	���ܣ�		����̬ѧ������ȡ��ֵͼ��������������������
*	��ڲ�����	unsigned char * bImage��   �����ͼ�����ݣ�ͼ���СΪWxH�ֽڣ�
*               int Width��                ͼ���������
*               int Height��               ͼ��ߣ�������
*               int x��                    ���ӵ��x����
*               int y��                    ���ӵ��y����
*               unsigned char newColor��   ����ɫ
*               unsigned char oldColor��   ����ɫ
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphContour( unsigned char * bImage, int Width, int Height, 
										   unsigned char * rImage );

/************************************************************************/
/*  ��������	viGrayDilation
*	���ܣ�		�Ҷ�ͼ�����������
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     ���������Ľ��ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayDilation( unsigned char * gImage, int Width, int Height,
										   unsigned char * sComponent, int w, int h, int AutoType,
										   unsigned char * rImage );

/************************************************************************/
/*  ��������	viGrayErosion
*	���ܣ�		�Ҷ�ͼ��ĸ�ʴ����
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     ��ʴ�����Ľ��ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayErosion( unsigned char * gImage, int Width, int Height,
										  unsigned char * sComponent, int w, int h, int AutoType,
										  unsigned char * rImage );

/************************************************************************/
/*  ��������	viGrayOpen
*	���ܣ�		�Ҷ�ͼ�����̬ѧ������
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     �������Ľ��ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayOpen( unsigned char * gImage, int Width, int Height,
									   unsigned char * sComponent, int w, int h, int AutoType,
									   unsigned char * rImage );

/************************************************************************/
/*  ��������	viGrayClose
*	���ܣ�		�Ҷ�ͼ�����̬ѧ������
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     �������Ľ��ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayClose( unsigned char * gImage, int Width, int Height,
									    unsigned char * sComponent, int w, int h, int AutoType,
									    unsigned char * rImage );

/************************************************************************/
/*  ��������	viMorphSmooth
*	���ܣ�		�Ҷ���̬ѧͼ��ƽ��
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     ƽ����Ľ��ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphSmooth( unsigned char * gImage, int Width, int Height,
										  unsigned char * sComponent, int w, int h, int AutoType,
										  unsigned char * rImage );

/************************************************************************/
/*  ��������	viMorphGradient
*	���ܣ�		�Ҷ���̬ѧ��ͼ���ݶ�
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     ��õ���̬ѧ�ݶ�ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphGradient( unsigned char * gImage, int Width, int Height,
										    unsigned char * sComponent, int w, int h, int AutoType,
										    unsigned char * rImage );

/************************************************************************/
/*  ��������	viMorphTophat
*	���ܣ�		�Ҷ���̬ѧ��ñ�任
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     ��õĽ��ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphTophat( unsigned char * gImage, int Width, int Height,
										  unsigned char * sComponent, int w, int h, int AutoType,
										  unsigned char * rImage );

/************************************************************************/
/*  ��������	viMorphBottomhat
*	���ܣ�		�Ҷ���̬ѧ��ñ�任
*	��ڲ�����	unsigned char * gImage��     ����ͼ�񣬱���Ϊ�Ҷ�ͼ��
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               unsigned char * sComponent�� �ṹԪ��(�ṹԪ�ص�ԭ����[w/2,h/2]��)
*               int w, h��                   �ṹԪ�صĿ�͸�
*               int AutoType��               �Զ������ĽṹԪ��
*                                            0 --- ���Զ���������sComponent�ṩ�� 
*                                            1 --- ���Σ�2 --- ʮ���Σ�3 --- ��Բ��
*                                            �Զ������ĻҶ�ֵΪsComponent[0]                 
*   ���������  unsigned char * rImage��     ��õĽ��ͼ��
*	����ֵ��    ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphBottomhat( unsigned char * gImage, int Width, int Height,
											 unsigned char * sComponent, int w, int h, int AutoType,
											 unsigned char * rImage );

/************************************************************************/
/*  ��������	viWaterShed_Vincent
*	���ܣ�		��ˮ��ָVincent����������+���飩
*	��ڲ�����	unsigned char * Image��      ���ָ�ͼ�����ݣ�8��24λ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int MorphGradient��          ��̬ѧ�ݶ���ȡǿ�ȣ�1--20��ԽСԽ����ȱʡΪ3
*               int GaussWin��               ��˹ƽ�����ڿ���Ϊ3��5��7��9��Ϊ1��ƽ����ȱʡȡ5
*               int Threshold��              �ݶ�������ֵ��ѡ��Χ�ڣ�2~8֮�䣬1���ʾ��������
*               int IfBound��                ���ͼ���ʽ
*                    IfBound = 1, ��ԭͼ����ʾ��ˮ���ߣ�ͼ��ָ���Ǵ�1��MaxLabelNo��
*                    IfBound = 0, ��ʾ�����飬ͼ��ָ����Ҳ�Ǵ�1��MaxLabelNo������û�з�ˮ��
*   ���������  int SegImage��               ������ͼ��ͼ���ʽ��IfBound����
*	����ֵ��	�ɹ����ָ����ͼ�����Ŀ��MaxLabelNo����ʧ�ܣ�����0
*   ע�⣺      �����Threshold���ڿ��Ʊ�Եͼ���м�Сֵ�ĸ�����������ı�Եͼ��ϵͳ�Զ�����
*               һ����ֵt��ȡt/Threshold��Ϊ������ֵ�����ڸ�ֵ�����ݶ���Ϊ��Сֵ��ǿ�Ƹ�Ϊ0��
*               MorphGradient��Threshold���������Ƽ�Сֵ����Ŀ
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaterShed_Vincent( unsigned char * Image, int Width, int Height, int PixelFormat, 
											   int * SegImage, int MorphGradient, int GaussWin, int Threshold, 
											   int IfBound );

/************************************************************************/
/*  ��������	viShowWaterShedSeg
*	���ܣ�		��ʾ��ˮ��ָ�Ľ��
*	��ڲ�����	int * SegImage��             ����ʾ�ķָ���
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int IfBound��                ���ͼ���ʽ����SegImage������
*                    IfBound = 1, ��ԭͼ����ʾ��ˮ���ߣ�ͼ��ָ���Ǵ�1��MaxLabelNo��
*                    IfBound = 0, ��ʾ�����飬ͼ��ָ����Ҳ�Ǵ�1��MaxLabelNo������û�з�ˮ��
*               unsigned char * OrigImage��  ԭʼͼ�����ݣ���/��ΪWidth��Height
*               int PixelFormat��            ԭʼͼ���ʽ��Ϊ24��8
*               double Alpha��               ͼ���͸��ֵAlphaֵ
*               int Color��                  ��ˮ����ɫ������AlphaֵӰ�죩
*   ���������  unsigned char * sImage��     ��ʾ��ͼ�񣨱���Ϊ24λ���ɫ����
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viShowWaterShedSeg( int * SegImage, int Width, int Height, int IfBound, 
											   unsigned char * OrigImage, int PixelFormat, double Alpha, int Color,
											   unsigned char * sImage );

/* 7 ����ͼ����������ɫ�ռ�ת������ */

/************************************************************************/
/*  ��������	viColor24toGray8
*	���ܣ�		24λ��ɫͼ��ת��Ϊ8λ�Ҷ�ͼ��
*	��ڲ�����	unsigned char * ColorImage��    ԭʼ��ɫͼ������
*               int Width, int Height��         ͼ��Ŀ�͸�
*               int Type��                      ת�����ͣ�
*   0��ȱʡ�� --- ƽ��ת����Y = ( R + G + B )/3
*   1         --- ��Ȩת����Y601 = 0.299 * R + 0.587 * G + 0.114 * B ��ITU_R_BT601��
*   ���ڲ�����  unsigned char * GrayImage��     �Ҷ�ͼ������
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColor24toGray8( unsigned char * ColorImage, int Width, int Height, int Type,
											 unsigned char * GrayImage );

/************************************************************************/
/*  ��������	viGray8toColor24
*	���ܣ�		8λ�Ҷ�ͼ��ת��Ϊ24λ��ɫͼ��
*	��ڲ�����	unsigned char * GrayImage��     �Ҷ�ͼ������
*               int Width, int Height��         ͼ��Ŀ�͸�
*               int Type��                      ת�����ͣ�
*                                               0��ȱʡ�� --- RGB�ֱ������Ӧ�Ҷ�����
*                                               1         --- ң��α��ɫ
*                                               2         --- ҽѧα��ɫ
*   ���ڲ�����  unsigned char * ColorImage��    24λ��ɫͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGray8toColor24( unsigned char * GrayImage, int Width, int Height, int Type,
											 unsigned char * ColorImage );

/************************************************************************/
/*  ��������	viColor24toRGB
*	���ܣ�		24λ��ɫͼ��ת��ΪRGB��ͨ��ͼ��
*	��ڲ�����	unsigned char * ColorImage��    ԭʼ��ɫͼ������
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  unsigned char * rChannel��      Rͨ��
*               unsigned char * gChannel��      Gͨ��
*               unsigned char * bChannel��      Bͨ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColor24toRGB( unsigned char * ColorImage, int Width, int Height,
										   unsigned char * rChannel, unsigned char * gChannel, unsigned char * bChannel );

/************************************************************************/
/*  ��������	viRGBtoColor24
*	���ܣ�		RGB��ͨ��ͼ��ת��Ϊ24λ��ɫͼ��
*	��ڲ�����	unsigned char * rChannel��      Rͨ��
*               unsigned char * gChannel��      Gͨ��
*               unsigned char * bChannel��      Bͨ��
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  unsigned char * ColorImage��    ԭʼ��ɫͼ������
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRGBtoColor24( unsigned char * rChannel, unsigned char * gChannel, unsigned char * bChannel,
										   int Width, int Height, unsigned char * ColorImage );

/************************************************************************/
/*  ��������	viRGBtoYUV
*	���ܣ�		RGBͼ��ת��ΪYUV��ͨ��ͼ��
*	��ڲ�����	unsigned char * ColorImage��    ԭʼ��ɫͼ������
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  unsigned char * Y��             Y����
*               unsigned char * U��             U����
*               unsigned char * V��             V����
*	����ֵ��	
*               1 --- �ɹ���0 --- ���ɹ�
*/
/************************************************************************/
VIIMAGE_API int __stdcall viRGBtoYUV( unsigned char * ColorImage, int Width, int Height,
									  unsigned char * Y, unsigned char * U, unsigned char * V );

/************************************************************************/
/*  ��������	viYUVtoRGB
*	���ܣ�		YUV��ͨ��ͼ��ת��ΪRGBͼ��
*	��ڲ�����	unsigned char * Y��             Y����
*               unsigned char * U��             U����
*               unsigned char * V��             V����
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  unsigned char * ColorImage��    ԭʼ��ɫͼ������
*	����ֵ��	
*               1 --- �ɹ���0 --- ���ɹ�
*/
/************************************************************************/
VIIMAGE_API int __stdcall viYUVtoRGB( unsigned char * Y, unsigned char * U, unsigned char * V,
									  int Width, int Height, unsigned char * ColorImage );

/************************************************************************/
/*  ��������	viRGBtoHSL
*	���ܣ�		RGB��ͨ��ͼ��ת��ΪHSLͼ��
*	��ڲ�����	unsigned char * ColorImage��    ԭʼ��ɫͼ������(������ȡֵ0-255)
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  
*               double * Hue��                  H����(ɫ��)��ȡֵ[0,360]
*               double * Saturation��           S����(���Ͷ�)��ȡֵ[0,100]
*               double * Luminance��            L����(����)��ȡֵ[0,100]
*	����ֵ��	
*               ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRGBtoHSL( unsigned char * ColorImage, int Width, int Height, 
									   double * Hue, double * Saturation, double * Luminance );

/************************************************************************/
/*  ��������	viHSLtoRGB
*	���ܣ�		HSLͼ��ת��ΪRGB��ͨ��ͼ��
*	��ڲ�����	
*               double * Hue��                  H����(ɫ��)��ȡֵ[0,360]
*               double * Saturation��           S����(���Ͷ�)��ȡֵ[0,100]
*               double * Luminance��            L����(����)��ȡֵ[0,100]
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  
*               unsigned char * ColorImage��    ��ɫͼ������(������ȡֵ0-255)
*	����ֵ��	
*               ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHSLtoRGB( double * Hue, double * Saturation, double * Luminance,
									   int Width, int Height, unsigned char * ColorImage );

/************************************************************************/
/*  ��������	viRGBtoHSL2
*	���ܣ�		RGB��ͨ��ͼ��ת��ΪHSLͼ��(������Χ)
*	��ڲ�����	unsigned char * ColorImage��    ԭʼ��ɫͼ������(������ȡֵ0-255)
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  
*               unsigned char * Hue��           H����(ɫ��)��ȡֵ[0,240]
*               unsigned char * Saturation��    S����(���Ͷ�)��ȡֵ[0,240]
*               unsigned char * Luminance��     L����(����)��ȡֵ[0,240]
*	����ֵ��	
*               ��
*   ע�⣺
*               ��Windowsϵͳ�£�HSL�����ķ�Χ��[0,240]���ο�"����"���򣬿��Կ���
*               RGB����|��|������HSL��ɫ��|���Ͷ�|���ȣ�����ϵ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRGBtoHSL2( unsigned char * ColorImage, int Width, int Height, 
									    unsigned char * Hue, unsigned char * Saturation, unsigned char * Luminance );

/************************************************************************/
/*  ��������	viHSLtoRGB2
*	���ܣ�		HSLͼ��(������Χ)ת��ΪRGB��ͨ��ͼ��
*	��ڲ�����
*               unsigned char * Hue��           H����(ɫ��)��ȡֵ[0,240]
*               unsigned char * Saturation��    S����(���Ͷ�)��ȡֵ[0,240]
*               unsigned char * Luminance��     L����(����)��ȡֵ[0,240]
*               int Width, int Height��         ͼ��Ŀ�͸�
*   ���������  
*               unsigned char * ColorImage��    ��ɫͼ������(������ȡֵ0-255)
*	����ֵ��	
*               ��
*   ע�⣺
*               ��Windowsϵͳ�£�HSL�����ķ�Χ��[0,240]���ο�"����"���򣬿��Կ���
*               RGB����|��|������HSL��ɫ��|���Ͷ�|���ȣ�����ϵ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHSLtoRGB2( unsigned char * Hue, unsigned char * Saturation, unsigned char * Luminance,
									    int Width, int Height, unsigned char * ColorImage );

/* 8 ����ͼ�������������Ե��� */

/************************************************************************/
/*  ��������	viEdge
*	���ܣ�		��ͼ����б�Ե��⣨δ����ֵ������
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int Type��                   ��Ե���ķ�����0 -- Sobel��ˮƽ����
*                                                            1 -- Sobel����ֱ��
*                                                            2 -- Sobel��45�ȣ�
*                                                            3 -- Sobel��135�ȣ�
*                                                            4 -- Prewitt��ˮƽ��
*                                                            5 -- Prewitt����ֱ��
*                                                            6 -- Laplacian
*                                                            7 -- Robots��45�Ƚǣ�
*                                                            8 -- Robots��135�Ƚǣ�
*                                                            9 -- ˮƽ�ݶ�
*                                                           10 -- ��ֱ�ݶ�
*   ���������  unsigned char * OutImage:    �Ҷȱ�Եͼ��
*	����ֵ��	��
*   ˵����      (1) ���ͼ��Ϊ�Ҷ�ͼ�񣬱�Եͼ��δ��ֵ��
*               (2) ��������Ϊ��ɫ���߻Ҷ�ͼ�������Ϊ�Ҷ�ͼ��
*               (3) �ⲻ��һ����Ե��ȡ�Ŀ���ʵ�֣����ʱ�õ���double����
*/
/************************************************************************/
VIIMAGE_API void __stdcall viEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
								   int Type, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viCannyEdge
*	���ܣ�		��ͼ�����Canny��Ե��⣨��������˶�ֵ������
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               double sigma��               Gaussian�˲��ı�׼����
*               double dRatioLow��           ����ֵռ����ֵ�İٷ���
*               double dRatioHigh��          ���ڸ���ֵ����ռͼ�����������İٷ���
*   ���������  unsigned char * EdgeImage:   ��Եͼ��
*	����ֵ��	��
*   ˵����      (1) ���ͼ��Ϊ��ֵͼ�񣬱�Եͼ������˶�ֵ����0Ϊ�ڣ�255Ϊ��
*               (2) ��������Ϊ��ɫ���߻Ҷ�ͼ�������Ϊ��ֵͼ��
*               (3) ����Canny���Ӳ����ĵ�����
*               �������͵�ͼ���Ե��ȡ���������£�
*               a) 256 x 256��8���Ҷ�houseͼ��
*                  ���ò�����sigma=0.3, dRatioLow=0.6,dRatioHigh=0.89
*               b) 256 x 256��8���Ҷ�lenaͼ��
*                  ���ò�����sigma=0.6, dRatioLow=0.45-0.5, dRatioHigh=0.75-0.8
*               lenaͼ������ϸ�ڱȽϷḻ����ȥ����ٱ�Ե��ͬʱ����ʹ��Ե���飬
*               ��˲����Ƚ��ѵ�����houseϸ�ڱȽ��٣������Ƚ�����
*/
/************************************************************************/
VIIMAGE_API void __stdcall viCannyEdge( unsigned char * InImage, int Width, int Height, int PixelFormat, double sigma,
									    double dRatioLow, double dRatioHigh, unsigned char * EdgeImage );

/************************************************************************/
/*  ��������	viShenEdge
*	���ܣ�		��ͼ������򿡱�Ե��⣨��������˶�ֵ������ֻ�ԻҶ�ͼ����
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               double Alpha��               ָ���˲������㷨��ϵ����Alpha��0.01-0.99֮��
*   ���������  unsigned char * EdgeImage:   ��Եͼ��
*	����ֵ��	��
*   ע�⣺      �ú���ֻ����Ҷ�ͼ��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viShenEdge( unsigned char * InImage, int Width, int Height,
									   int PixelFormat, double Alpha, unsigned char * EdgeImage );

/************************************************************************/
/*  ��������	viShenEdge2
*	���ܣ�		��ͼ������򿡱�Ե��⣨��������˶�ֵ������
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               double b��                   ָ���˲������㷨��ϵ����һ��ȡֵΪ0.9����
*               double Ratio��               ���ڸ���ֵ��������ռ�����������İٷֱ�
*               int WindowSize��             ��������Ӧ�ݶȵĴ��ڴ�С��һ��ȡֵΪ7
*   ���������  unsigned char * EdgeImage:   ��Եͼ��
*	����ֵ��	��
*   ˵����      (1) ���ͼ��Ϊ��ֵͼ�񣬱�Եͼ������˶�ֵ����0Ϊ�ڣ�255Ϊ��
*               (2) ��������Ϊ��ɫ���߻Ҷ�ͼ�������Ϊ��ֵͼ��
*               (3) ����Shen���Ӳ����ĵ�����
*                   ����Lena 256x256ͼ��Ϊ b = 0.95, ratio = 0.85, WindowSize = 7
*               �ɸĽ���������⣺apply_ISEF_horizontal���˲�������b��ȡֵ��ϸ���ķ���
*/
/************************************************************************/
VIIMAGE_API void __stdcall viShenEdge2( unsigned char * InImage, int Width, int Height, int PixelFormat, double b,
									    double Ratio, int WindowSize, unsigned char * EdgeImage );

/************************************************************************/
/*  ��������	viLoGEdge
*	���ܣ�		LOG���ӱ�Ե���(�����ֵͼ��)
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int Type��                   5 --- 5x5ģ�壨ȱʡ����9 --- 9x9ģ��
*               int Threshold��              ��ֵ��0 --- �Զ���ֵ��1---255 �˹���ֵ
*   ���������  unsigned char * EdgeImage:   ��Եͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viLoGEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
									  int Type, int Threshold, unsigned char * EdgeImage );

/************************************************************************/
/*  ��������	viKirschEdge
*	���ܣ�		Kirsch���ӱ�Ե��⣨���������ӣ�
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int Thres��                  ������ֵ��0-255��
*   ���������  unsigned char * EdgeImage:   ��Եͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viKirschEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
									     int Thres, unsigned char * EdgeImage );

/************************************************************************/
/*  ��������	viWallisEdge
*	���ܣ�		Wallis���ӱ�Ե��⣨�����Զ������ӣ�
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int Thres��                  ������ֵ��1-255������<0�����Զ�ѡ����ֵ��=0������Ҷ�ͼ��
*   ���������  unsigned char * EdgeImage:   ��Եͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viWallisEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
										 int Thres, unsigned char * EdgeImage );

/************************************************************************/
/*  ��������	viFastVerticalEdge
*	���ܣ�		���ٴ�ֱ��Ե���dI/dx (����Ҷ�ͼ��)
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int Type��                   1 --- Sobel��0 --- Previtt������[-1 0 1]
*   ���������  int * EdgeImage:             ��Ե����
*	����ֵ��	��
*   ˵����      ����viFastVerticalEdge(), viFastHorizontalEdge()���Լ����ݶȷ���ͷ�ֵ
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastVerticalEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   int Type, int * EdgeImage );

/************************************************************************/
/*  ��������	viFastHorizontalEdge
*	���ܣ�		����ˮƽ��Ե���dI/dy (����Ҷ�ͼ��)
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int Type��                   1 --- Sobel��0 --- Previtt������[-1 0 1]'
*   ���������  int * EdgeImage:             ��Ե����
*	����ֵ��	��
*   ˵����      ����viFastVerticalEdge(), viFastHorizontalEdge()���Լ����ݶȷ���ͷ�ֵ
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastHorizontalEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
											     int Type, int * EdgeImage );

/* 9 ����ͼ������������ǵ��� */

/************************************************************************/
/*  ��������	viHarrisCorner
*	���ܣ�		��ͼ�����Harris�ǵ���
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               double Sigma��               ����ǵ���Gauss�����ķ���(ȱʡ2.0)
*               double Alpha��               ����ǵ���Alphaֵ(ȱʡ0.04)
*               double Threshold��           �ǵ�����ֵ(ȱʡ0.0)
*               int Radius��                 ͼ��ƽ���뾶(ȱʡ2������ֵ>50��<1���򲻽���ͼ��ƽ��)
*               int UseMorph��               �Ƿ���з����ֵ���ƣ�1 -- ʹ�ã�0 -- ��ʹ��
*   ���������  unsigned char * CornerImage: �ǵ�ͼ��
*	����ֵ��	��
*   ˵����      (1) ���͵�ͼ��ǵ���ȡ�Ĳ������£�
*               Sigma = 2.0; Radius = 2; Alpha = 0.04; Threshold = 0; UseMorph = 1
*               (2) �ó���Ϊһ������ʵ�֣��ٶȽ���
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHarrisCorner( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										   double Sigma, double Alpha, double Threshold, int Radius, int UseMorph,
								           unsigned char * CornerImage );

/************************************************************************/
/*  ��������	viMoravecCorner
*	���ܣ�		��ͼ�����Moravec�ǵ���
*	��ڲ�����	unsigned char * InImage��    �����ͼ�����ݣ����ڻҶ�ͼ���СΪWxH�ֽڣ�
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int w��                      �������Ȥ������򴰿ڣ�wΪ3-15���������
*               int Threshold��              �ǵ�����ֵ(ȱʡ0)
*   ���������  unsigned char * CornerImage: �ǵ�ͼ��
*	����ֵ��	��
*   ˵����      ���͵�ͼ��ǵ���ȡ�Ĳ������£�
*               w = 5; Threshold = 0
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMoravecCorner( unsigned char * InImage, int Width, int Height, int PixelFormat,
										    int w, int Threshold, unsigned char * CornerImage );

/* 10 ����ͼ��������ͼ��ƽ�� */

/************************************************************************/
/*  ��������	viAvgSmoothing
*	���ܣ�		��ͼ����о�ֵƽ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int w, h��                   ͼ���ֵƽ�����ڴ�СΪw x h
*               int Thres��                  ��ֵ��<= 0 -- ��ֵ�����м�ֵ��
*                                            > 0 -- ��ֵ������ֵʱ���������
*   ���������  unsigned char * OutImage:    ��ǿ���ͼ��
*	����ֵ��	��
*   ˵��:       �������û���ͼ���������˼���
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAvgSmoothing( unsigned char * InImage, int Width, int Height, 
										   int PixelFormat, int w, int h, int Thres, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viGaussianSmoothing
*	���ܣ�		��ͼ����и�˹����ͬ��ƽ��
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               double Sigma��               Gaussian�����ķ���(ȱʡΪ1.5)������ƽ�����ڿ��
*               int rounds��                 ƽ���Ĵ���
*   ���������  unsigned char * OutImage:    ƽ�����ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianSmoothing( unsigned char * InImage, int Width, int Height,
											    int PixelFormat, double Sigma, int rounds, 
												unsigned char * OutImage );

/************************************************************************/
/*  ��������	viGaussianSmoothing2
*	���ܣ�		��ͼ����и�˹����ͬ��ƽ��������һά��������ά�����
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int w��                      Gaussianƽ�����ڿ��(1-49������)
*               int rounds��                 ƽ���Ĵ���
*   ���������  unsigned char * OutImage:    ƽ�����ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianSmoothing2( unsigned char * InImage, int Width, int Height,
											     int PixelFormat, int w, int rounds, 
												 unsigned char * OutImage );

/************************************************************************/
/*  ��������	viGaussianSmoothing3
*	���ܣ�		��ͼ����и�˹����ͬ��ƽ�������õ����˲�����
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               double Sigma��               Gaussian�����ķ���(ȱʡΪ1.5)������ƽ�����ڿ��
*               int rounds��                 ƽ���Ĵ���
*   ���������  unsigned char * OutImage:    ƽ�����ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianSmoothing3( unsigned char * InImage, int Width, int Height,
											     int PixelFormat, double Sigma, int rounds, 
												 unsigned char * OutImage );

/************************************************************************/
/*  ��������	viPMSmoothing
*	���ܣ�		��ͼ����и�������ƽ��(Perona-Malik��������ƽ��)
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int gType��                  ��ɢ��������(0 - ����������1 - ָ������(ȱʡֵ)
*               double K��                   ��ɢ����(1-255)����gType�������Ӧ
*               double l��                   ��һ��ϵ����ȡֵ��Χ��0-0.25��һ��ȡ0.25
*               int rounds��                 ƽ���Ĵ���
*   ���������  unsigned char * OutImage:    ƽ�����ͼ��
*	����ֵ��	��
*   ˵��:       һ�����ֵ��
*               gType = 0, K = 4, l = 0.20
*/
/************************************************************************/
VIIMAGE_API void __stdcall viPMSmoothing( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										  int gType, double K, double l, int rounds, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viMediumFiltering
*	���ܣ�		��ͼ�������ֵ�˲�
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ��������24��8
*               int w, h��                   ͼ���˲����ڴ�СΪw x h�����10x10
*               unsigned char * Mask��       �˲����ڵ���ģ��
*               ����λ���ϵ�ֵΪ0 --- ��Ӧ���ز��μ��˲�����0 --- ��Ӧ���زμ��˲�
*   ���������  unsigned char * OutImage:    �˲����ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMediumFiltering( unsigned char * InImage, int Width, int Height, int PixelFormat, 
											  int w, int h, unsigned char * Mask, unsigned char * OutImage );

/* 11 ����ͼ��������ͼ����ǿ */

/************************************************************************/
/*  ��������	viGammaCorrect
*	���ܣ�		��ͼ�����GammaУ��
*	��ڲ�����	unsigned char * InImage��     �����ͼ������
*               int Width��                   ͼ���������
*               int Height��                  ͼ��ߣ�������
*               int PixelFormat��             ��������24��8
*               float rGamma, gGamma, bGamma����ͨ����Gammaֵ��0.2-5֮�䣩
*               float iGamma��                �Ҷ�Gammaֵ��0.2-5֮�䣩
*                                             ��������ĸ�Gammaֵȡ����PixelFormat
*   ���������  unsigned char * OutImage:     GammaУ�����ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGammaCorrect( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										   float rGamma, float gGamma, float bGamma, float iGamma,
										   unsigned char * OutImage );

/************************************************************************/
/*  ��������	viSharpening
*	���ܣ�		��ͼ�����Laplacian����ǿ
*	��ڲ�����	unsigned char * InImage��     �����ͼ������
*               int Width��                   ͼ���������
*               int Height��                  ͼ��ߣ�������
*               int PixelFormat��             ��������24��8
*               int Type��                    �����ͣ�Laplacian���Ӳ��죺
*                                             0 --- [0 -1 0; -1 4 -1; 0 -1 0]
*                                             1 --- [-1 -1 -1; -1 8 -1; -1 -1 -1] 
*   ���������  unsigned char * OutImage:     ��ǿ���ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSharpening( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										 int Type, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viHistogramCorrect
*	���ܣ�		��ͼ�����ֱ��ͼ����
*	��ڲ�����	unsigned char * InImage��     �����ͼ������
*               int Width��                   ͼ���������
*               int Height��                  ͼ��ߣ�������
*               int PixelFormat��             �������ͣ�24��8��
*               int Type��                    ֱ��ͼ�������ͣ�
*                                             0 --- ��YCrCb���Y������
*                                             1 --- ��R��G��B�������ֱ���
*               int * dHist��                 ����ֱ��ͼ�������ΪNULL��������һ��256��BIN
*                                             ������ֱ��ͼ������ϵͳ�Զ���ֱ��ͼ���⻯
*   ���������  unsigned char * OutImage:     ֱ��ͼ�������ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHistogramCorrect( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   int Type, int * dHist, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viHistogramEqu
*	���ܣ�		��ͼ�����ֱ��ͼ���⻯
*	��ڲ�����	unsigned char * InImage��     �����ͼ������
*               int Width��                   ͼ���������
*               int Height��                  ͼ��ߣ�������
*               int PixelFormat��             �������ͣ�24��8��
*               int Type��                    ֱ��ͼ�������ͣ�
*                                             0 --- ��YCrCb���Y������
*                                             1 --- ��R��G��B�������ֱ���
*   ���������  unsigned char * OutImage:     ֱ��ͼ�������ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHistogramEqu( unsigned char * InImage, int Width, int Height, int PixelFormat,
										   int Type, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viGainOffsetCorrect
*	���ܣ�	    ͼ�������/ƫ������
*	��ڲ�����	unsigned char * InImage��     �����ͼ������
*               int Width��                   ͼ���������
*               int Height��                  ͼ��ߣ�������
*               int PixelFormat��             �������ͣ�24��8��
*               int Rmin��                    ����ͼ��Ҷ���Сֵ
*               int Rmax��                    ����ͼ��Ҷ����ֵ
*               int Dmin��                    ���ͼ��Ҷ���Сֵ��Ϊһ��0---255������ֵ
*               int Dmax��                    ���ͼ��Ҷ����ֵ����Χ0---255
*                                             Gain = (Dmax-Offset)/(Rmax-Rmin)��Ϊ����
*   ���������  unsigned char * OutImage:     ֱ��ͼ�������ͼ��
*	����ֵ��	��
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGainOffsetCorrect( unsigned char * InImage, int Width, int Height, int PixelFormat,
											    int Rmin, int Rmax, int Dmin, int Dmax, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viFrequencyFiltering
*	���ܣ�		��ͼ�����Ƶ�����˲�
*
*                       1  D<= D0               1                     -D(u,v)^2/2D0^2
*       ��ͨ��  H(u,v)=          ; H(u,v)=------------------; H(u,v)=e
*                       0  D> D0           1+[D(u,v)/D0]^2n
*
*                       0  D<= D0               1                       -D(u,v)^2/2D0^2
*       ��ͨ��  H(u,v)=          ; H(u,v)=------------------; H(u,v)=1-e
*                       1  D> D0           1+[D0/D(u,v)]^2n
*
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int FilterType��             �˲�������
*                                            0 - �����˲�����ȥֱ������
*                                            1 - ILPF��2 - BLPF��3 - GLPF
*                                            4 - IHPF��5 - BHPF��6 - GHPF
*               int D0��                     �˲��뾶D0(Ϊһ����ֱ�0---10000)
*               int n��                      Butterworth�˲����Ľ���(>= 1)       
*   ���������  unsigned char * OutImage��   �˲����ͼ��
*	����ֵ��	��
*   ˵����
*               ����ͼ��ֻ��Ϊ8λ�Ҷ�ͼ�񡣲���nֻ��Butterworth�˲�����Ч
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFrequencyFiltering( unsigned char * InImage, int Width, int Height,
												 int FilterType, int D0, int n, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viFastFrequencyFiltering
*	���ܣ�		��ͼ����п���Ƶ�����˲�������FFT��
*
*                       1  D<= D0               1                     -D(u,v)^2/2D0^2
*       ��ͨ��  H(u,v)=          ; H(u,v)=------------------; H(u,v)=e
*                       0  D> D0           1+[D(u,v)/D0]^2n
*
*                       0  D<= D0               1                       -D(u,v)^2/2D0^2
*       ��ͨ��  H(u,v)=          ; H(u,v)=------------------; H(u,v)=1-e
*                       1  D> D0           1+[D0/D(u,v)]^2n
*
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int FilterType��             �˲�������
*                                            0 - �����˲�����ȥֱ������
*                                            1 - ILPF��2 - BLPF��3 - GLPF
*                                            4 - IHPF��5 - BHPF��6 - GHPF
*               int D0��                     �˲��뾶D0(Ϊһ����ֱ�0---10000)
*               int n��                      Butterworth�˲����Ľ���(>= 1)       
*   ���������  unsigned char * OutImage��   �˲����ͼ��
*	����ֵ��	��
*   ˵����
*               ����ͼ��ֻ��Ϊ8λ�Ҷ�ͼ�񡣲���nֻ��Butterworth�˲�����Ч
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastFrequencyFiltering( unsigned char * InImage, int Width, int Height,
													 int FilterType, int D0, int n, unsigned char * OutImage );

/* 12 ����ͼ��������ͼ��任 */

/************************************************************************/
/*  ��������	viFDFT1Df
*	���ܣ�		��һά���н���Fourier���任
*	��ڲ�����	double * xRe��               �������е�ʵ��
*               double * xIm��               �����鲿
*               int n��                      ���г���
*   ���������  double * yRe��               �任������е�ʵ��
*               double * yIm��               �任������е��鲿
*	����ֵ��	��
*   ˵��:       �����������˿���FFT�������ܶ���������н��п��ٱ任
*               ע�����г����� < 65537 
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFDFT1Df( double * xRe, double * xIm, int n,
									  double * yRe, double * yIm );

/************************************************************************/
/*  ��������	viIDFT1Df
*	���ܣ�		��һά���н���Fourier���任
*	��ڲ�����	double * xRe��               �������е�ʵ��
*               double * xIm��               �����鲿
*               int n��                      ���г���
*   ���������  double * yRe��               ���任������е�ʵ��
*               double * yIm��               ���任������е��鲿
*	����ֵ��	��
*   ˵��:       �����������˿���FFT�������ܶ���������н��п��ٱ任
*               ע�����г����� < 65537 
*/
/************************************************************************/
VIIMAGE_API void __stdcall viIDFT1Df( double * xRe, double * xIm, int n,
									  double * yRe, double * yIm );

/************************************************************************/
/*  ��������	viFFT2D
*	���ܣ�		��ͼ�����FFT�任
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int OutType��                0 --- ���ʵ��/�鲿��ȱʡ��
*                                            1 --- �����ֵ/��λ
*   ���������  double * RAImage:            �任���ͼ���ʵ��/��ֵ
*               double * IPImage:            �任���ͼ����鲿/��λ
*	����ֵ��	> 0 �任��ȷ��<= 0 δ���б任
*   ˵��:       ������Ҫ������ͼ��Ϊ8λ�Ҷ�ͼ���ҿ���Ϊ2���ݴ�
*/
/************************************************************************/
VIIMAGE_API int __stdcall viFFT2D( unsigned char * InImage, int Width, int Height,
								   int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  ��������	viFFT2Df
*	���ܣ�		��ͼ�����FFT�任(���������)
*	��ڲ�����	double * RealData��          ���ݿ�ʵ��
*               double * ImagData��          ���ݿ��鲿
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int OutType��                0 --- ���ʵ��/�鲿��ȱʡ��
*                                            1 --- �����ֵ/��λ
*   ���������  double * RAImage:            �任���ͼ���ʵ��/��ֵ
*               double * IPImage:            �任���ͼ����鲿/��λ
*	����ֵ��	> 0 �任��ȷ��<= 0 δ���б任
*   ˵��:       ������Ҫ������ͼ��Ϊ8λ�Ҷ�ͼ���ҿ���Ϊ2���ݴ�
*/
/************************************************************************/
VIIMAGE_API int __stdcall viFFT2Df( double * RealData, double * ImagData, int Width, int Height,
								    int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  ��������	viIFFT2D
*	���ܣ�		��ͼ�����FFT���任
*	��ڲ�����	double * RAImage:            FFT�任���ͼ���ʵ��/��ֵ
*               double * IPImage:            FFT�任���ͼ����鲿/��λ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int InType��                 �����������ͣ�
*                                            0 --- ʵ��/�鲿��ȱʡ��
*                                            1 --- ��ֵ/��λ
*   ���������  unsigned char * OutImage��   ���ͼ������
*	����ֵ��	> 0 ���任��ȷ��<= 0 δ���з��任
*   ˵��:       ���������ͼ��Ϊ8λ�Ҷ�ͼ���ҿ���Ϊ2���ݴ�
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIFFT2D( double * RAImage, double * IPImage, int Width, int Height,
								    int InType, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viIFFT2Df
*	���ܣ�		��ͼ�����FFT���任(���������)
*	��ڲ�����	double * RAImage:            FFT�任���ͼ���ʵ��/��ֵ
*               double * IPImage:            FFT�任���ͼ����鲿/��λ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int InType��                 �����������ͣ�
*                                            0 --- ʵ��/�鲿��ȱʡ��
*                                            1 --- ��ֵ/��λ
*   ���������  unsigned char * RealData��   ���ͼ������ʵ��
*               unsigned char * ImagData��   ���ͼ�������鲿
*	����ֵ��	> 0 ���任��ȷ��<= 0 δ���з��任
*   ˵��:       ���������ͼ��Ϊ8λ�Ҷ�ͼ���ҿ���Ϊ2���ݴ�
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIFFT2Df( double * RAImage, double * IPImage, int Width, int Height,
								     int InType, double * RealData, double * ImagData );

/************************************************************************/
/*  ��������	viDFT2D
*	���ܣ�		��ͼ�����DFT�任
*	��ڲ�����	unsigned char * InImage��    �����ͼ������
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int OutType��                0 --- ���ʵ��/�鲿��ȱʡ��
*                                            1 --- �����ֵ/��λ
*   ���������  double * RAImage:            �任���ͼ���ʵ��/��ֵ
*               double * IPImage:            �任���ͼ����鲿/��λ
*	����ֵ��	> 0 �任��ȷ��<= 0 δ���б任
*   ˵��:       ������Ҫ������ͼ��Ϊ8λ�Ҷ�ͼ��ͼ�������Ҫ��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viDFT2D( unsigned char * InImage, int Width, int Height,
								   int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  ��������	viDFT2Df
*	���ܣ�		��ͼ�����DFT�任(���������)
*	��ڲ�����	double * RealData��          �����ͼ������ʵ��
*               double * ImagData��          �����ͼ�������鲿
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int OutType��                0 --- ���ʵ��/�鲿��ȱʡ��
*                                            1 --- �����ֵ/��λ
*   ���������  double * RAImage:            �任���ͼ���ʵ��/��ֵ
*               double * IPImage:            �任���ͼ����鲿/��λ
*	����ֵ��	> 0 �任��ȷ��<= 0 δ���б任
*   ˵��:       ������Ҫ������ͼ��Ϊ8λ�Ҷ�ͼ��ͼ�������Ҫ��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viDFT2Df( double * RealData, double * ImagData, int Width, int Height,
								    int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  ��������	viIDFT2D
*	���ܣ�		��ͼ�����DFT���任
*	��ڲ�����	double * RAImage:            DFT�任���ͼ���ʵ��/��ֵ
*               double * IPImage:            DFT�任���ͼ����鲿/��λ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int InType��                 �����������ͣ�
*                                            0 --- ʵ��/�鲿��ȱʡ��
*                                            1 --- ��ֵ/��λ
*   ���������  unsigned char * OutImage��   ���ͼ������
*	����ֵ��	> 0 ���任��ȷ��<= 0 δ���з��任
*   ˵��:       ���������ͼ��Ϊ8λ�Ҷ�ͼ�󣬶�ͼ�������Ҫ��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIDFT2D( double * RAImage, double * IPImage, int Width, int Height,
								    int InType, unsigned char * OutImage );

/************************************************************************/
/*  ��������	viIDFT2Df
*	���ܣ�		��ͼ�����DFT���任(���������)
*	��ڲ�����	double * RAImage:            DFT�任���ͼ���ʵ��/��ֵ
*               double * IPImage:            DFT�任���ͼ����鲿/��λ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int InType��                 �����������ͣ�
*                                            0 --- ʵ��/�鲿��ȱʡ��
*                                            1 --- ��ֵ/��λ
*   ���������  double * RealData��          ���ͼ������ʵ��
*               double * ImagData��          ���ͼ�������鲿
*	����ֵ��	> 0 ���任��ȷ��<= 0 δ���з��任
*   ˵��:       ���������ͼ��Ϊ8λ�Ҷ�ͼ�󣬶�ͼ�������Ҫ��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIDFT2Df( double * RAImage, double * IPImage, int Width, int Height,
								     int InType, double * RealData, double * ImagData );

/************************************************************************/
/*  ��������	viDFT2Df2
*	���ܣ�		��ͼ����п���DFT�任(���������)
*	��ڲ�����	double * RealData��          �����ͼ������ʵ��
*               double * ImagData��          �����ͼ�������鲿
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int OutType��                0 --- ���ʵ��/�鲿��ȱʡ��
*                                            1 --- �����ֵ/��λ
*   ���������  double * RAImage:            �任���ͼ���ʵ��/��ֵ
*               double * IPImage:            �任���ͼ����鲿/��λ
*	����ֵ��	> 0 �任��ȷ��<= 0 δ���б任
*   ˵��:       ������Ҫ������ͼ��Ϊ8λ�Ҷ�ͼ��ͼ�������Ҫ��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viDFT2Df2( double * RealData, double * ImagData, int Width, int Height,
									 int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  ��������	viIDFT2Df2
*	���ܣ�		��ͼ����п���DFT���任(���������)
*	��ڲ�����	double * RAImage:            DFT�任���ͼ���ʵ��/��ֵ
*               double * IPImage:            DFT�任���ͼ����鲿/��λ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int InType��                 �����������ͣ�
*                                            0 --- ʵ��/�鲿��ȱʡ��
*                                            1 --- ��ֵ/��λ
*   ���������  double * RealData��          ���ͼ������ʵ��
*               double * ImagData��          ���ͼ�������鲿
*	����ֵ��	> 0 ���任��ȷ��<= 0 δ���з��任
*   ˵��:       ���������ͼ��Ϊ8λ�Ҷ�ͼ�󣬶�ͼ�������Ҫ��
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIDFT2Df2( double * RAImage, double * IPImage, int Width, int Height,
									  int InType, double * RealData, double * ImagData );

/************************************************************************/
/*  ��������	viFastDCT8x8
*	���ܣ�		��8x8�Ҷ�ͼ�����п���DCT�任
*	��ڲ�����	unsigned char * Image8x8:    ԭʼ8x8ͼ��
*   ���������  double * Coeff8x8��          ���8x8 DCT�任ϵ��
*	����ֵ��	��
*   ˵��:       ����������/�����Ϊ8x8�����ݿ飬������߶���Ϊ8
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastDCT8x8( unsigned char * Image8x8, double * Coeff8x8 );

/************************************************************************/
/*  ��������	viFastIDCT8x8
*	���ܣ�		��8x8���ݿ���п���DCT���任
*	��ڲ�����	double * Coeff8x8��          ����8x8 DCT�任ϵ��
*   ���������  unsigned char * Image8x8:    ������任8x8ͼ��
*	����ֵ��	��
*   ˵��:       ����������/�����Ϊ8x8�����ݿ飬������߶���Ϊ8
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastIDCT8x8( double * Coeff8x8, unsigned char * Image8x8 );

/************************************************************************/
/*  ��������	viWaveletDecom2D
*	���ܣ�		�Զ�ά���ݿ����С���ֽ⣨Mallat�㷨��
*	��ڲ�����	double * image:        ͼ�����ݿ�
*               int width, height:     ͼ����ߣ���Ϊ2�ı���(�ο�˵������)
*               double * Hi:           �ֽ��ͨ�˲���ϵ��
*               int n_Hi:              �ֽ��ͨ�˲�������
*               double * Lo:           �ֽ��ͨ�˲���ϵ��
*               int n_Lo:              �ֽ��ͨ�˲�������
*               int levels:            С���ֽ⼶��
*   ���������  double * wavelet_data: С���ֽ�������
*	����ֵ��	��άС���ֽ����
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2^levels * M������MΪ������������
*               levels>=1������������һ������ǰ����������ݽ��зֽ⣬β������ԭ��
*               wavelet_data����������Ϊ����2���ֽ�Ϊ������
*                    A2 A2 H2 H2 H1 H1 H1 H1 
*                    A2 A2 H2 H2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaveletDecom2D(  double * image, int width, int height,
										   	 double * Hi, int n_Hi, double * Lo, int n_Lo,
											 int levels, double * wavelet_data );

/************************************************************************/
/*  ��������	viWaveletRecon2D
*	���ܣ�		�Զ�ά���ݿ����С���ع���Mallat�㷨��
*	��ڲ�����	double * wavelet_data: С��ϵ��
*               int width, height:     ͼ����ߣ���Ϊ2�ı���(�ο�˵������)
*               double * Hi:           �ع���ͨ�˲���ϵ��
*               int n_Hi:              �ع���ͨ�˲�������
*               double * Lo:           �ع���ͨ�˲���ϵ��
*               int n_Lo:              �ع���ͨ�˲�������
*               int levels:            С���ع�����
*   ���������  double * image:        �ع�ͼ�����ݿ�
*	����ֵ��	��άС���ع�����
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2^levels * M������MΪ������������
*               levels>=1������������һ������ǰ����������ݽ����ع���β������ԭ��
*               wavelet_data����������Ϊ����2���ֽ�Ϊ������
*                    A2 A2 H2 H2 H1 H1 H1 H1 
*                    A2 A2 H2 H2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaveletRecon2D(  double * wavelet_data, int width, int height,
										   	 double * Hi, int n_Hi, double * Lo, int n_Lo,
											 int levels, double * image );

/************************************************************************/
/*  ��������	viWaveletDecom2DR
*	���ܣ�		�Զ�ά���ݿ����һ��С���ֽ��Ҳ������²�����Mallat�㷨��
*	��ڲ�����	double * image:        ͼ�����ݿ�
*               int width, height:     ͼ����ߣ���Ϊ2�ı���
*               double * Hi:           �ֽ��ͨ�˲���ϵ��
*               int n_Hi:              �ֽ��ͨ�˲�������
*               double * Lo:           �ֽ��ͨ�˲���ϵ��
*               int n_Lo:              �ֽ��ͨ�˲�������
*   ���������  double * approximation: С���ֽ��ıƽ�����
*               double * detail_h:     С���ֽ���ˮƽϸ��
*               double * detail_v:     С���ֽ��Ĵ�ֱϸ��
*               double * detail_d:     С���ֽ��ĶԽ�ϸ��
*	����ֵ��	��άС���ֽ������Ϊ1��
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2M������MΪ����������
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaveletDecom2DR(  double * image, int width, int height,
										   	  double * Hi, int n_Hi, double * Lo, int n_Lo,
											  double * approximation, double * detail_h,
											  double * detail_v, double * detail_d );

/************************************************************************/
/*  ��������	viWaveletRecon2DR
*	���ܣ�		�Զ�ά���ݿ����һ��С���ع��Ҳ����в�ֵ��Mallat�㷨��
*	��ڲ�����	double * approximation: С���ƽ�����
*               double * detail_h:      С��ˮƽϸ��
*               double * detail_v:      С����ֱϸ��
*               double * detail_d:      С���Խ�ϸ��
*               int width, height:      ͼ����ߣ���Ϊ2�ı���
*               double * Hi:            �ع���ͨ�˲���ϵ��
*               int n_Hi:               �ع���ͨ�˲�������
*               double * Lo:            �ع���ͨ�˲���ϵ��
*               int n_Lo:               �ع���ͨ�˲�������
*   ���������  double * image:         �ع�ͼ�����ݿ�
*	����ֵ��	��άС���ع�������Ϊ1��
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2M������MΪ����������
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaveletRecon2DR( double * approximation, double * detail_h,
											 double * detail_v, double * detail_d, 
											 int width, int height,
										   	 double * Hi, int n_Hi, double * Lo, int n_Lo,
											 double * image );

/************************************************************************/
/*  ��������	viLifting53Decom2D
*	���ܣ�		�Զ�ά���ݿ����lifting 5/3С���ֽ⣨�����������ı任��
*	��ڲ�����	int * image:           ͼ�����ݿ�
*               int width, height:     ͼ����ߣ���Ϊ2�ı������ο�˵�����֣�
*               int levels:            �ֽ����
*   ���������  int * wavelet_data:    ����lifting 5/3С���ֽ���ϵ��
*	����ֵ��	��άС���ֽ����
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2^levels * M������MΪ������������
*               levels>=1������������һ������ǰ����������ݽ����ع���β������ԭ��
*               wavelet_data����������Ϊ����2���ֽ�Ϊ������
*                    A2 A2 H2 H2 H1 H1 H1 H1 
*                    A2 A2 H2 H2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viLifting53Decom2D(  int * image, int width, int height,
										   	   int levels, int * wavelet_data );

/************************************************************************/
/*  ��������	viLifting53Recon2D
*	���ܣ�		�Զ�ά���ݿ����lifting 5/3С���ع��������������ı任��
*	��ڲ�����	int * wavelet_data:    ����lifting 5/3С���ֽ���ϵ��
*               int width, height:     ͼ����ߣ���Ϊ2�ı������ο�˵�����֣�
*               int levels:            �ع�����
*   ���������  int * image:           �ع�ͼ�����ݿ�
*	����ֵ��	��άС���ع�����
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2^levels * M������MΪ������������
*               levels>=1������������һ������ǰ����������ݽ����ع���β������ԭ��
*               wavelet_data����������Ϊ����2���ֽ�Ϊ������
*                    A2 A2 H2 H2 H1 H1 H1 H1 
*                    A2 A2 H2 H2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viLifting53Recon2D(  int * wavelet_data, int width, int height,
										   	   int levels, int * image );

/************************************************************************/
/*  ��������	viSplusPDecom2D
*	���ܣ�		�Զ�ά���ݿ����S+P�ֽ⣨�����������ı任��
*	��ڲ�����	int * I:               ͼ�����ݿ�
*               int width, height:     ͼ����ߣ���Ϊ2�ı������ο�˵�����֣�
*               int n_levels:          �ֽ����
*               int predictor_type:    Ԥ�������ͣ���Ϊ1��2��3����A��B��C���࣬ȱʡB��
*   ���������  int * SP:              ����S+P�ֽ���ϵ��
*	����ֵ��	��άS+P�ֽ����
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2^levels * M������MΪ������������
*               levels>=1������������һ������ǰ����������ݽ����ع���β������ԭ��
*               SP����������Ϊ����2���ֽ�Ϊ������
*                    A2 A2 H2 H2 H1 H1 H1 H1 
*                    A2 A2 H2 H2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viSplusPDecom2D(  int * I, int width, int height,
										   	int n_levels, int predictor_type, int * SP );

/************************************************************************/
/*  ��������	viSplusPRecon2D
*	���ܣ�		�Զ�ά���ݿ����S+P�ع��������������ı任��
*	��ڲ�����	int * SP:              ����S+P�ֽ���ϵ��
*               int width, height:     ͼ����ߣ���Ϊ2�ı������ο�˵�����֣�
*               int n_levels:          �ֽ����
*               int predictor_type:    Ԥ�������ͣ���Ϊ1��2��3����A��B��C���࣬ȱʡB��
*   ���������  int * I:               �ع�ͼ�����ݿ�
*	����ֵ��	��άS+P�ع�����
*   ˵��:       �������������ݿ�Ŀ���Ϊ 2^levels * M������MΪ������������
*               levels>=1������������һ������ǰ����������ݽ����ع���β������ԭ��
*               SP����������Ϊ����2���ֽ�Ϊ������
*                    A2 A2 H2 H2 H1 H1 H1 H1 
*                    A2 A2 H2 H2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V2 V2 D2 D2 H1 H1 H1 H1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*                    V1 V1 V1 V1 D1 D1 D1 D1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viSplusPRecon2D(  int * SP, int width, int height,
										   	int n_levels, int predictor_type, int * I );

/************************************************************************/
/*  ��������	viCensusTransform
 *	���ܣ�		��ͼ�����CensusTransform
 *	��ڲ�����	unsigned char * InImage��    �����ͼ������
 *              int Width��                  ͼ���������
 *              int Height��                 ͼ��ߣ�������
 *  ���������  int * OutData��              �任��Ľ��
 *	����ֵ��	��
 *  ˵��:       (1) ����ͼ�����Ϊ8λ�Ҷ�ͼ��������ݷ�ΧΪ0 - 510��511�֡�
 *              000000000��111111111Ϊһ�ֽṹ����Ϊ0
 *              (2) �������û���ͼ���������˼���
 *              (3) ������δ�Ա߽���д����߽�ǿ��Ϊ0
 */
/************************************************************************/
void viCensusTransform( unsigned char * InImage, int Width, int Height, 
					    int * OutData );

/* 13 ģʽʶ������ģ��ƥ�� */

/************************************************************************/
/*  ��������	viSAD
*	���ܣ�		������ͬ�ߴ��ͼ���SADֵ��sum of the absolute difference��
*	��ڲ�����	unsigned char * Image1��     ����ͼ��1
*               unsigned char * Image2��     ����ͼ��2
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ͼ���ʽ8����24
*	����ֵ��    sadֵ��< 0��ʾ�����д���
*/
/************************************************************************/
VIIMAGE_API double __stdcall viSAD( unsigned char * Image1, unsigned char * Image2, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  ��������	viSSD
*	���ܣ�		������ͬ�ߴ��ͼ���SSDֵ��sum of the squared difference��
*	��ڲ�����	unsigned char * Image1��     ����ͼ��1
*               unsigned char * Image2��     ����ͼ��2
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ͼ���ʽ8����24
*	����ֵ��    ssdֵ��< 0��ʾ�����д���
*/
/************************************************************************/
VIIMAGE_API double __stdcall viSSD( unsigned char * Image1, unsigned char * Image2, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  ��������	viNCC
*	���ܣ�		������ͬ�ߴ��ͼ���NCCֵ��normalized cross-correlation��
*	��ڲ�����	unsigned char * Image1��     ����ͼ��1
*               unsigned char * Image2��     ����ͼ��2
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int PixelFormat��            ͼ���ʽ8����24
*	����ֵ��    NCCֵ
*/
/************************************************************************/
VIIMAGE_API double __stdcall viNCC( unsigned char * Image1, unsigned char * Image2, int Width, int Height, 
								    int PixelFormat );

/* 14 ͼ����������ɫͼ��ָ� */

/************************************************************************/
/*  ��������	viColorBlobExtract
*	���ܣ�		�Բ�ɫͼ����ȡ������ɫ��Blob�ĺ���
*	��ڲ�����	unsigned char * cImage��     �����ɫͼ�񣬱���Ϊ24λ���ɫ
*               int Width��                  ͼ���������
*               int Height��                 ͼ��ߣ�������
*               int R, G, B��                ��ɫ������ɫ������������Ϊ0---255��
*               int dR, dG, dB��             ����ɫ���������ƫ��������(R-dR,R+dR)��Χ����ɫ�����ںϸ�Rɫ
*               bool IfCopy��                �Ƿ�ÿ��Blob���򿽱���BLOBREGION��BlobImage��(trueΪ����)
*   ���������  BLOBREGION **blobregions��   ÿ��blob������Ͻ�����Ϳ���(��Ч������1��ʼ��
*                                            blobregions[0]δ��)
*	����ֵ��    Ѱ�ҵ�������������˳�����blobregions�����У�
*               ��ֵ��ʾ��ȡ����
*   ʹ�÷�����
*      ��1����������һ��ָ�룺BLOBREGION * blobregions;
*	   ��2�����ñ�������        viColorBlobExtract( cImage, Width, Height, R, G, B, dR, dG, dB, false, &blobregions );
*	   ��3�������������ͷ��ڴ棺viFreeBlobRegion( &blobregions );
*   ˵����
*               �ú�������û��blob���������ƣ�����Ϊ2^31��blob��    
*/
/************************************************************************/
VIIMAGE_API int __stdcall viColorBlobExtract( unsigned char * cImage, int Width, int Height, int R, int G, int B, 
											  int dR, int dG, int dB, bool IfCopy, BLOBREGION ** blobregions );

#endif