# ifndef _VIIMAGEAPI_
# define _VIIMAGEAPI_

# define VIIMAGE_API  extern "C" __declspec(dllexport)

//////////////////////////////////////////////////////////////////////////
/* 定义一些数据结构 */

/* 定义二值目标块数据结构 */
# ifndef __BLOBREGION
# define __BLOBREGION

typedef struct _BlobRegion  // Blob区域的定义
{
	int top, left;  // 区域的左上角坐标
	int w, h;       // 区域宽和高
	int tag;        // 保留的tag位，可用于标记或存放周长、面积等数据
	unsigned char * BlobImage;  // 保留的图像块指针，其尺寸为wxh，由应用程序申请和释放该图像内存
} BLOBREGION;

# endif

/* 定义链码数据结构 */
typedef struct _ChainContourObj 
{
	bool IsOutContour;         // 链码类型，true:外轮廓; false:内轮廓
	//	char Type;                 // 链码类型：8链码还是4链码（8或4）
	int x0, y0;                // 链码起始位置，(x,y)
	int ChainLength;           // 链码的长度
	unsigned char * Chain;      // 具体链码编码，逆时针方向8连通
	struct _ChainContourObj * Next;   // 下一个链码标记目标指针
	int Area;                   // 面积，空值
	int Perimeter;              // 周长，空值
	int Left, Right, Top, Bottom;     // 外接矩形，空值
	int tag;                    // 保留未用的变量，空值
	int Xc, Yc;                 // 链码包围区域质心坐标(不是中心坐标)，空值
	double Theta;               // 与垂直方向的夹角，顺时针为正
	int a, b;                   // 最小拟合椭圆的半长轴和半短轴
} ChainContourObj;   // 链码目标对象

//////////////////////////////////////////////////////////////////////////

/* 1 常用信号处理函数 */

/************************************************************************/
/*  函数名：	viMSE
*	功能：		计算图像的MSE（Mean Squared Error）
*	入口参数：	unsigned char * InData：    原始无噪图像数据
*               unsigned char * OutData：   待计算含噪图像数据
*               int Width, int Height：     图像的宽和高
*               int PixelFormat：           像素类型24或8
*	返回值：	double：                    MSE
*/
/************************************************************************/
VIIMAGE_API double __stdcall viMSE( unsigned char * InData, unsigned char * OutData, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  函数名：	viPSNR
*	功能：		计算图像的峰值信噪比（PSNR）
*	入口参数：	unsigned char * InData：    原始无噪图像数据
*               unsigned char * OutData：   待计算含噪图像数据
*               int Width, int Height：     图像的宽和高
*               int PixelFormat：           像素类型24或8
*	返回值：	double：                    PSNR
*/
/************************************************************************/
VIIMAGE_API double __stdcall viPSNR( unsigned char * InData, unsigned char * OutData, int Width, int Height, 
									 int PixelFormat );

/************************************************************************/
/*  函数名：	viSNR
*	功能：		计算图像的信噪比（SNR）
*	入口参数：	unsigned char * InData：    原始无噪图像数据
*               unsigned char * OutData：   待计算含噪图像数据
*               int Width, int Height：     图像的宽和高
*               int PixelFormat：           像素类型24或8
*	返回值：	double：                    SNR
*/
/************************************************************************/
VIIMAGE_API double __stdcall viSNR( unsigned char * InData, unsigned char * OutData, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  函数名：	viSaltPepperNoise
*	功能：		产生Salt&Pepper噪声
*	入口参数：	unsigned char * InData：    原始无噪图像数据
*               int Width, int Height：     图像的宽和高
*               int PixelFormat：           像素类型24或8
*               float percentage：          0---100之间的一个百分比值，加入噪声的百分比
*   出口参数：  unsigned char * OutData：   含噪图像数据
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSaltPepperNoise( unsigned char * InData, int Width, int Height, int PixelFormat, 
											  unsigned char * OutData, float percentage );

/************************************************************************/
/*  函数名：	viGaussianNoise
*	功能：		产生Gaussian噪声
*	入口参数：	unsigned char * InData：    原始无噪图像数据
*               int Width, int Height：     图像的宽和高
*               int PixelFormat：           像素类型24或8
*               float u, sigma：            正态分布的均值和方差(归一化了)
*   出口参数：  unsigned char * OutData：   含噪图像数据
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianNoise( unsigned char * InData, int Width, int Height, int PixelFormat, 
											unsigned char * OutData, float u, float sigma );

/************************************************************************/
/*  函数名：	viMeanAndVariance
*	功能：		计算给定图像的均值和方差
*	入口参数：	unsigned char * InData：    图像数据
*               int Width, int Height：     图像的宽和高
*               int PixelFormat：           像素类型24或8
*   输出参数：  double u, sigma：           图像的均值和方差
*	返回值：	无
*   注意： 当图像为8位灰度图时，该函数计算的是一幅图像的方差与均值；
*          当图像为24位彩色图时，函数计算的是R、G、B三通道的方差与均值
*          若要得到R、G、B各个通道的均值与方差，可将图像分为3个位平面单独计算
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMeanAndVariance( unsigned char * InData, int Width, int Height, int PixelFormat, 
											  double &u, double &sigma );

/* 2 基本图像处理函数：图像的几何变换 */

/************************************************************************/
/*  函数名：	viCalcuIntegralImageI
*	功能：		计算灰度图像的积分图（整型运算版）
*   积分图像定义为：
*    ii(x,y) = sum_{x'<=x,y'<=y} i(x',y')
*
*   积分图的快速实现为：
*    s(x,y) = s(x, y-1)+i(x,y)
*    ii(x,y) = ii(x-1,y)+s(x,y)
*   此处，s(x,y)是第y行的累加和，定义s(x,-1) = 0，且ii(-1,y)=0. 
*   ii(x,y)即为积分图，i(x,y)为原始图像
*  
*	入口参数：	unsigned char * Image：      读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型，必须为8（即256级灰度图）
*   输出参数：  long * IntegralImage:        输出图像须为long型积分灰度图像
*	返回值：	1 --- 成功；-1 --- 计算不成功，返回的积分图无效
*/
/************************************************************************/
VIIMAGE_API int __stdcall viCalcuIntegralImageI( unsigned char * Image, int Width, int Height, int PixelFormat,
												 long * IntegralImage );

/************************************************************************/
/*  宏函数名：	viIntegralRegionArea
*	功能：		通过积分图获得某块区域的灰度值和
*	入口参数：	long * IntegralImage:        输出图像须为long型积分灰度图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int x1, y1, x2, y2：         积分图像的左上和右下坐标
*	返回值：	成功: 所选区域面积; 识别: -1
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIntegralRegionArea( long * IntegralImage, int Width, int Height, 
											    int x1, int y1, int x2, int y2 );

/************************************************************************/
/*  函数名：	viResize
*	功能：		改变图像的尺寸
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               PixelFormat:      PixelFormat为图像像素格式：24为彩色图像，8为灰度图
*               rImage:           尺寸修改后的图像数据块
*               rWidth, rHeight:  修改后的图像宽高
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*                                 2 --- 三线性插值
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viResize( unsigned char * Image, int Width, int Height, int PixelFormat,
									 unsigned char * rImage, int rWidth, int rHeight, int Type );

/************************************************************************/
/*  函数名：	viResizeBinary
*	功能：		改变二值图像的尺寸
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               rImage:           尺寸修改后的图像数据块
*               rWidth, rHeight:  修改后的图像宽高
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*	返回值：	无
*   注意：原始图像为二值图像，0代表背景，255代表前景；缺省插值类型为1
*/
/************************************************************************/
VIIMAGE_API void __stdcall viResizeBinary( unsigned char * Image, int Width, int Height,
										   unsigned char * rImage, int rWidth, int rHeight, int Type );

/************************************************************************/
/*  函数名：	viAffineTransform
*	功能：		仿射变换，基本变换矩阵如下：
*               x'      a11   a12     x     b1
*                   =              *     +  
*               y'      a21   a22     y     b2
*               采用逆向映射：
*               x        1     a22  -a12    x'-b1
*                   =   --- *            * 
*               y        d    -a21   a11    y'-b2
*
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               PixelFormat:      像素位数：8或者24
*               rImage:           变换后的图像数据块
*               rWidth, rHeight:  为变换后的图像宽高
*               a:                变换参数阵(为6个参数，顺序为a11, a12, b1, a21, a22, b2)
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*	返回值：	无
*   注意：      此函数的各种仿射变换均以中心点（Width/2, Height/2）为原点
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAffineTransform( unsigned char * Image, int Width, int Height, int PixelFormat,
											  unsigned char * rImage, int rWidth, int rHeight, double * a, int Type );

/************************************************************************/
/*  函数名：	viAffineTransformBinary
*	功能：		对二值图像的仿射变换，基本变换矩阵如下：
*               x'      a11   a12     x     b1
*                   =              *     +  
*               y'      a21   a22     y     b2
*               采用逆向映射：
*               x        1     a22  -a12    x'-b1
*                   =   --- *            * 
*               y        d    -a21   a11    y'-b2
*
*	入口参数：	Image:            原始图像数据块（0---背景；255---前景）
*               Width, Height:    为图像宽高
*               rImage:           变换后的图像数据块
*               rWidth, rHeight:  为变换后的图像宽高
*               a:                变换参数阵(为6个参数，顺序为a11, a12, b1, a21, a22, b2)
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*	返回值：	无
*   注意：      此函数的各种仿射变换均以中心点（Width/2, Height/2）为原点
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAffineTransformBinary( unsigned char * Image, int Width, int Height, unsigned char * rImage, 
												    int rWidth, int rHeight, double * a, int Type );

/************************************************************************/
/*  函数名：	viRotate
*	功能：		对图像旋转一个角度
*
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               PixelFormat:      像素位数：8或者24
*               rImage:           变换后的图像数据块
*               rWidth, rHeight:  为变换后的图像宽高
*               Theta:            旋转角度（角度为单位，与y轴方向夹角，顺时针为正）
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*	返回值：	无
*   注意：      此函数的各种仿射变换均以中心点（Width/2, Height/2）为原点
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRotate( unsigned char * Image, int Width, int Height, int PixelFormat,
									 unsigned char * rImage, int rWidth, int rHeight, double Theta, int Type );

/************************************************************************/
/*  函数名：	viRotateBinary
*	功能：		对二值图像旋转一个角度
*
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               rImage:           变换后的图像数据块
*               rWidth, rHeight:  为变换后的图像宽高
*               Theta:            旋转角度（角度为单位，与y轴方向夹角，顺时针为正）
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*	返回值：	无
*   注意：      此函数的各种仿射变换均以中心点（Width/2, Height/2）为原点
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRotateBinary( unsigned char * Image, int Width, int Height,
										   unsigned char * rImage, int rWidth, int rHeight, double Theta, int Type );

/************************************************************************/
/*  函数名：	viSkew
*	功能：		对图像某个轴旋转一个角度
*
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               PixelFormat:      像素位数：8或者24
*               rImage:           变换后的图像数据块
*               rWidth, rHeight:  为变换后的图像宽高
*               Theta:            旋转角度（角度为单位，与y/x轴方向夹角，顺时针为正）
*               axis:             0 --- x轴，1 --- y轴
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*	返回值：	无
*   注意：      此函数的各种仿射变换均以中心点（Width/2, Height/2）为原点
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSkew( unsigned char * Image, int Width, int Height, int PixelFormat,
								   unsigned char * rImage, int rWidth, int rHeight, double Theta, 
								   int axis, int Type );

/************************************************************************/
/*  函数名：	viSkewBinary
*	功能：		对二值图像沿某个轴旋转一个角度
*
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               rImage:           变换后的图像数据块
*               rWidth, rHeight:  为变换后的图像宽高
*               Theta:            旋转角度（角度为单位，与y/x轴方向夹角，顺时针为正）
*               axis:             0 --- x轴，1 --- y轴
*               Type:             图像插值类型，0 --- 最近邻插值； 1 --- 双线性插值；
*	返回值：	无
*   注意：      此函数的各种仿射变换均以中心点（Width/2, Height/2）为原点
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSkewBinary( unsigned char * Image, int Width, int Height, 
										 unsigned char * rImage, int rWidth, int rHeight, double Theta, 
										 int axis, int Type );

/************************************************************************/
/*  函数名：	viClipImage
*	功能：		剪取图像一部分
*	入口参数：	Image:            原始图像数据块
*               Width, Height:    为图像宽高
*               PixelFormat:      PixelFormat为图像像素格式：24为彩色图像，8为灰度图
*               cImage:           剪取后的图像数据块
*               int top, left:    剪取后的图像的左上
*               int bottom,right: 右下坐标
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viClipImage( unsigned char * Image, int Width, int Height, int PixelFormat,
									    unsigned char * cImage, int top, int left, int bottom, int right );

/************************************************************************/
/*  函数名：	viPasteImage
*	功能：		将一幅图像粘贴到另一幅图像上去
*	入口参数：	Image:            被粘贴的图像数据块
*               Width, Height:    被粘贴图像宽高
*               PixelFormat:      PixelFormat为图像像素格式：24为彩色图像，8为灰度图
*                                 被粘贴与粘贴图像须颜色位数一致
*               int top, left:    粘贴的起始位置
*               pImage:           粘贴图像数据块
*               int W, H:         粘贴图像的宽高
*	返回值：	无
*   说明：      将pImage粘贴到Image上
*/
/************************************************************************/
VIIMAGE_API void __stdcall viPasteImage( unsigned char * Image, int Width, int Height, int PixelFormat, 
										 int top, int left, unsigned char * pImage, int W, int H );

/* 3 基本图像分析函数：阈值化方法 */

/************************************************************************/
/*  函数名：	viOtsuThreshold
*	功能：		Otsu法对图像进行阈值化
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*   输出参数：  unsigned char * OutImage:    二值化后的图像（为易于显示，值为0或255）
*               int &threshold：             选择出的最佳阈值
*                                            注意: 输出图像须为256级灰度图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viOtsuThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
										    unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  函数名：	viKSWThreshold
*	功能：		KSW法对图像进行阈值化(最大熵法)
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*   输出参数：  unsigned char * OutImage:    二值化后的图像（为易于显示，值为0或255）
*               int &threshold：             选择出的最佳阈值
*                                            注意: 输出图像须为256级灰度图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viKSWThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
										   unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  函数名：	viMeanThreshold
*	功能：		平均值法对图像进行阈值化
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*   输出参数：  unsigned char * OutImage:    二值化后的图像（为易于显示，值为0或255）
*               int &threshold：             选择出的最佳阈值
*                                            注意: 输出图像须为256级灰度图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMeanThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
										    unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  函数名：	viIterateThreshold
*	功能：		迭代法对图像进行阈值化
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*   输出参数：  unsigned char * OutImage:    二值化后的图像（为易于显示，值为0或255）
*               int &threshold：             选择出的最佳阈值
*                                            注意: 输出图像须为256级灰度图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viIterateThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   unsigned char * OutImage, int & threshold );

/************************************************************************/
/*  函数名：	viBinary
*	功能：		人工选择阈值对图像进行二值化
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int threshold：              设定的阈值
*               int Type：                   彩色图像变灰度图像方法
*                                            0 --- 平均，1 --- 视觉特性加权
*   输出参数：  unsigned char * OutImage:    二值化后的图像（为易于显示，值为0或255）
*                                            注意: 输出图像须为256级灰度图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinary( unsigned char * InImage, int Width, int Height, int PixelFormat,
									 unsigned char * OutImage, int threshold, int Type );

/************************************************************************/
/*  函数名：	viDynamicThreshold
*	功能：		动态阈值法对图像进行二值化
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int w,h：                    局部处理窗口的宽和高
*               int Type：                   全局阈值法的方法：0 -- Otsu，1 -- KSW，
*                                                              2 -- 迭代，3 -- 平均值法
*   输出参数：  unsigned char * OutImage:    二值化后的图像（为易于显示，值为0或255）
*                                            注意: 输出图像须为256级灰度图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viDynamicThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   int w, int h, int Type, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viAdaptiveThreshold
*	功能：		自适应阈值法对图像进行二值化
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int NWid：                   宽度方向分割的块数（一般在4-12，缺省为8）
*               float T：                    目标占小区域的百分比（一般在-0.3 --- 0.3，缺省0.15）
*                                            实验表明：当前景目标为暗色，背景为白色时，取正值；反之，负值
*   输出参数：  unsigned char * OutImage:    二值化后的图像（为易于显示，值为0或255）
*                                            注意: 输出图像须为256级灰度图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAdaptiveThreshold( unsigned char * InImage, int Width, int Height, int PixelFormat,
											    int NWid, float T, unsigned char * OutImage );

/* 4 基本图像分析函数：二值图像处理 */

/************************************************************************/
/*  函数名：	viBlobExtract
*	功能：		求二值图像的各个Blob（最多提取255个）
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  BLOBREGION blobregions[256]：每个blob块的左上角坐标和宽、高(有效块从序号1开始，
*                                            blobregions[0]未用)
*	返回值：    寻找到的区域数量，顺序放在blobregions数组中，最多为255个；
*               负值表示求取错误
*/
/************************************************************************/
VIIMAGE_API int __stdcall viBlobExtract( unsigned char * bImage, int Width, int Height, 
										 BLOBREGION blobregions[256] );

/************************************************************************/
/*  函数名：	viLabelImage
*	功能：		标记二值图像的各个连通域
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  unsigned int * LaImage：     结果图像。图像0为背景，目标从序号1开始标记
*	返回值：    寻找到的区域数量；负值表示求取错误
*/
/************************************************************************/
VIIMAGE_API int __stdcall viLabelImage( unsigned char * bImage, int width, int height, 
									    unsigned int * LaImage );

/************************************************************************/
/*  函数名：	viBlobExtract2
*	功能：		一个功能更完善的求二值图像的Blob的函数
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               bool IfCopy：                是否将每个Blob区域拷贝到BLOBREGION的BlobImage中(true为拷贝)
*   输出参数：  BLOBREGION **blobregions：   每个blob块的左上角坐标和宽、高(有效块从序号1开始，
*                                            blobregions[0]未用)
*	返回值：    寻找到的区域数量，顺序放在blobregions数组中；
*               负值表示求取错误
*   使用方法：
*      （1）主程序定义一个指针：BLOBREGION * blobregions;
*	   （2）调用本函数：        viBlobExtract2( bImage, Width, Height, &blobregions );
*	   （3）在主函数中释放内存：viFreeBlobRegion( &blobregions );
*   说明：
*               该函数几乎没有blob个数的限制（最大可为2^31个blob）    
*/
/************************************************************************/
VIIMAGE_API int __stdcall viBlobExtract2( unsigned char * bImage, int Width, int Height, bool IfCopy, 
										  BLOBREGION ** blobregions );

/************************************************************************/
/*  函数名：	viFreeBlobRegion
*	功能：		释放BlobRegion申请的内存
*	入口参数：	BLOBREGION ** blobregions：  每个blob块的左上角坐标和宽、高(有效块从序号1开始，
*                                            blobregions[0]未用)
*               int BlobNum：                blobregions的维数，为blob块个数+1（0未用）
*	返回值：    无   
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFreeBlobRegion( BLOBREGION ** blobregions, int BlobNum );

/************************************************************************/
/*  函数名：	viConnectComponent
*	功能：		一个求二值图像连接区域的函数
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  int * lImage：               标记了连接区域的矩阵，其尺寸与图像相同
*                                            (有效块从序号1开始，0为背景标记)
*	返回值：    区域个数，负值表示求取错误
*   说明：
*               该函数几乎没有blob个数的限制（最大可为2^31个blob）
*               但是，每个blob大小不能太大，Blob大小的限制为堆栈尺寸，目前为32K 
*               即一个256x128的块可以正确标记，大于此尺寸结果不正确。   
*/
/************************************************************************/
VIIMAGE_API int __stdcall viConnectComponent( unsigned char * bImage, int Width, int Height, 
											  int * lImage );

/************************************************************************/
/*  函数名：	viColorRegions
*	功能：		用伪彩色标记出各个Blob块
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               BLOBREGION blobregions[256]：每个blob块的左上角坐标和宽、高(有效块从序号1开始，
*                                            blobregions[0]未用)
*               int RegionNum：              标记出的blob块的个数
*   输出参数：  unsigned char * pImage：     输出24位色伪彩色图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColorRegions( unsigned char * bImage, int Width, int Height, 
										   BLOBREGION * blobregions, int RegionNum, unsigned char * pImage );

/************************************************************************/
/*  函数名：	viColorRegions2
*	功能：		用伪彩色标记各个连通区域块
*	入口参数：	unsigned int * LaImage：     输入标记图像，其中0为背景，
*                                            其他正数为顺序标记的目标
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  unsigned char * pImage：     输出24位色伪彩色图像
*	返回值：    无
*   注意：LaImage最大值即为区域个数，0为背景，区域计数从1开始
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColorRegions2( unsigned int * LaImage, int Width, int Height, 
										    unsigned char * pImage );

/************************************************************************/
/*  函数名：	viMinBoundingBox
*	功能：		求取目标的最小等价椭圆
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  double Xc, Yc：              目标的质心
*               double l, w：                目标的半长轴和半短轴
*               double Theta：               目标与y轴的倾角(角度为单位)，顺时针为正
*	返回值：    > 0 正确，< 0 计算错误
*/
/************************************************************************/
VIIMAGE_API int __stdcall viMinBoundingBox( unsigned char * bImage, int Width, int Height,
										    double & Xc, double & Yc, double & l, double & w, double & Theta );

/************************************************************************/
/*  函数名：	viMinBoundingRectangle
*	功能：		求取目标的最小外接矩形
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  double Xc, Yc：              目标的质心(注意，它不一定在目标的正中间)
*               double l, w：                目标的长和宽
*               double Theta：               目标与y轴的倾角(角度为单位)，顺时针为正
*               double xt, yt, xr, yr：      外接矩形四个顶点，以(xt, yt)为起点
*               double xb, yb, xl, yl：      按顺时针排列
*	返回值：    > 0 正确，< 0 计算错误
*/
/************************************************************************/
VIIMAGE_API int __stdcall viMinBoundingRectangle( unsigned char * bImage, int Width, int Height,
												  double & Xc, double & Yc, double & l, double & w, double & Theta,
												  double & xt, double & yt, double & xr, double & yr,
												  double & xb, double & yb, double & xl, double & yl );

/************************************************************************/
/*  函数名：	viWHRatioFilter
*	功能：		对二值图像进行宽高比滤波
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               BLOBREGION * blobregions：   每个blob块的左上角坐标和宽、高(有效块从序号1开始，
*                                            blobregions[0]未用)
*               int RegionNum：              区域个数
*               double MaxWHRatio, MinWHRatio：  最大，最小宽高比，在这区间中的区域保留
*	返回值：    滤波后的区域数量，负值表示求取错误
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWHRatioFilter( unsigned char * bImage, int Width, int Height, 
										   BLOBREGION * blobregions, int RegionNum, 
										   double MaxWHRatio, double MinWHRatio );

/************************************************************************/
/*  函数名：	viAreaFilter
*	功能：		对二值图像进行面积滤波
*	入口参数：	unsigned char * bImage：     输入二值图，其中白点为255，黑点为0，
*                                            白点为要标记目标读入的二值图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               BLOBREGION * blobregions：   每个blob块的左上角坐标和宽、高(有效块从序号1开始，
*                                            blobregions[0]未用)
*               int RegionNum：              区域个数
*               int MaxArea, MinArea：       最大，最小面积，面积在这区间中的区域保留
*	返回值：    滤波后的区域数量，负值表示求取错误
*/
/************************************************************************/
VIIMAGE_API int __stdcall viAreaFilter( unsigned char * bImage, int Width, int Height,
									    BLOBREGION * blobregions, int RegionNum, 
										int MaxArea, int MinArea );

/************************************************************************/
/*  函数名：	viThinning
*	功能：		对二值图像进行细化
*	入口参数：	unsigned char * bImage：     输入二值图，其中0（黑）代表背景，
*                                            255（白）代表前景。白点为要标记目标。
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  unsigned char * rImage：     骨骼化运算后的二值图像（0为背景或255为前景）
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viThinning( unsigned char * bImage, int Width, int Height,
									   unsigned char * rImage );

/************************************************************************/
/*  函数名：	viFloodFill4
*	功能：		快速Flood Fill算法(4邻域)
*	入口参数：	unsigned char * Image：    读入的图像数据(要求为灰度图像)；
*               int Width：                图像宽（列数）
*               int Height：               图像高（行数）
*               int x：                    种子点的x坐标
*               int y：                    种子点的y坐标
*               unsigned char newColor：   新颜色
*               unsigned char oldColor：   旧颜色
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFloodFill4( unsigned char * Image, int Width, int Height, 
										 int x, int y, unsigned char newColor, unsigned char oldColor );

/************************************************************************/
/*  函数名：	viContour8
*	功能：		计算二值图像的轮廓（8邻域判别）
*	入口参数：	unsigned char * BinImage：   读入的二值图像数据（目标以255标记）
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  unsigned char * ConImage：   轮廓图像
*	返回值：	无
*   说明：
*               输入图像只能为二值图像，255为目标，0为背景。
*/
/************************************************************************/
VIIMAGE_API void __stdcall viContour8( unsigned char * BinImage, int Width, int Height, 
									   unsigned char * ConImage );

/************************************************************************/
/*  函数名：	viContour4
*	功能：		计算二值图像的轮廓（4邻域判别）
*	入口参数：	unsigned char * BinImage：   读入的二值图像数据（目标以255标记）
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  unsigned char * ConImage：   轮廓图像
*	返回值：	无
*   说明：
*               输入图像只能为二值图像，255为目标，0为背景。
*/
/************************************************************************/
VIIMAGE_API void __stdcall viContour4( unsigned char * BinImage, int Width, int Height, 
									   unsigned char * ConImage );

/************************************************************************/
/*  函数名：	viTraceContour8
*	功能：		获得一条轮廓（8邻域判别）
*	入口参数：	unsigned char * ConImage：   读入的二值轮廓图像（轮廓以255标记）
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  int ** Contour：             轮廓数据
*	返回值：	所跟踪轮廓线的点数N(起始点计2次)；N = 0表示未跟踪到轮廓（图中已没有轮廓）
*   说明：
*               1、*Contour的维数为2N维，偶数位置存x坐标，奇数位置存y坐标
*               2、本函数中申请*Contour内存（所以用指针的指针），使用viFreeContour()函数释放内存
*               3、调用一次本函数可获得一条轮廓，同时，在二值轮廓图像ConImage中将该轮廓清除，
*                  以便于继续调用本函数获得另外的轮廓。因此，若要获得多条轮廓，须多次调用本
*                  函数，直到返回值为0。此外，调用本函数会影响ConImage中的内容。
*               4、本函数可跟踪非封闭曲线，对于非封闭曲线，该曲线被来回记录。
*               5、本函数不处理四周边界上的点，如果边界上有目标点，可采用对四周边界进行扩充的图像。
*               6、每条轮廓起始点保存两次，以使曲线封闭，即：(x0,y0)->(x1,y1)->...->(xn,yn)->(x0,y0)
*/
/************************************************************************/
VIIMAGE_API int __stdcall viTraceContour8( unsigned char * ConImage, int Width, int Height,
										   int ** Contour );

/************************************************************************/
/*  函数名：	viTraceContour4
*	功能：		获得一条轮廓（4邻域判别）
*	入口参数：	unsigned char * ConImage：   读入的二值轮廓图像（轮廓以255标记）
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  int ** Contour：             轮廓数据
*	返回值：	所跟踪轮廓线的点数N(起始点计2次)；N = 0表示未跟踪到轮廓（图中已没有轮廓）
*   说明：
*               1、*Contour的维数为2N维，偶数位置存x坐标，奇数位置存y坐标
*               2、本函数中申请*Contour内存（所以用指针的指针），使用viFreeContour()函数释放内存
*               3、调用一次本函数可获得一条轮廓，同时，在二值轮廓图像ConImage中将该轮廓清除，
*                  以便于继续调用本函数获得另外的轮廓。因此，若要获得多条轮廓，须多次调用本
*                  函数，直到返回值为0。此外，调用本函数会影响ConImage中的内容。
*               4、本函数可跟踪非封闭曲线，对于非封闭曲线，该曲线被来回记录。
*               5、本函数不处理四周边界上的点，如果边界上有目标点，可采用对四周边界进行扩充的图像。
*               6、每条轮廓起始点保存两次，以使曲线封闭，即：(x0,y0)->(x1,y1)->...->(xn,yn)->(x0,y0)
*/
/************************************************************************/
VIIMAGE_API int __stdcall viTraceContour4( unsigned char * ConImage, int Width, int Height, 
										   int ** Contour );

/************************************************************************/
/*  函数名：	viFreeContour
*	功能：		释放轮廓数据所占内存
*	入口参数：	int ** Contour：             轮廓数据
*	返回值：	无
*   说明：
*               释放viTraceContour4()或viTraceContour8()申请的轮廓数据内存。
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFreeContour( int ** Contour );

/************************************************************************/
/*  函数名：	viTraceContour
*	功能：		跟踪单条轮廓，产生链码
*	入口参数：	unsigned char * Img：     输入图像，为二值图像
*               int Width, Height：       图像宽和高
*               int x, int y：            标记起始点（链码起始点）
*               unsigned char * codebuf： 链码（1字节一个编码）
*               int bufsize：             链码Buffer长度
*               bool isOut：              是否为外轮廓（1为外轮廓，0为内轮廓）
*	返回值：	链码长度
*/
/************************************************************************/
VIIMAGE_API int __stdcall viTraceContour( unsigned char * Img, int Width, int Height, int x, int y, 
										  unsigned char * codebuf, int bufsize, bool isOut );

/************************************************************************/
/*  函数名：	viFindContours
*	功能：		获得二值目标的多条链码描述
*	入口参数：	unsigned char * bImage：     读入的二值图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int MiniP：                  最小周长（像素为单位）
*               int MiniS：                  最小面积（像素为单位）
*               int ChainType:               链码跟踪类型，1 --- 外轮廓跟踪，
*                                            2 --- 内轮廓跟踪，3 --- 内外轮廓都跟踪
*   输出值：    int ObjectNum:               跟踪到的目标个数
*	返回值：	链码指针，若未找到链码，则返回NULL
*   说明：      在跟踪链码后，已经计算链码所描述目标的面积（像素数）和周长
*/
/************************************************************************/
VIIMAGE_API ChainContourObj * __stdcall viFindContours( unsigned char * bImage, int Width, int Height,
													    int MiniP, int MiniS, int ChainType, int &ObjectNum );

/************************************************************************/
/*  函数名：	viFreeChainContourObj
*	功能：		释放目标链码
*	入口参数：	ChainContourObj * all_Contours： 目标链码描述头指针
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFreeChainContourObj( ChainContourObj * all_Contours );

/************************************************************************/
/*  函数名：	viFillingContour
*	功能：		对链码描述的一段区域进行颜色填充
*	入口参数：	unsigned char * gImage：     图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int x0, y0：                 链码起点
*               unsigned char * code：       链码编码
*               int N:                       链码长度
*               boo fillEdge：               是否填充边缘
*               unsigned char nonc：         边界颜色（填充终点）
*                                           （任意设置一个未用过的中间值，在填充中间过程中用来描绘边界）
*               unsigned char fillc：        填充颜色（填充起点）
*   输出值：    unsigned char * gImage：     目标填充后的图像数据
*	返回值：	填充方向
*/
/************************************************************************/
VIIMAGE_API int __stdcall viFillingContour( unsigned char * gImage, int Width, int Height,
										    int x0, int y0, unsigned char * code, int N,
										    bool fillEdge, unsigned char nonc, unsigned char fillc );

/************************************************************************/
/*  函数名：	viMarkChainWithColor
*	功能：		对链码标记的目标轮廓赋一种灰度
*	入口参数：  unsigned char * gImage:      灰度图象
*               int Width, Height:           图像宽高
*               int x, y:                    链码起始坐标
*               unsigned char * Code:        链码编码
*               int N:                       链码长度
*               unsigned char Color:         绘制的颜色，0-255
*   输出参数：  unsigned char * gImage:      标记好目标的灰度图象
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMarkChainWithColor( unsigned char * gImage, int Width, int Height, 
												 int x, int y, unsigned char * Code, int N, unsigned char Color );

/************************************************************************/
/*  函数名：	viAreaAndPerimeterPixel
*	功能：		根据链码求区域面积和周长(面积求的就是像素的个数，不考虑边界占的比重)
*	入口参数：	unsigned char * code： 目标链码描述头指针
*               int N：                链码长度
*   输出参数：  int * Area：           计算出的目标面积
*               int * Perimeter：      计算出的目标周长
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAreaAndPerimeterPixel( unsigned char * code, int N, int * Area, int * Perimeter );

/************************************************************************/
/*  函数名：	viAreaAndPerimeter
*	功能：		根据链码求区域面积和周长
*               (按定义式计算，8链码的斜边面积算sqrt(2)个像素，因此面积偏大)
*	入口参数：	unsigned char * Code:   链码编码
*               int N:                  链码长度
*   输出参数：  int * Area:             目标面积
*               int * Perimeter:        目标周长
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAreaAndPerimeter( unsigned char * Code, int N, int * Area, int * Perimeter );

/************************************************************************/
/*  函数名：	viCentroidAndBoundingBox
*	功能：		根据链码求区域面积和周长
*               (按定义式计算，8链码的斜边面积算sqrt(2)个像素，因此面积偏大)
*	入口参数：	int x0, y0:             链码起点(x0,y0)
*               unsigned char * Code:   链码编码
*               int N:                  链码长度
*   输出参数：  int * Left, * Top:      目标左、右、上、下边界
*               int * Right, * Bottom:
*               int * Xc, * Yc:         目标质心
*               double * Theta:         与y轴的倾角，顺时针为正，角度单位
*               int * l, * w:           半长轴、短轴
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viCentroidAndBoundingBox( int x0, int y0, unsigned char * Code, int N, int * Left, int * Top, 
													 int * Right, int * Bottom, int * Xc, int * Yc, double * Theta, int * l, int * w );
													
/************************************************************************/
/*  函数名：	viCalcuContourObj
*	功能：		计算目标链码的面积、周长、外接矩形宽、高、质心坐标等
*	入口参数：	ChainContourObj * all_Contours： 目标链码描述头指针
*	返回值：	目标的个数
*/
/************************************************************************/
VIIMAGE_API int __stdcall viCalcuContourObj( ChainContourObj * all_Contours );

/************************************************************************/
/*  函数名：	viLineFitting
*	功能：		用直线 y = bx + a 拟合一组点（xi,yi）
*	入口参数：	int * xi:         x坐标
*               int * yi:         y坐标
*               int N:            数据组数，须 >=2
*   输出参数：  double alpha:     与x轴夹角，角度为单位，顺时针为正，b = tan( alpha )
*               double a:         直线截距(当alpha = 90时，a为无穷)
*	返回值：	0 --- 计算不成功； 1 --- 计算成功
*/
/************************************************************************/
VIIMAGE_API int __stdcall viLineFitting( int * xi, int * yi, int N, double & alpha, double & a );

/************************************************************************/
/*  函数名：	viHuMoments
*	功能：		计算二值图像的7个Hu不变矩
*	入口参数：	unsigned char * BinImage：   读入的二值图像数据（目标以255标记）
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*   输出参数：  int Xc, Yc：                 目标的中心
*               double & phi1 - phi7：       7个Hu不变矩
*	返回值：	无
*   说明：
*               输入图像只能为二值图像，255为目标，0为背景。
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHuMoments( unsigned char * BinImage, int Width, int Height, int & Xc, int & Yc,
									    double & phi1, double & phi2, double & phi3, double & phi4, 
									    double & phi5, double & phi6, double & phi7 );

/************************************************************************/
/*  函数名：	viEllipticFD
*	功能：		采用Elliptic Fourier Descriptor计算二值图像轮廓傅立叶描述子
*	入口参数：	int * Contour：              轮廓数据坐标
*               N：                          轮廓数据点数
*               int M：                      傅立叶描述子的个数
*   输出参数：  double * FD：                傅立叶描述子数组
*	返回值：	无
*   说明：
*               轮廓数据点数为N，数组Contour的长度为2N，偶数位置存x坐标，
*               奇数位置存y坐标。Contour为封闭轮廓，且首尾衔接（第1点保存两次）
*               M为输出傅立叶描述子的个数，M控制了空域曲线上的点的抽样间隔，
*               抽样间隔为round( N/M )
*/
/************************************************************************/
VIIMAGE_API void __stdcall viEllipticFD( int * Contour, int N, int M, double * FD );

/* 5 基本图像处理函数：图像点处理 */

/************************************************************************/
/*  函数名：	viImageInvert
*	功能：		图像取反操作
*	入口参数：	unsigned char * Image：      输入图像
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            图像像素格式，24或8
*   输出参数：  unsigned char * rImage：     输出图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viImageInvert( unsigned char * Image, int Width, int Height, int PixelFormat,
										  unsigned char * rImage );

/************************************************************************/
/*  函数名：	viAlphaFusion
*	功能：		两幅彩色图像Alpha合成
*	入口参数：	unsigned char * Image1：     输入第1幅彩色图像
*               int Width：                  第1幅图像宽（列数）
*               int Height：                 第1幅图像高（行数）
*               int PixelFormat：            第1幅图像像素格式，必须为24位真彩色
*               double Alpha：               第1幅图像的Alpha值
*               unsigned char * Image2：     输入第2幅图像
*               int Width2：                 第2幅图像宽
*               int Height2：                第2幅图像高
*               int PixelFormat2：           第2幅图像像素格式，24或8
*   输出参数：  unsigned char * rImage：     输出图像，尺寸与第1幅图像一样，须为24位真彩色
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAlphaFusion( unsigned char * Image1, int Width, int Height, int PixelFormat,
										  double Alpha, unsigned char * Image2, int Width2, int Height2,
										  int PixelFormat2, unsigned char * rImage );

/* 6 基本图像处理函数：形态学处理 */

/************************************************************************/
/*  函数名：	viBinaryErosion
*	功能：		二值图像的腐蚀运算
*	入口参数：	unsigned char * bImage：     输入图像，必须为二值图像，
*                                            0（黑）代表背景，255（白）代表前景
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*   输出参数：  unsigned char * rImage：     腐蚀运算后的二值图像（0为背景，255为前景）
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryErosion( unsigned char * bImage, int Width, int Height,
										    unsigned char * sComponent, int w, int h,
											unsigned char * rImage );

/************************************************************************/
/*  函数名：	viBinaryDilation
*	功能：		二值图像的膨胀运算
*	入口参数：	unsigned char * bImage：     输入图像，必须为二值图像，
*                                            0（黑）代表背景，255（白）代表前景
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*   输出参数：  unsigned char * rImage：     膨胀运算后的二值图像（0为背景，255为前景）
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryDilation( unsigned char * bImage, int Width, int Height,
										     unsigned char * sComponent, int w, int h,
											 unsigned char * rImage );

/************************************************************************/
/*  函数名：	viBinaryOpen
*	功能：		二值图像的开运算
*	入口参数：	unsigned char * bImage：     输入图像，必须为二值图像，
*                                            0（黑）代表背景，255（白）代表前景
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponentE：腐蚀结构元素(原点在[w/2,h/2]处)
*               int wE,hE：                  腐蚀结构元素的宽和高
*               unsigned char * sComponentD：膨胀结构元素(原点在[w/2,h/2]处)
*               int wD,hD：                  膨胀结构元素的宽和高
*   输出参数：  unsigned char * rImage：     膨胀运算后的二值图像（0为背景，255为前景）
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryOpen( unsigned char * bImage, int Width, int Height,
										 unsigned char * sComponentE, int wE, int hE,
										 unsigned char * sComponentD, int wD, int hD,
										 unsigned char * rImage );

/************************************************************************/
/*  函数名：	viBinaryClose
*	功能：		二值图像的闭运算
*	入口参数：	unsigned char * bImage：     输入图像，必须为二值图像，
*                                            0（黑）代表背景，255（白）代表前景
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponentE：腐蚀结构元素(原点在[w/2,h/2]处)
*               int wE,hE：                  腐蚀结构元素的宽和高
*               unsigned char * sComponentD：膨胀结构元素(原点在[w/2,h/2]处)
*               int wD,hD：                  膨胀结构元素的宽和高
*   输出参数：  unsigned char * rImage：     膨胀运算后的二值图像（0为背景，255为前景）
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viBinaryClose( unsigned char * bImage, int Width, int Height,
										  unsigned char * sComponentE, int wE, int hE,
										  unsigned char * sComponentD, int wD, int hD,
										  unsigned char * rImage );

/************************************************************************/
/*  函数名：	viMorphContour
*	功能：		用形态学方法提取二值图像轮廓（但不作描述）
*	入口参数：	unsigned char * bImage：   读入的图像数据，图像大小为WxH字节；
*               int Width：                图像宽（列数）
*               int Height：               图像高（行数）
*               int x：                    种子点的x坐标
*               int y：                    种子点的y坐标
*               unsigned char newColor：   新颜色
*               unsigned char oldColor：   旧颜色
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphContour( unsigned char * bImage, int Width, int Height, 
										   unsigned char * rImage );

/************************************************************************/
/*  函数名：	viGrayDilation
*	功能：		灰度图像的膨胀运算
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     膨胀运算后的结果图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayDilation( unsigned char * gImage, int Width, int Height,
										   unsigned char * sComponent, int w, int h, int AutoType,
										   unsigned char * rImage );

/************************************************************************/
/*  函数名：	viGrayErosion
*	功能：		灰度图像的腐蚀运算
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     腐蚀运算后的结果图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayErosion( unsigned char * gImage, int Width, int Height,
										  unsigned char * sComponent, int w, int h, int AutoType,
										  unsigned char * rImage );

/************************************************************************/
/*  函数名：	viGrayOpen
*	功能：		灰度图像的形态学开运算
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     开运算后的结果图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayOpen( unsigned char * gImage, int Width, int Height,
									   unsigned char * sComponent, int w, int h, int AutoType,
									   unsigned char * rImage );

/************************************************************************/
/*  函数名：	viGrayClose
*	功能：		灰度图像的形态学闭运算
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     闭运算后的结果图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGrayClose( unsigned char * gImage, int Width, int Height,
									    unsigned char * sComponent, int w, int h, int AutoType,
									    unsigned char * rImage );

/************************************************************************/
/*  函数名：	viMorphSmooth
*	功能：		灰度形态学图像平滑
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     平滑后的结果图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphSmooth( unsigned char * gImage, int Width, int Height,
										  unsigned char * sComponent, int w, int h, int AutoType,
										  unsigned char * rImage );

/************************************************************************/
/*  函数名：	viMorphGradient
*	功能：		灰度形态学求图像梯度
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     求得的形态学梯度图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphGradient( unsigned char * gImage, int Width, int Height,
										    unsigned char * sComponent, int w, int h, int AutoType,
										    unsigned char * rImage );

/************************************************************************/
/*  函数名：	viMorphTophat
*	功能：		灰度形态学高帽变换
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     求得的结果图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphTophat( unsigned char * gImage, int Width, int Height,
										  unsigned char * sComponent, int w, int h, int AutoType,
										  unsigned char * rImage );

/************************************************************************/
/*  函数名：	viMorphBottomhat
*	功能：		灰度形态学低帽变换
*	入口参数：	unsigned char * gImage：     输入图像，必须为灰度图像，
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               unsigned char * sComponent： 结构元素(结构元素的原点在[w/2,h/2]处)
*               int w, h：                   结构元素的宽和高
*               int AutoType：               自动产生的结构元素
*                                            0 --- 不自动产生，由sComponent提供； 
*                                            1 --- 矩形；2 --- 十字形；3 --- 椭圆形
*                                            自动产生的灰度值为sComponent[0]                 
*   输出参数：  unsigned char * rImage：     求得的结果图像
*	返回值：    无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMorphBottomhat( unsigned char * gImage, int Width, int Height,
											 unsigned char * sComponent, int w, int h, int AutoType,
											 unsigned char * rImage );

/************************************************************************/
/*  函数名：	viWaterShed_Vincent
*	功能：		分水岭分割（Vincent方法，排序+泛洪）
*	入口参数：	unsigned char * Image：      待分割图像数据，8或24位
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int MorphGradient：          形态学梯度求取强度，1--20，越小越弱，缺省为3
*               int GaussWin：               高斯平滑窗口宽，可为3，5，7，9，为1则不平滑，缺省取5
*               int Threshold：              梯度修正阈值，选择范围在（2~8之间，1则表示不修正）
*               int IfBound：                输出图像格式
*                    IfBound = 1, 在原图上显示分水岭线，图像分割块标记从1到MaxLabelNo；
*                    IfBound = 0, 显示各个块，图像分割块标记也是从1到MaxLabelNo，当中没有分水线
*   输出参数：  int SegImage：               输出标记图像，图像格式由IfBound控制
*	返回值：	成功：分割出的图像块数目（MaxLabelNo）；失败：返回0
*   注意：      这里的Threshold用于控制边缘图像中极小值的个数。对输入的边缘图像系统自动计算
*               一个阈值t，取t/Threshold作为真正阈值，低于该值的数据都作为极小值，强制赋为0。
*               MorphGradient和Threshold合起来控制极小值的数目
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaterShed_Vincent( unsigned char * Image, int Width, int Height, int PixelFormat, 
											   int * SegImage, int MorphGradient, int GaussWin, int Threshold, 
											   int IfBound );

/************************************************************************/
/*  函数名：	viShowWaterShedSeg
*	功能：		显示分水岭分割的结果
*	入口参数：	int * SegImage：             待显示的分割结果
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int IfBound：                输出图像格式（由SegImage决定）
*                    IfBound = 1, 在原图上显示分水岭线，图像分割块标记从1到MaxLabelNo；
*                    IfBound = 0, 显示各个块，图像分割块标记也是从1到MaxLabelNo，当中没有分水线
*               unsigned char * OrigImage：  原始图像数据，宽/高为Width和Height
*               int PixelFormat：            原始图像格式，为24或8
*               double Alpha：               图像的透明值Alpha值
*               int Color：                  分水线颜色（不受Alpha值影响）
*   输出参数：  unsigned char * sImage：     显示的图像（必须为24位真彩色！）
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viShowWaterShedSeg( int * SegImage, int Width, int Height, int IfBound, 
											   unsigned char * OrigImage, int PixelFormat, double Alpha, int Color,
											   unsigned char * sImage );

/* 7 基本图像处理函数：彩色空间转换函数 */

/************************************************************************/
/*  函数名：	viColor24toGray8
*	功能：		24位彩色图像转换为8位灰度图像
*	入口参数：	unsigned char * ColorImage：    原始彩色图像数据
*               int Width, int Height：         图像的宽和高
*               int Type：                      转换类型：
*   0（缺省） --- 平均转换，Y = ( R + G + B )/3
*   1         --- 加权转换，Y601 = 0.299 * R + 0.587 * G + 0.114 * B （ITU_R_BT601）
*   出口参数：  unsigned char * GrayImage：     灰度图像数据
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColor24toGray8( unsigned char * ColorImage, int Width, int Height, int Type,
											 unsigned char * GrayImage );

/************************************************************************/
/*  函数名：	viGray8toColor24
*	功能：		8位灰度图像转换为24位彩色图像
*	入口参数：	unsigned char * GrayImage：     灰度图像数据
*               int Width, int Height：         图像的宽和高
*               int Type：                      转换类型：
*                                               0（缺省） --- RGB分别放置相应灰度数据
*                                               1         --- 遥感伪彩色
*                                               2         --- 医学伪彩色
*   出口参数：  unsigned char * ColorImage：    24位彩色图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGray8toColor24( unsigned char * GrayImage, int Width, int Height, int Type,
											 unsigned char * ColorImage );

/************************************************************************/
/*  函数名：	viColor24toRGB
*	功能：		24位彩色图像转换为RGB三通道图像
*	入口参数：	unsigned char * ColorImage：    原始彩色图像数据
*               int Width, int Height：         图像的宽和高
*   输出参数：  unsigned char * rChannel：      R通道
*               unsigned char * gChannel：      G通道
*               unsigned char * bChannel：      B通道
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viColor24toRGB( unsigned char * ColorImage, int Width, int Height,
										   unsigned char * rChannel, unsigned char * gChannel, unsigned char * bChannel );

/************************************************************************/
/*  函数名：	viRGBtoColor24
*	功能：		RGB三通道图像转换为24位彩色图像
*	入口参数：	unsigned char * rChannel：      R通道
*               unsigned char * gChannel：      G通道
*               unsigned char * bChannel：      B通道
*               int Width, int Height：         图像的宽和高
*   输出参数：  unsigned char * ColorImage：    原始彩色图像数据
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRGBtoColor24( unsigned char * rChannel, unsigned char * gChannel, unsigned char * bChannel,
										   int Width, int Height, unsigned char * ColorImage );

/************************************************************************/
/*  函数名：	viRGBtoYUV
*	功能：		RGB图像转换为YUV三通道图像
*	入口参数：	unsigned char * ColorImage：    原始彩色图像数据
*               int Width, int Height：         图像的宽和高
*   输出参数：  unsigned char * Y：             Y分量
*               unsigned char * U：             U分量
*               unsigned char * V：             V分量
*	返回值：	
*               1 --- 成功；0 --- 不成功
*/
/************************************************************************/
VIIMAGE_API int __stdcall viRGBtoYUV( unsigned char * ColorImage, int Width, int Height,
									  unsigned char * Y, unsigned char * U, unsigned char * V );

/************************************************************************/
/*  函数名：	viYUVtoRGB
*	功能：		YUV三通道图像转换为RGB图像
*	入口参数：	unsigned char * Y：             Y分量
*               unsigned char * U：             U分量
*               unsigned char * V：             V分量
*               int Width, int Height：         图像的宽和高
*   输出参数：  unsigned char * ColorImage：    原始彩色图像数据
*	返回值：	
*               1 --- 成功；0 --- 不成功
*/
/************************************************************************/
VIIMAGE_API int __stdcall viYUVtoRGB( unsigned char * Y, unsigned char * U, unsigned char * V,
									  int Width, int Height, unsigned char * ColorImage );

/************************************************************************/
/*  函数名：	viRGBtoHSL
*	功能：		RGB三通道图像转换为HSL图像
*	入口参数：	unsigned char * ColorImage：    原始彩色图像数据(各分量取值0-255)
*               int Width, int Height：         图像的宽和高
*   输出参数：  
*               double * Hue：                  H分量(色度)，取值[0,360]
*               double * Saturation：           S分量(饱和度)，取值[0,100]
*               double * Luminance：            L分量(亮度)，取值[0,100]
*	返回值：	
*               无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRGBtoHSL( unsigned char * ColorImage, int Width, int Height, 
									   double * Hue, double * Saturation, double * Luminance );

/************************************************************************/
/*  函数名：	viHSLtoRGB
*	功能：		HSL图像转换为RGB三通道图像
*	入口参数：	
*               double * Hue：                  H分量(色度)，取值[0,360]
*               double * Saturation：           S分量(饱和度)，取值[0,100]
*               double * Luminance：            L分量(亮度)，取值[0,100]
*               int Width, int Height：         图像的宽和高
*   输出参数：  
*               unsigned char * ColorImage：    彩色图像数据(各分量取值0-255)
*	返回值：	
*               无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHSLtoRGB( double * Hue, double * Saturation, double * Luminance,
									   int Width, int Height, unsigned char * ColorImage );

/************************************************************************/
/*  函数名：	viRGBtoHSL2
*	功能：		RGB三通道图像转换为HSL图像(整数范围)
*	入口参数：	unsigned char * ColorImage：    原始彩色图像数据(各分量取值0-255)
*               int Width, int Height：         图像的宽和高
*   输出参数：  
*               unsigned char * Hue：           H分量(色度)，取值[0,240]
*               unsigned char * Saturation：    S分量(饱和度)，取值[0,240]
*               unsigned char * Luminance：     L分量(亮度)，取值[0,240]
*	返回值：	
*               无
*   注意：
*               在Windows系统下，HSL分量的范围是[0,240]。参考"画笔"程序，可以看到
*               RGB（红|绿|蓝）和HSL（色调|饱和度|亮度）的联系。
*/
/************************************************************************/
VIIMAGE_API void __stdcall viRGBtoHSL2( unsigned char * ColorImage, int Width, int Height, 
									    unsigned char * Hue, unsigned char * Saturation, unsigned char * Luminance );

/************************************************************************/
/*  函数名：	viHSLtoRGB2
*	功能：		HSL图像(整数范围)转换为RGB三通道图像
*	入口参数：
*               unsigned char * Hue：           H分量(色度)，取值[0,240]
*               unsigned char * Saturation：    S分量(饱和度)，取值[0,240]
*               unsigned char * Luminance：     L分量(亮度)，取值[0,240]
*               int Width, int Height：         图像的宽和高
*   输出参数：  
*               unsigned char * ColorImage：    彩色图像数据(各分量取值0-255)
*	返回值：	
*               无
*   注意：
*               在Windows系统下，HSL分量的范围是[0,240]。参考"画笔"程序，可以看到
*               RGB（红|绿|蓝）和HSL（色调|饱和度|亮度）的联系。
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHSLtoRGB2( unsigned char * Hue, unsigned char * Saturation, unsigned char * Luminance,
									    int Width, int Height, unsigned char * ColorImage );

/* 8 基本图像分析函数：边缘检测 */

/************************************************************************/
/*  函数名：	viEdge
*	功能：		对图像进行边缘检测（未做二值化处理）
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int Type：                   边缘检测的方法：0 -- Sobel（水平），
*                                                            1 -- Sobel（垂直）
*                                                            2 -- Sobel（45度）
*                                                            3 -- Sobel（135度）
*                                                            4 -- Prewitt（水平）
*                                                            5 -- Prewitt（垂直）
*                                                            6 -- Laplacian
*                                                            7 -- Robots（45度角）
*                                                            8 -- Robots（135度角）
*                                                            9 -- 水平梯度
*                                                           10 -- 垂直梯度
*   输出参数：  unsigned char * OutImage:    灰度边缘图像
*	返回值：	无
*   说明：      (1) 输出图像为灰度图像，边缘图像未二值化
*               (2) 无论输入为彩色或者灰度图像，输出皆为灰度图像
*               (3) 这不是一个边缘提取的快速实现，检测时用到了double运算
*/
/************************************************************************/
VIIMAGE_API void __stdcall viEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
								   int Type, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viCannyEdge
*	功能：		对图像进行Canny边缘检测（结果进行了二值化处理）
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               double sigma：               Gaussian滤波的标准方差
*               double dRatioLow：           低阈值占高阈值的百分例
*               double dRatioHigh：          低于高阈值像素占图像像素总数的百分例
*   输出参数：  unsigned char * EdgeImage:   边缘图像
*	返回值：	无
*   说明：      (1) 输出图像为二值图像，边缘图像进行了二值化，0为黑，255为白
*               (2) 无论输入为彩色或者灰度图像，输出皆为二值图像
*               (3) 关于Canny算子参数的调整：
*               两个典型的图像边缘提取的例子如下：
*               a) 256 x 256，8级灰度house图像：
*                  采用参数：sigma=0.3, dRatioLow=0.6,dRatioHigh=0.89
*               b) 256 x 256，8级灰度lena图像：
*                  采用参数：sigma=0.6, dRatioLow=0.45-0.5, dRatioHigh=0.75-0.8
*               lena图像由于细节比较丰富，在去掉虚假边缘的同时容易使边缘破碎，
*               因此参数比较难调；而house细节比较少，轮廓比较清晰
*/
/************************************************************************/
VIIMAGE_API void __stdcall viCannyEdge( unsigned char * InImage, int Width, int Height, int PixelFormat, double sigma,
									    double dRatioLow, double dRatioHigh, unsigned char * EdgeImage );

/************************************************************************/
/*  函数名：	viShenEdge
*	功能：		对图像进行沈俊边缘检测（结果进行了二值化处理，只对灰度图象处理）
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               double Alpha：               指数滤波迭代算法的系数，Alpha在0.01-0.99之间
*   输出参数：  unsigned char * EdgeImage:   边缘图像
*	返回值：	无
*   注意：      该函数只处理灰度图像
*/
/************************************************************************/
VIIMAGE_API void __stdcall viShenEdge( unsigned char * InImage, int Width, int Height,
									   int PixelFormat, double Alpha, unsigned char * EdgeImage );

/************************************************************************/
/*  函数名：	viShenEdge2
*	功能：		对图像进行沈俊边缘检测（结果进行了二值化处理）
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               double b：                   指数滤波迭代算法的系数，一般取值为0.9左右
*               double Ratio：               低于高阈值的象素数占所有象素数的百分比
*               int WindowSize：             计算自适应梯度的窗口大小，一般取值为7
*   输出参数：  unsigned char * EdgeImage:   边缘图像
*	返回值：	无
*   说明：      (1) 输出图像为二值图像，边缘图像进行了二值化，0为黑，255为白
*               (2) 无论输入为彩色或者灰度图像，输出皆为二值图像
*               (3) 关于Shen算子参数的调整：
*                   对于Lena 256x256图像为 b = 0.95, ratio = 0.85, WindowSize = 7
*               可改进方向和问题：apply_ISEF_horizontal的滤波方法，b的取值和细化的方法
*/
/************************************************************************/
VIIMAGE_API void __stdcall viShenEdge2( unsigned char * InImage, int Width, int Height, int PixelFormat, double b,
									    double Ratio, int WindowSize, unsigned char * EdgeImage );

/************************************************************************/
/*  函数名：	viLoGEdge
*	功能：		LOG算子边缘检测(输出二值图像)
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int Type：                   5 --- 5x5模板（缺省），9 --- 9x9模板
*               int Threshold：              阈值，0 --- 自动阈值；1---255 人工阈值
*   输出参数：  unsigned char * EdgeImage:   边缘图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viLoGEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
									  int Type, int Threshold, unsigned char * EdgeImage );

/************************************************************************/
/*  函数名：	viKirschEdge
*	功能：		Kirsch算子边缘检测（非线性算子）
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int Thres：                  处理阈值（0-255）
*   输出参数：  unsigned char * EdgeImage:   边缘图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viKirschEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
									     int Thres, unsigned char * EdgeImage );

/************************************************************************/
/*  函数名：	viWallisEdge
*	功能：		Wallis算子边缘检测（非线性对数算子）
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int Thres：                  处理阈值（1-255），若<0，则自动选择阈值，=0，输出灰度图像
*   输出参数：  unsigned char * EdgeImage:   边缘图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viWallisEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
										 int Thres, unsigned char * EdgeImage );

/************************************************************************/
/*  函数名：	viFastVerticalEdge
*	功能：		快速垂直边缘检测dI/dx (输出灰度图像)
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int Type：                   1 --- Sobel，0 --- Previtt。算子[-1 0 1]
*   输出参数：  int * EdgeImage:             边缘矩阵
*	返回值：	无
*   说明：      根据viFastVerticalEdge(), viFastHorizontalEdge()可以计算梯度方向和幅值
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastVerticalEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   int Type, int * EdgeImage );

/************************************************************************/
/*  函数名：	viFastHorizontalEdge
*	功能：		快速水平边缘检测dI/dy (输出灰度图像)
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int Type：                   1 --- Sobel，0 --- Previtt。算子[-1 0 1]'
*   输出参数：  int * EdgeImage:             边缘矩阵
*	返回值：	无
*   说明：      根据viFastVerticalEdge(), viFastHorizontalEdge()可以计算梯度方向和幅值
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastHorizontalEdge( unsigned char * InImage, int Width, int Height, int PixelFormat,
											     int Type, int * EdgeImage );

/* 9 基本图像分析函数：角点检测 */

/************************************************************************/
/*  函数名：	viHarrisCorner
*	功能：		对图像进行Harris角点检测
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               double Sigma：               计算角点用Gauss函数的方差(缺省2.0)
*               double Alpha：               计算角点用Alpha值(缺省0.04)
*               double Threshold：           角点检测阈值(缺省0.0)
*               int Radius：                 图像平滑半径(缺省2，若该值>50或<1，则不进行图像平滑)
*               int UseMorph：               是否进行非最大值抑制，1 -- 使用，0 -- 不使用
*   输出参数：  unsigned char * CornerImage: 角点图像
*	返回值：	无
*   说明：      (1) 典型的图像角点提取的参数如下：
*               Sigma = 2.0; Radius = 2; Alpha = 0.04; Threshold = 0; UseMorph = 1
*               (2) 该程序为一个浮点实现，速度较慢
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHarrisCorner( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										   double Sigma, double Alpha, double Threshold, int Radius, int UseMorph,
								           unsigned char * CornerImage );

/************************************************************************/
/*  函数名：	viMoravecCorner
*	功能：		对图像进行Moravec角点检测
*	入口参数：	unsigned char * InImage：    读入的图像数据，对于灰度图像大小为WxH字节；
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int w：                      计算感兴趣点的邻域窗口（w为3-15间的奇数）
*               int Threshold：              角点检测阈值(缺省0)
*   输出参数：  unsigned char * CornerImage: 角点图像
*	返回值：	无
*   说明：      典型的图像角点提取的参数如下：
*               w = 5; Threshold = 0
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMoravecCorner( unsigned char * InImage, int Width, int Height, int PixelFormat,
										    int w, int Threshold, unsigned char * CornerImage );

/* 10 基本图像处理函数：图像平滑 */

/************************************************************************/
/*  函数名：	viAvgSmoothing
*	功能：		对图像进行均值平滑
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int w, h：                   图像均值平滑窗口大小为w x h
*               int Thres：                  阈值（<= 0 -- 均值代替中间值，
*                                            > 0 -- 差值高于阈值时进行替代）
*   输出参数：  unsigned char * OutImage:    增强后的图像
*	返回值：	无
*   说明:       本函数用积分图方法进行了加速
*/
/************************************************************************/
VIIMAGE_API void __stdcall viAvgSmoothing( unsigned char * InImage, int Width, int Height, 
										   int PixelFormat, int w, int h, int Thres, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viGaussianSmoothing
*	功能：		对图像进行高斯各向同性平滑
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               double Sigma：               Gaussian函数的方差(缺省为1.5)，决定平滑窗口宽度
*               int rounds：                 平滑的次数
*   输出参数：  unsigned char * OutImage:    平滑后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianSmoothing( unsigned char * InImage, int Width, int Height,
											    int PixelFormat, double Sigma, int rounds, 
												unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viGaussianSmoothing2
*	功能：		对图像进行高斯各向同性平滑（两次一维卷积代替二维卷积）
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int w：                      Gaussian平滑窗口宽度(1-49，奇数)
*               int rounds：                 平滑的次数
*   输出参数：  unsigned char * OutImage:    平滑后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianSmoothing2( unsigned char * InImage, int Width, int Height,
											     int PixelFormat, int w, int rounds, 
												 unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viGaussianSmoothing3
*	功能：		对图像进行高斯各向同性平滑（采用递推滤波器）
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               double Sigma：               Gaussian函数的方差(缺省为1.5)，决定平滑窗口宽度
*               int rounds：                 平滑的次数
*   输出参数：  unsigned char * OutImage:    平滑后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGaussianSmoothing3( unsigned char * InImage, int Width, int Height,
											     int PixelFormat, double Sigma, int rounds, 
												 unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viPMSmoothing
*	功能：		对图像进行各向异性平滑(Perona-Malik各向异性平滑)
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int gType：                  扩散函数类型(0 - 倒数函数，1 - 指数函数(缺省值)
*               double K：                   扩散参数(1-255)，与gType参数相对应
*               double l：                   归一化系数，取值范围：0-0.25，一般取0.25
*               int rounds：                 平滑的次数
*   输出参数：  unsigned char * OutImage:    平滑后的图像
*	返回值：	无
*   说明:       一组典型值：
*               gType = 0, K = 4, l = 0.20
*/
/************************************************************************/
VIIMAGE_API void __stdcall viPMSmoothing( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										  int gType, double K, double l, int rounds, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viMediumFiltering
*	功能：		对图像进行中值滤波
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            像素类型24或8
*               int w, h：                   图像滤波窗口大小为w x h，最大10x10
*               unsigned char * Mask：       滤波窗口的掩模，
*               像素位置上的值为0 --- 对应像素不参加滤波，非0 --- 对应像素参加滤波
*   输出参数：  unsigned char * OutImage:    滤波后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viMediumFiltering( unsigned char * InImage, int Width, int Height, int PixelFormat, 
											  int w, int h, unsigned char * Mask, unsigned char * OutImage );

/* 11 基本图像处理函数：图像增强 */

/************************************************************************/
/*  函数名：	viGammaCorrect
*	功能：		对图像进行Gamma校正
*	入口参数：	unsigned char * InImage：     读入的图像数据
*               int Width：                   图像宽（列数）
*               int Height：                  图像高（行数）
*               int PixelFormat：             像素类型24或8
*               float rGamma, gGamma, bGamma：三通道的Gamma值（0.2-5之间）
*               float iGamma：                灰度Gamma值（0.2-5之间）
*                                             具体采用哪个Gamma值取决于PixelFormat
*   输出参数：  unsigned char * OutImage:     Gamma校正后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGammaCorrect( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										   float rGamma, float gGamma, float bGamma, float iGamma,
										   unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viSharpening
*	功能：		对图像进行Laplacian锐化增强
*	入口参数：	unsigned char * InImage：     读入的图像数据
*               int Width：                   图像宽（列数）
*               int Height：                  图像高（行数）
*               int PixelFormat：             像素类型24或8
*               int Type：                    锐化类型，Laplacian算子差异：
*                                             0 --- [0 -1 0; -1 4 -1; 0 -1 0]
*                                             1 --- [-1 -1 -1; -1 8 -1; -1 -1 -1] 
*   输出参数：  unsigned char * OutImage:     增强后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viSharpening( unsigned char * InImage, int Width, int Height, int PixelFormat, 
										 int Type, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viHistogramCorrect
*	功能：		对图像进行直方图修正
*	入口参数：	unsigned char * InImage：     读入的图像数据
*               int Width：                   图像宽（列数）
*               int Height：                  图像高（行数）
*               int PixelFormat：             像素类型（24或8）
*               int Type：                    直方图修正类型：
*                                             0 --- 在YCrCb域对Y分量做
*                                             1 --- 对R、G、B三分量分别做
*               int * dHist：                 期望直方图，如果不为NULL，则输入一个256个BIN
*                                             的期望直方图；否则系统自动做直方图均衡化
*   输出参数：  unsigned char * OutImage:     直方图修正后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHistogramCorrect( unsigned char * InImage, int Width, int Height, int PixelFormat,
											   int Type, int * dHist, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viHistogramEqu
*	功能：		对图像进行直方图均衡化
*	入口参数：	unsigned char * InImage：     读入的图像数据
*               int Width：                   图像宽（列数）
*               int Height：                  图像高（行数）
*               int PixelFormat：             像素类型（24或8）
*               int Type：                    直方图修正类型：
*                                             0 --- 在YCrCb域对Y分量做
*                                             1 --- 对R、G、B三分量分别做
*   输出参数：  unsigned char * OutImage:     直方图修正后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viHistogramEqu( unsigned char * InImage, int Width, int Height, int PixelFormat,
										   int Type, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viGainOffsetCorrect
*	功能：	    图像的增益/偏移修正
*	入口参数：	unsigned char * InImage：     读入的图像数据
*               int Width：                   图像宽（列数）
*               int Height：                  图像高（行数）
*               int PixelFormat：             像素类型（24或8）
*               int Rmin：                    输入图像灰度最小值
*               int Rmax：                    输入图像灰度最大值
*               int Dmin：                    结果图像灰度最小值，为一个0---255的整数值
*               int Dmax：                    结果图像灰度最大值，范围0---255
*                                             Gain = (Dmax-Offset)/(Rmax-Rmin)即为增益
*   输出参数：  unsigned char * OutImage:     直方图修正后的图像
*	返回值：	无
*/
/************************************************************************/
VIIMAGE_API void __stdcall viGainOffsetCorrect( unsigned char * InImage, int Width, int Height, int PixelFormat,
											    int Rmin, int Rmax, int Dmin, int Dmax, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viFrequencyFiltering
*	功能：		对图像进行频率域滤波
*
*                       1  D<= D0               1                     -D(u,v)^2/2D0^2
*       低通：  H(u,v)=          ; H(u,v)=------------------; H(u,v)=e
*                       0  D> D0           1+[D(u,v)/D0]^2n
*
*                       0  D<= D0               1                       -D(u,v)^2/2D0^2
*       高通：  H(u,v)=          ; H(u,v)=------------------; H(u,v)=1-e
*                       1  D> D0           1+[D0/D(u,v)]^2n
*
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int FilterType：             滤波器类型
*                                            0 - 带陷滤波器（去直流）；
*                                            1 - ILPF；2 - BLPF；3 - GLPF
*                                            4 - IHPF；5 - BHPF；6 - GHPF
*               int D0：                     滤波半径D0(为一个万分比0---10000)
*               int n：                      Butterworth滤波器的阶数(>= 1)       
*   输出参数：  unsigned char * OutImage：   滤波后的图像
*	返回值：	无
*   说明：
*               输入图像只能为8位灰度图像。参数n只对Butterworth滤波器有效
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFrequencyFiltering( unsigned char * InImage, int Width, int Height,
												 int FilterType, int D0, int n, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viFastFrequencyFiltering
*	功能：		对图像进行快速频率域滤波（采用FFT）
*
*                       1  D<= D0               1                     -D(u,v)^2/2D0^2
*       低通：  H(u,v)=          ; H(u,v)=------------------; H(u,v)=e
*                       0  D> D0           1+[D(u,v)/D0]^2n
*
*                       0  D<= D0               1                       -D(u,v)^2/2D0^2
*       高通：  H(u,v)=          ; H(u,v)=------------------; H(u,v)=1-e
*                       1  D> D0           1+[D0/D(u,v)]^2n
*
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int FilterType：             滤波器类型
*                                            0 - 带陷滤波器（去直流）；
*                                            1 - ILPF；2 - BLPF；3 - GLPF
*                                            4 - IHPF；5 - BHPF；6 - GHPF
*               int D0：                     滤波半径D0(为一个万分比0---10000)
*               int n：                      Butterworth滤波器的阶数(>= 1)       
*   输出参数：  unsigned char * OutImage：   滤波后的图像
*	返回值：	无
*   说明：
*               输入图像只能为8位灰度图像。参数n只对Butterworth滤波器有效
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastFrequencyFiltering( unsigned char * InImage, int Width, int Height,
													 int FilterType, int D0, int n, unsigned char * OutImage );

/* 12 基本图像处理函数：图像变换 */

/************************************************************************/
/*  函数名：	viFDFT1Df
*	功能：		对一维序列进行Fourier正变换
*	入口参数：	double * xRe：               读入序列的实部
*               double * xIm：               序列虚部
*               int n：                      序列长度
*   输出参数：  double * yRe：               变换后的序列的实部
*               double * yIm：               变换后的序列的虚部
*	返回值：	无
*   说明:       本函数采用了快速FFT技术，能对任意的序列进行快速变换
*               注意序列长度须 < 65537 
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFDFT1Df( double * xRe, double * xIm, int n,
									  double * yRe, double * yIm );

/************************************************************************/
/*  函数名：	viIDFT1Df
*	功能：		对一维序列进行Fourier正变换
*	入口参数：	double * xRe：               读入序列的实部
*               double * xIm：               序列虚部
*               int n：                      序列长度
*   输出参数：  double * yRe：               反变换后的序列的实部
*               double * yIm：               反变换后的序列的虚部
*	返回值：	无
*   说明:       本函数采用了快速FFT技术，能对任意的序列进行快速变换
*               注意序列长度须 < 65537 
*/
/************************************************************************/
VIIMAGE_API void __stdcall viIDFT1Df( double * xRe, double * xIm, int n,
									  double * yRe, double * yIm );

/************************************************************************/
/*  函数名：	viFFT2D
*	功能：		对图像进行FFT变换
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int OutType：                0 --- 输出实部/虚部（缺省）
*                                            1 --- 输出幅值/相位
*   输出参数：  double * RAImage:            变换后的图像的实部/幅值
*               double * IPImage:            变换后的图像的虚部/相位
*	返回值：	> 0 变换正确；<= 0 未进行变换
*   说明:       本函数要求输入图像为8位灰度图象，且宽、高为2的幂次
*/
/************************************************************************/
VIIMAGE_API int __stdcall viFFT2D( unsigned char * InImage, int Width, int Height,
								   int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  函数名：	viFFT2Df
*	功能：		对图像进行FFT变换(浮点运算版)
*	入口参数：	double * RealData：          数据块实部
*               double * ImagData：          数据块虚部
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int OutType：                0 --- 输出实部/虚部（缺省）
*                                            1 --- 输出幅值/相位
*   输出参数：  double * RAImage:            变换后的图像的实部/幅值
*               double * IPImage:            变换后的图像的虚部/相位
*	返回值：	> 0 变换正确；<= 0 未进行变换
*   说明:       本函数要求输入图像为8位灰度图象，且宽、高为2的幂次
*/
/************************************************************************/
VIIMAGE_API int __stdcall viFFT2Df( double * RealData, double * ImagData, int Width, int Height,
								    int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  函数名：	viIFFT2D
*	功能：		对图像进行FFT反变换
*	入口参数：	double * RAImage:            FFT变换后的图像的实部/幅值
*               double * IPImage:            FFT变换后的图像的虚部/相位
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int InType：                 输入数据类型：
*                                            0 --- 实部/虚部（缺省）
*                                            1 --- 幅值/相位
*   输出参数：  unsigned char * OutImage：   输出图像数据
*	返回值：	> 0 反变换正确；<= 0 未进行反变换
*   说明:       本函数输出图像为8位灰度图象，且宽、高为2的幂次
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIFFT2D( double * RAImage, double * IPImage, int Width, int Height,
								    int InType, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viIFFT2Df
*	功能：		对图像进行FFT反变换(浮点运算版)
*	入口参数：	double * RAImage:            FFT变换后的图像的实部/幅值
*               double * IPImage:            FFT变换后的图像的虚部/相位
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int InType：                 输入数据类型：
*                                            0 --- 实部/虚部（缺省）
*                                            1 --- 幅值/相位
*   输出参数：  unsigned char * RealData：   输出图像数据实部
*               unsigned char * ImagData：   输出图像数据虚部
*	返回值：	> 0 反变换正确；<= 0 未进行反变换
*   说明:       本函数输出图像为8位灰度图象，且宽、高为2的幂次
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIFFT2Df( double * RAImage, double * IPImage, int Width, int Height,
								     int InType, double * RealData, double * ImagData );

/************************************************************************/
/*  函数名：	viDFT2D
*	功能：		对图像进行DFT变换
*	入口参数：	unsigned char * InImage：    读入的图像数据
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int OutType：                0 --- 输出实部/虚部（缺省）
*                                            1 --- 输出幅值/相位
*   输出参数：  double * RAImage:            变换后的图像的实部/幅值
*               double * IPImage:            变换后的图像的虚部/相位
*	返回值：	> 0 变换正确；<= 0 未进行变换
*   说明:       本函数要求输入图像为8位灰度图象，图像宽、高无要求
*/
/************************************************************************/
VIIMAGE_API int __stdcall viDFT2D( unsigned char * InImage, int Width, int Height,
								   int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  函数名：	viDFT2Df
*	功能：		对图像进行DFT变换(浮点运算版)
*	入口参数：	double * RealData：          读入的图像数据实部
*               double * ImagData：          读入的图像数据虚部
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int OutType：                0 --- 输出实部/虚部（缺省）
*                                            1 --- 输出幅值/相位
*   输出参数：  double * RAImage:            变换后的图像的实部/幅值
*               double * IPImage:            变换后的图像的虚部/相位
*	返回值：	> 0 变换正确；<= 0 未进行变换
*   说明:       本函数要求输入图像为8位灰度图象，图像宽、高无要求
*/
/************************************************************************/
VIIMAGE_API int __stdcall viDFT2Df( double * RealData, double * ImagData, int Width, int Height,
								    int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  函数名：	viIDFT2D
*	功能：		对图像进行DFT反变换
*	入口参数：	double * RAImage:            DFT变换后的图像的实部/幅值
*               double * IPImage:            DFT变换后的图像的虚部/相位
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int InType：                 输入数据类型：
*                                            0 --- 实部/虚部（缺省）
*                                            1 --- 幅值/相位
*   输出参数：  unsigned char * OutImage：   输出图像数据
*	返回值：	> 0 反变换正确；<= 0 未进行反变换
*   说明:       本函数输出图像为8位灰度图象，对图像宽、高无要求
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIDFT2D( double * RAImage, double * IPImage, int Width, int Height,
								    int InType, unsigned char * OutImage );

/************************************************************************/
/*  函数名：	viIDFT2Df
*	功能：		对图像进行DFT反变换(浮点运算版)
*	入口参数：	double * RAImage:            DFT变换后的图像的实部/幅值
*               double * IPImage:            DFT变换后的图像的虚部/相位
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int InType：                 输入数据类型：
*                                            0 --- 实部/虚部（缺省）
*                                            1 --- 幅值/相位
*   输出参数：  double * RealData：          输出图像数据实部
*               double * ImagData：          输出图像数据虚部
*	返回值：	> 0 反变换正确；<= 0 未进行反变换
*   说明:       本函数输出图像为8位灰度图象，对图像宽、高无要求
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIDFT2Df( double * RAImage, double * IPImage, int Width, int Height,
								     int InType, double * RealData, double * ImagData );

/************************************************************************/
/*  函数名：	viDFT2Df2
*	功能：		对图像进行快速DFT变换(浮点运算版)
*	入口参数：	double * RealData：          读入的图像数据实部
*               double * ImagData：          读入的图像数据虚部
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int OutType：                0 --- 输出实部/虚部（缺省）
*                                            1 --- 输出幅值/相位
*   输出参数：  double * RAImage:            变换后的图像的实部/幅值
*               double * IPImage:            变换后的图像的虚部/相位
*	返回值：	> 0 变换正确；<= 0 未进行变换
*   说明:       本函数要求输入图像为8位灰度图象，图像宽、高无要求
*/
/************************************************************************/
VIIMAGE_API int __stdcall viDFT2Df2( double * RealData, double * ImagData, int Width, int Height,
									 int OutType, double * RAImage, double * IPImage );

/************************************************************************/
/*  函数名：	viIDFT2Df2
*	功能：		对图像进行快速DFT反变换(浮点运算版)
*	入口参数：	double * RAImage:            DFT变换后的图像的实部/幅值
*               double * IPImage:            DFT变换后的图像的虚部/相位
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int InType：                 输入数据类型：
*                                            0 --- 实部/虚部（缺省）
*                                            1 --- 幅值/相位
*   输出参数：  double * RealData：          输出图像数据实部
*               double * ImagData：          输出图像数据虚部
*	返回值：	> 0 反变换正确；<= 0 未进行反变换
*   说明:       本函数输出图像为8位灰度图象，对图像宽、高无要求
*/
/************************************************************************/
VIIMAGE_API int __stdcall viIDFT2Df2( double * RAImage, double * IPImage, int Width, int Height,
									  int InType, double * RealData, double * ImagData );

/************************************************************************/
/*  函数名：	viFastDCT8x8
*	功能：		对8x8灰度图像块进行快速DCT变换
*	入口参数：	unsigned char * Image8x8:    原始8x8图像
*   输出参数：  double * Coeff8x8：          输出8x8 DCT变换系数
*	返回值：	无
*   说明:       本函数输入/输出均为8x8的数据块，输入宽、高都须为8
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastDCT8x8( unsigned char * Image8x8, double * Coeff8x8 );

/************************************************************************/
/*  函数名：	viFastIDCT8x8
*	功能：		对8x8数据块进行快速DCT反变换
*	入口参数：	double * Coeff8x8：          输入8x8 DCT变换系数
*   输出参数：  unsigned char * Image8x8:    输出反变换8x8图像
*	返回值：	无
*   说明:       本函数输入/输出均为8x8的数据块，输入宽、高都须为8
*/
/************************************************************************/
VIIMAGE_API void __stdcall viFastIDCT8x8( double * Coeff8x8, unsigned char * Image8x8 );

/************************************************************************/
/*  函数名：	viWaveletDecom2D
*	功能：		对二维数据块进行小波分解（Mallat算法）
*	入口参数：	double * image:        图像数据块
*               int width, height:     图像宽、高，须为2的倍数(参考说明部分)
*               double * Hi:           分解高通滤波器系数
*               int n_Hi:              分解高通滤波器长度
*               double * Lo:           分解低通滤波器系数
*               int n_Lo:              分解低通滤波器长度
*               int levels:            小波分解级数
*   输出参数：  double * wavelet_data: 小波分解后的数据
*	返回值：	二维小波分解层数
*   说明:       本函数输入数据块的宽、高为 2^levels * M，其中M为任意正整数，
*               levels>=1。若不满足这一条件，前面满足的数据进行分解，尾数保持原样
*               wavelet_data的数据排列为（以2级分解为例）：
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
/*  函数名：	viWaveletRecon2D
*	功能：		对二维数据块进行小波重构（Mallat算法）
*	入口参数：	double * wavelet_data: 小波系数
*               int width, height:     图像宽、高，须为2的倍数(参考说明部分)
*               double * Hi:           重构高通滤波器系数
*               int n_Hi:              重构高通滤波器长度
*               double * Lo:           重构低通滤波器系数
*               int n_Lo:              重构低通滤波器长度
*               int levels:            小波重构级数
*   输出参数：  double * image:        重构图像数据块
*	返回值：	二维小波重构层数
*   说明:       本函数输入数据块的宽、高为 2^levels * M，其中M为任意正整数，
*               levels>=1。若不满足这一条件，前面满足的数据进行重构，尾数保持原样
*               wavelet_data的数据排列为（以2级分解为例）：
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
/*  函数名：	viWaveletDecom2DR
*	功能：		对二维数据块进行一阶小波分解且不进行下采样（Mallat算法）
*	入口参数：	double * image:        图像数据块
*               int width, height:     图像宽、高，须为2的倍数
*               double * Hi:           分解高通滤波器系数
*               int n_Hi:              分解高通滤波器长度
*               double * Lo:           分解低通滤波器系数
*               int n_Lo:              分解低通滤波器长度
*   输出参数：  double * approximation: 小波分解后的逼近数据
*               double * detail_h:     小波分解后的水平细节
*               double * detail_v:     小波分解后的垂直细节
*               double * detail_d:     小波分解后的对角细节
*	返回值：	二维小波分解层数（为1）
*   说明:       本函数输入数据块的宽、高为 2M，其中M为任意正整数
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaveletDecom2DR(  double * image, int width, int height,
										   	  double * Hi, int n_Hi, double * Lo, int n_Lo,
											  double * approximation, double * detail_h,
											  double * detail_v, double * detail_d );

/************************************************************************/
/*  函数名：	viWaveletRecon2DR
*	功能：		对二维数据块进行一阶小波重构且不进行插值（Mallat算法）
*	入口参数：	double * approximation: 小波逼近数据
*               double * detail_h:      小波水平细节
*               double * detail_v:      小波垂直细节
*               double * detail_d:      小波对角细节
*               int width, height:      图像宽、高，须为2的倍数
*               double * Hi:            重构高通滤波器系数
*               int n_Hi:               重构高通滤波器长度
*               double * Lo:            重构低通滤波器系数
*               int n_Lo:               重构低通滤波器长度
*   输出参数：  double * image:         重构图像数据块
*	返回值：	二维小波重构层数（为1）
*   说明:       本函数输入数据块的宽、高为 2M，其中M为任意正整数
*/
/************************************************************************/
VIIMAGE_API int __stdcall viWaveletRecon2DR( double * approximation, double * detail_h,
											 double * detail_v, double * detail_d, 
											 int width, int height,
										   	 double * Hi, int n_Hi, double * Lo, int n_Lo,
											 double * image );

/************************************************************************/
/*  函数名：	viLifting53Decom2D
*	功能：		对二维数据块进行lifting 5/3小波分解（整数到整数的变换）
*	入口参数：	int * image:           图像数据块
*               int width, height:     图像宽、高，须为2的倍数（参考说明部分）
*               int levels:            分解层数
*   输出参数：  int * wavelet_data:    采用lifting 5/3小波分解后的系数
*	返回值：	二维小波分解层数
*   说明:       本函数输入数据块的宽、高为 2^levels * M，其中M为任意正整数，
*               levels>=1。若不满足这一条件，前面满足的数据进行重构，尾数保持原样
*               wavelet_data的数据排列为（以2级分解为例）：
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
/*  函数名：	viLifting53Recon2D
*	功能：		对二维数据块进行lifting 5/3小波重构（整数到整数的变换）
*	入口参数：	int * wavelet_data:    采用lifting 5/3小波分解后的系数
*               int width, height:     图像宽、高，须为2的倍数（参考说明部分）
*               int levels:            重构层数
*   输出参数：  int * image:           重构图像数据块
*	返回值：	二维小波重构层数
*   说明:       本函数输入数据块的宽、高为 2^levels * M，其中M为任意正整数，
*               levels>=1。若不满足这一条件，前面满足的数据进行重构，尾数保持原样
*               wavelet_data的数据排列为（以2级分解为例）：
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
/*  函数名：	viSplusPDecom2D
*	功能：		对二维数据块进行S+P分解（整数到整数的变换）
*	入口参数：	int * I:               图像数据块
*               int width, height:     图像宽、高，须为2的倍数（参考说明部分）
*               int n_levels:          分解层数
*               int predictor_type:    预测器类型，可为1，2，3代表A、B、C三类，缺省B类
*   输出参数：  int * SP:              采用S+P分解后的系数
*	返回值：	二维S+P分解层数
*   说明:       本函数输入数据块的宽、高为 2^levels * M，其中M为任意正整数，
*               levels>=1。若不满足这一条件，前面满足的数据进行重构，尾数保持原样
*               SP的数据排列为（以2级分解为例）：
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
/*  函数名：	viSplusPRecon2D
*	功能：		对二维数据块进行S+P重构（整数到整数的变换）
*	入口参数：	int * SP:              采用S+P分解后的系数
*               int width, height:     图像宽、高，须为2的倍数（参考说明部分）
*               int n_levels:          分解层数
*               int predictor_type:    预测器类型，可为1，2，3代表A、B、C三类，缺省B类
*   输出参数：  int * I:               重构图像数据块
*	返回值：	二维S+P重构层数
*   说明:       本函数输入数据块的宽、高为 2^levels * M，其中M为任意正整数，
*               levels>=1。若不满足这一条件，前面满足的数据进行重构，尾数保持原样
*               SP的数据排列为（以2级分解为例）：
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
/*  函数名：	viCensusTransform
 *	功能：		对图像进行CensusTransform
 *	入口参数：	unsigned char * InImage：    读入的图像数据
 *              int Width：                  图像宽（列数）
 *              int Height：                 图像高（行数）
 *  输出参数：  int * OutData：              变换后的结果
 *	返回值：	无
 *  说明:       (1) 输入图像必须为8位灰度图像，输出数据范围为0 - 510共511种。
 *              000000000和111111111为一种结构，都为0
 *              (2) 本函数用积分图方法进行了加速
 *              (3) 本函数未对边界进行处理，边界强制为0
 */
/************************************************************************/
void viCensusTransform( unsigned char * InImage, int Width, int Height, 
					    int * OutData );

/* 13 模式识别函数：模板匹配 */

/************************************************************************/
/*  函数名：	viSAD
*	功能：		求两幅同尺寸的图像的SAD值（sum of the absolute difference）
*	入口参数：	unsigned char * Image1：     输入图像1
*               unsigned char * Image2：     输入图像2
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            图像格式8或者24
*	返回值：    sad值，< 0表示计算有错误
*/
/************************************************************************/
VIIMAGE_API double __stdcall viSAD( unsigned char * Image1, unsigned char * Image2, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  函数名：	viSSD
*	功能：		求两幅同尺寸的图像的SSD值（sum of the squared difference）
*	入口参数：	unsigned char * Image1：     输入图像1
*               unsigned char * Image2：     输入图像2
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            图像格式8或者24
*	返回值：    ssd值，< 0表示计算有错误
*/
/************************************************************************/
VIIMAGE_API double __stdcall viSSD( unsigned char * Image1, unsigned char * Image2, int Width, int Height, 
								    int PixelFormat );

/************************************************************************/
/*  函数名：	viNCC
*	功能：		求两幅同尺寸的图像的NCC值（normalized cross-correlation）
*	入口参数：	unsigned char * Image1：     输入图像1
*               unsigned char * Image2：     输入图像2
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int PixelFormat：            图像格式8或者24
*	返回值：    NCC值
*/
/************************************************************************/
VIIMAGE_API double __stdcall viNCC( unsigned char * Image1, unsigned char * Image2, int Width, int Height, 
								    int PixelFormat );

/* 14 图像处理函数：彩色图像分割 */

/************************************************************************/
/*  函数名：	viColorBlobExtract
*	功能：		对彩色图像提取给定颜色的Blob的函数
*	入口参数：	unsigned char * cImage：     输入彩色图像，必须为24位真彩色
*               int Width：                  图像宽（列数）
*               int Height：                 图像高（行数）
*               int R, G, B：                彩色中心颜色（各分量必须为0---255）
*               int dR, dG, dB：             各颜色分量允许的偏移量，即(R-dR,R+dR)范围的颜色都属于合格R色
*               bool IfCopy：                是否将每个Blob区域拷贝到BLOBREGION的BlobImage中(true为拷贝)
*   输出参数：  BLOBREGION **blobregions：   每个blob块的左上角坐标和宽、高(有效块从序号1开始，
*                                            blobregions[0]未用)
*	返回值：    寻找到的区域数量，顺序放在blobregions数组中；
*               负值表示求取错误
*   使用方法：
*      （1）主程序定义一个指针：BLOBREGION * blobregions;
*	   （2）调用本函数：        viColorBlobExtract( cImage, Width, Height, R, G, B, dR, dG, dB, false, &blobregions );
*	   （3）在主函数中释放内存：viFreeBlobRegion( &blobregions );
*   说明：
*               该函数几乎没有blob个数的限制（最大可为2^31个blob）    
*/
/************************************************************************/
VIIMAGE_API int __stdcall viColorBlobExtract( unsigned char * cImage, int Width, int Height, int R, int G, int B, 
											  int dR, int dG, int dB, bool IfCopy, BLOBREGION ** blobregions );

#endif