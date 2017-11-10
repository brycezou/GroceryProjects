#ifndef _VIAPI_
#define _VIAPI_
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define VI_API  extern "C" __declspec(dllexport)
typedef void (__stdcall *GuiMouseCallback )( int event, int x, int y, int flags, void* param );

typedef void (__stdcall *GuiTrackbarCallback)( double pos );
typedef void (__stdcall *GuiTrackbarCallback2)( double pos, void* userdata );

#define GUI_WINDOW_AUTOSIZE		1
#define GUI_WINDOW_FULLSCREEN	2

#define GUI_EVENT_MOUSEMOVE      0
#define GUI_EVENT_LBUTTONDOWN    1
#define GUI_EVENT_RBUTTONDOWN    2
#define GUI_EVENT_MBUTTONDOWN    3
#define GUI_EVENT_LBUTTONUP      4
#define GUI_EVENT_RBUTTONUP      5
#define GUI_EVENT_MBUTTONUP      6
#define GUI_EVENT_LBUTTONDBLCLK  7
#define GUI_EVENT_RBUTTONDBLCLK  8
#define GUI_EVENT_MBUTTONDBLCLK  9

#define GUI_EVENT_FLAG_LBUTTON   1
#define GUI_EVENT_FLAG_RBUTTON   2
#define GUI_EVENT_FLAG_MBUTTON   4
#define GUI_EVENT_FLAG_CTRLKEY   8
#define GUI_EVENT_FLAG_SHIFTKEY  16
#define GUI_EVENT_FLAG_ALTKEY    32

//////////////////////////////////////////////////////////////////////////

/* 1 GUI函数 */

/************************************************************************/
/*  函数名：	viNamedWindow
*	功能：		创建一个窗口
*	入口参数：	name窗口名称； flag窗口类型，目前只支持两种 GUI_WINDOW_AUTOSIZE 和 GUI_WINDOW_FULLSCREEN
*	返回值：	void
*/
/************************************************************************/
VI_API void	__stdcall viNamedWindow( const char* name, int flag = GUI_WINDOW_AUTOSIZE ) ;

/************************************************************************/
/*  函数名：	viResizeWindow
*	功能：		改变窗口大小
*	入口参数：	name窗口名称； width、height窗口宽高
*	返回值：	void
*/
/************************************************************************/
VI_API void	__stdcall viResizeWindow( const char* name, int width, int height ) ;


/************************************************************************/
/*  函数名：	viMoveWindow
*	功能：		改变窗口位置
*	入口参数：	name窗口名称； x、y窗口新位置
*	返回值：	void
*/
/************************************************************************/
VI_API void __stdcall viMoveWindow( const char* name, int x, int y );

/************************************************************************/
/*  函数名：	viDestroyWindow
*	功能：		销毁窗口
*	入口参数：	name窗口名称
*	返回值：	void
*/
/************************************************************************/
VI_API void	__stdcall viDestroyWindow(  const char* name ) ;

/************************************************************************/
/*  函数名：	viDestroyWindow
*	功能：		销毁该应用程序实例创建的所有窗口
*	入口参数：	void
*	返回值：	void
*/
/************************************************************************/
VI_API void	__stdcall viDestroyAllWindows( void ) ;

/************************************************************************/
/*  函数名：	viWaitKey
*	功能：		等待按键
*	入口参数：	delay 等待时间，单位ms； 如果delay<=0，一直等到按键
*	返回值：	void
*/
/************************************************************************/
VI_API int __stdcall viWaitKey( int delay );

/************************************************************************/
/*  函数名：	viShowImage
*	功能：		显示图片
*	入口参数：	name窗口名称， image指向图像数据的指针，width，height图像的宽高
*               pixelformat像素类型：8---灰度图像，24---24位彩色图像，
                orig为坐标原点位置：0---左上角，1---左下角
*	返回值：	void
*/
/************************************************************************/
VI_API void	__stdcall viShowImage( const char* name, unsigned char * image, int width, int height, 
							       int pixelformat, int orig ) ;

/************************************************************************/
/*  函数名：	viSetMouseCallback
*	功能：		设置鼠标响应回调函数
*	入口参数：	name窗口名称， on_mouse回调函数， 回调函数参数
*	返回值：	void
*/
/************************************************************************/
VI_API void	__stdcall viSetMouseCallback( const char* window_name, GuiMouseCallback on_mouse, void* param );

/************************************************************************/
/*  函数名：	GuiCreateInputWindow
*	功能：		创建输入窗口
*	入口参数：	void
*	返回值：	void
*/
/************************************************************************/
VI_API void	__stdcall viCreateInputWindow( void );

/************************************************************************/
/*  函数名：	viCreateTrackbar
*	功能：		创建调节块(trackbar)
*	入口参数：	trackbar_name调节块名称
*               val绑定的数值
*               minval最小值
*               maxval最大值
*               step步长
*               on_notify回调函数
*	返回值：	非0即成功，0创建失败
*/
/************************************************************************/
VI_API int __stdcall viCreateTrackbar( const char * trackbar_name,  double * val, double minval,
									   double maxval, double step, GuiTrackbarCallback on_notify );

/************************************************************************/
/*  函数名：	viCreateTrackbar2
*	功能：		创建调节块(trackbar)， 与viCreateTrackbar不同之处为回调函数
*	入口参数：	trackbar_name调节块名称
*               val绑定的数值
*               minval最小值
*               maxval最大值
*               step步长
*               on_notify2回调函数
*               userdata 可以为回调函数传递参数
*	返回值：	非0即成功，0创建失败
*/
/************************************************************************/ 
VI_API int __stdcall viCreateTrackbar2( const char * trackbar_name,  double * val, double minval, 
									    double maxval, double step,  GuiTrackbarCallback2 on_notify2, void* userdata );

/* 2 图像读写函数 */

/************************************************************************/
/*  函数名：	viGetImageWH
*	功能：		获取图像的宽和高
*	入口参数：	ImageFileName图像文件名， Width返回图像宽， Height返回图像高
*	返回值：	1 --- 正确获得；0 --- 未正确获得
*/
/************************************************************************/
VI_API int __stdcall viGetImageWH( char * ImageFileName, int &Width, int &Height ) ;

/************************************************************************/
/*  函数名：	viReadImageFile
*	功能：		读取图像数据
*	入口参数：	ImageFileName图像文件名， 
*   出口参数：  ImageData读取的图像数据，Width返回图像宽， Height返回图像高
*               PixelFormat图像格式：8为灰度图像，24为真彩色图像
*	返回值：	1 --- 正确获得；0 --- 未正确获得
*/
/************************************************************************/
VI_API int __stdcall viReadImageFile( char * ImageFileName, unsigned char * ImageData, int &Width, int &Height, 
							          int PixelFormat ) ;

/************************************************************************/
/*  函数名：	viSaveImageFile
*	功能：		保存图像数据
*	入口参数：	ImageFileName图像文件名， 
*   出口参数：  ImageData图像数据，Width图像宽， Height图像高，
*               PixelFormat图像格式：8为灰度图像，24为真彩色图像
*               JPEGQuality JPEG压缩的质量系数，在1-100中取值
*	返回值：	1 --- 正确保存；0 --- 未正确保存
*/
/************************************************************************/
VI_API int __stdcall viSaveImageFile( char * ImageFileName, unsigned char * ImageData, int Width, int Height, 
							          int PixelFormat, int JPEGQuality ) ;

/* 3 视频读写函数 */
/*
 * 定义一种函数指针类型，pFrame为图像指针
 */ 
/************************************************************************/
/*  函数名：	viOpenVideoFile
*	功能：		打开视频AVI文件
*	入口参数：	VideoFilename视频文件名
*	返回值：	1 --- 正确打开；0 --- 未正确打开
*/
/************************************************************************/
VI_API int __stdcall viOpenVideoFile( char * VideoFilename );

/************************************************************************/
/*  函数名：	viCloseVideoFile
*	功能：		关闭打开的用于读的视频AVI文件
*/
/************************************************************************/
VI_API void __stdcall viCloseVideoFile();

/************************************************************************/
/*  函数名：	viReadVideoFrame
*	功能：		读取打开的AVI文件中的一帧
*	入口参数：	Image一帧数据
*	返回值：	1 --- 正确获得；0 --- 未正确获得
*/
/************************************************************************/
VI_API int __stdcall viReadVideoFrame( unsigned char * Image );

/************************************************************************/
/*  函数名：	viReadTheVideoFrame
*	功能：		读取打开的AVI文件中的指定一帧
*	入口参数：	Image一帧数据，FrameIndex为指定帧号（从1开始计）
*	返回值：	1 --- 正确获得；0 --- 未正确获得
*/
/************************************************************************/
VI_API int __stdcall viReadTheVideoFrame( unsigned char * Image, int FrameIndex );

/************************************************************************/
/*  函数名：	viGetVideoFrameInfo
*	功能：		获取视频中的每帧图像宽、高、像素格式和总帧数
*	入口参数：	Width返回图像宽， Height返回图像高，PixelFormat图像格式，8
*               或者24，TotalFrames总帧数
*/
/************************************************************************/
VI_API void __stdcall viGetVideoFrameInfo( int & Width, int & Height, // 图像宽高
								           int & PixelFormat, // 图像格式，8位灰度或者24位彩色
								           int & TotalFrames  // 视频的总帧数
							             );

/* 另一组视频读取函数 */
/************************************************************************/
/*  函数名：	viOpenVideoFile2
*	功能：		打开视频文件(可以为MPEG，AVI等文件)
*	入口参数：	VideoFilename视频文件名
*	返回值：	1 --- 正确打开；0 --- 未正确打开
*/
/************************************************************************/
VI_API int __stdcall viOpenVideoFile2( char * VideoFilename );

/************************************************************************/
/*  函数名：	viCloseVideoFile2
*	功能：		关闭打开的用于读的视频文件
*/
/************************************************************************/
VI_API void __stdcall viCloseVideoFile2();

/************************************************************************/
/*  函数名：	viReadVideoFrame2
*	功能：		读取打开的视频文件中的指定一帧
*	入口参数：	Image一帧数据，FrameIndex为指定帧号（从0开始计）
*	返回值：	1 --- 正确获得；0 --- 未正确获得
*/
/************************************************************************/
VI_API int __stdcall viReadVideoFrame2( unsigned char * Image, int FrameIndex );

/************************************************************************/
/*  函数名：	viGetVideoFrameInfo2
*	功能：		获取视频中的每帧图像宽、高、像素格式和总帧数
*	入口参数：	Width返回图像宽， Height返回图像高，PixelFormat图像格式，8
*               或者24，TotalFrames总帧数
*/
/************************************************************************/
VI_API void __stdcall viGetVideoFrameInfo2( int & Width, int & Height, // 图像宽高
								            int & PixelFormat, // 图像格式，8位灰度或者24位彩色
								            int & TotalFrames  // 视频的总帧数
								          );

/************************************************************************/
/*  函数名：	viSaveVideoFile
*	功能：		创建视频AVI文件用于保存
*	入口参数：	VideoFilename视频文件名
*               FrameInterval为压缩的帧间时间间隔，单位ms
*               Type 为文件类型，0为avi文件，1为wmv文件 
*               CompressionType 为AVI文件压缩类型，只对AVI文件压缩有效
*               0--不压缩，1--MSVC，2--XVID，3--DIVX，4--MPG4，5--MP42
*	返回值：	1 --- 正确创建；0 --- 未正确创建
*/
/************************************************************************/
VI_API int __stdcall viSaveVideoFile( char * VideoFilename, int FrameInterval, int Type, int CompressionType );

/************************************************************************/
/*  函数名：	viCloseSaveVideo
*	功能：		关闭打开的用于保存的视频AVI文件
*/
/************************************************************************/
VI_API void __stdcall viCloseSaveVideo();

/************************************************************************/
/*  函数名：	viWriteVideoFrame
*	功能：		保存一帧图像到AVI文件中
*	入口参数：	Image一帧数据，Width图像宽，Height图像高
*	返回值：	1 --- 正确保存；0 --- 未正确保存
*/
/************************************************************************/
VI_API int __stdcall viWriteVideoFrame( unsigned char * Image, int Width, int Height );

/************************************************************************/
/*  函数名：	viCameraNumbers
*	功能：		罗列系统中的摄像头个数
*	入口参数：	无
*	返回值：	摄像头个数
*/
/************************************************************************/
VI_API int __stdcall viCameraNumbers( void );

/************************************************************************/
/*  函数名：	viOpenCapture
*	功能：		打开摄像头
*	入口参数：	DeviceID为摄像头的标号，当为-1时，由系统自动寻找第一个摄像头
*               Width, Height为摄像头的宽和高，若Width和Height为0，则用缺省值
*	返回值：	-1 --- 未打开摄像头；>= 0 --- 打开的摄像头ID号
*/
/************************************************************************/
VI_API int __stdcall viOpenCapture( int DeviceID, int Width, int Height );

/************************************************************************/
/*  函数名：	viGetCaptureWH
*	功能：		获得采集图像的宽和高
*	出口参数：	Width, Height为图像宽高
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viGetCaptureWH( int & Width, int & Height );

/************************************************************************/
/*  函数名：	viCaptureFrame
*	功能：		采集一帧图像
*	出口参数：	unsigned char * Image为24位色图像，Width, Height为图像宽高
*               PixelFormat为颜色数                 
*	返回值：	1 --- 成功，0 --- 失败
*/
/************************************************************************/
VI_API int __stdcall viCaptureFrame( unsigned char * Image, int & Width, int & Height, int & PixelFormat );

/************************************************************************/
/*  函数名：	viCloseCapture
*	功能：		关闭图像采集设备
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viCloseCapture();

/************************************************************************/
/*  函数名：	viOpenTwoCapture
*	功能：		打开双摄像头
*	入口参数：	DeviceLeftID、DeviceRightID为摄像头的标号，当其中一个为-1时，由系统
*               自动寻找分配摄像头，Width, Height为设置的摄像头的宽和高，左右
*               摄像头的宽高最好一致，若Width和Height为0，则用各摄像头的缺省值
*	返回值：	-1 --- 未打开摄像头；>= 0 --- 打开的摄像头个数
*/
/************************************************************************/
VI_API int __stdcall viOpenTwoCapture( int DeviceLeftID, int DeviceRightID, int Width, int Height );

/************************************************************************/
/*  函数名：	viGetLeftCaptureWH
*	功能：		获得左摄像头采集图像的宽和高
*	出口参数：	Width, Height为图像宽高
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viGetLeftCaptureWH( int & Width, int & Height );

/************************************************************************/
/*  函数名：	viGetRightCaptureWH
*	功能：		获得右摄像头采集图像的宽和高
*	出口参数：	Width, Height为图像宽高
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viGetRightCaptureWH( int & Width, int & Height );

/************************************************************************/
/*  函数名：	viCaptureTwoFrame
*	功能：		同时（约1/帧率的误差）采集左右摄像头各一帧图像
*	出口参数：	unsigned char * LeftImage, * RightImage为24位色图像                 
*	返回值：	1 --- 成功，0 --- 失败
*/
/************************************************************************/
VI_API int __stdcall viCaptureTwoFrame( unsigned char * LeftImage, unsigned char * RightImage );

/************************************************************************/
/*  函数名：	viCloseTwoCapture
*	功能：		关闭两摄像头
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viCloseTwoCapture();

/************************************************************************/
/*
   通过定义回调函数将获得视频文件中的每帧图像，并在应用程序中进行处理
   数据类型：回调函数函数指针
   其中：
   unsigned char * pImage:  为传出的图像数据
   int Width, Height:       为图像数据的宽和高
   int PixelFormat:         为图像数据的格式，为24
   该组函数的使用过程如下：
   （1）打开视频文件文件
   viOpenVideoFile2( "Demo.avi" );
   （2）获得文件的宽高等信息
   viGetVideoFrameInfo2( Width, Height, PixelFormat, TotalFrames );
   （3） 定义一个函数，比如
   void Processing( unsigned char * pImage, int Width, int Height, int PixelFormat);
   （4）调用设置函数
   viSetVIPCallback( Processing );
   （5）播放视频文件（在此过程中，处理图像）
   viPlayVideoFile();
   （6）关闭视频文件
   viCloseVideoFile2();
   （7）释放回调函数(可选)
   viSetVIPCallback( NULL );
*/
/************************************************************************/
typedef void ( __stdcall * VIP_FuncPtr )( unsigned char * pImage, int Width, int Height,
									      int PixelFormat );

/************************************************************
   函数名：设置视频处理回调函数
   入口参数：回调函数的函数指针
 ************************************************************/
VI_API int __stdcall viSetVIPCallback( VIP_FuncPtr vipFunAddress );

/************************************************************
   函数名：播放打开的视频文件
   返回值：正确播放 --- 1；未播放 --- 0
 ************************************************************/
VI_API int __stdcall viPlayVideoFile( long BeginFrame );

/* 4 图形函数（包括2D和3D绘图、数据可视化等） */
/************************************************************************/
/*  函数名：	viDrawRectangle
*	功能：		在一幅矩形图像上画一个矩形
*   入口参数:   Canvas为一幅图像，Width和Height为图像宽高，PixelFormat为图像
*               像素格式：24为彩色图像，8为灰度图。top、left、w、h分别为所画
*               矩形的左上角坐标和矩形宽高；Thickness为线宽，为1-3；线颜色为
*               Color，对24位彩色图格式为0x00rrggbb，8位灰度图为0xgg
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawRectangle( unsigned char * Canvas, int Width, int Height, int PixelFormat, 
						               int top, int left, int w, int h, int Thickness, int Color );

/************************************************************************/
/*  函数名：	viDrawRectangle2
*	功能：		在一幅图像上画一个任意角度旋转的矩形
*   入口参数:   Canvas:           为一幅图像
*               Width,Height:     为图像宽高
*               PixelFormat:      为图像像素格式：24为彩色图像，8为灰度图。
*               x0, y0, wh, hh:   分别为所画矩形的中心坐标和矩形半宽高
*               Theta:            矩形倾斜角，角度为单位，与y轴方向夹角，顺时针为正
*               Thickness:        为线宽，为1-3
*               Color:            线颜色，对24位彩色图格式为0x00rrggbb，8位灰度图为0xgg
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawRectangle2( unsigned char * Canvas, int Width, int Height, int PixelFormat, 
										int x0, int y0, int wh, int hh, double Theta, int Thickness, int Color );

/************************************************************************/
/*  函数名：	viDrawEllipse
*	功能：		在一幅图像上画一个任意角度旋转的矩形
*   入口参数:   Canvas:           为一幅图像
*               Width,Height:     为图像宽高
*               PixelFormat:      为图像像素格式：24为彩色图像，8为灰度图。
*               Xc, Yc:           分别为所画椭圆的中心X，Y坐标
*               a,b:              为椭圆的半长轴和半短轴
*               Theta:            椭圆倾斜角，角度为单位，与y轴方向夹角，顺时针为正
*               Thickness:        为线宽，为1-3
*               Color:            线颜色，对24位彩色图格式为0x00rrggbb，8位灰度图为0xgg
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawEllipse( unsigned char * Canvas, int Width, int Height, int PixelFormat,
									 int Xc, int Yc, int a, int b, double Theta, int Thickness, int Color );

/************************************************************************/
/*  函数名：	viDrawCross
*	功能：		在一幅图像上画一个十字
*   入口参数:   Canvas:           为一幅图像
*               Width,Height:     为图像宽高
*               PixelFormat:      为图像像素格式：24为彩色图像，8为灰度图。
*               Xc, Yc:           分别为所画十字的中心X，Y坐标
*               a, b:             为十字的半长
*               Thickness:        为线宽，为1-3
*               Color:            线颜色，对24位彩色图格式为0x00rrggbb，8位灰度图为0xgg
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawCross( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								   int Xc, int Yc, int a, int b, int Thickness, int Color );

/************************************************************************/
/*  函数名：	viDrawLine2（直线的Bresenham算法）
*	功能：		在一幅图像上画任意角度的线
*	入口参数：	Canvas:           一幅图像
*               Width,Height:     图像宽高
*               PixelFormat:      图像像素格式：24为彩色图像，8为灰度图
*               xa,ya:            直线的起点
*               xb,yb:            直线的终点
*               Color:            字符颜色，对24位彩色为0x00rrggbb，8位灰度图为0xgg
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawLine2( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								   int xa, int ya, int xb, int yb, int Color );

/************************************************************************/
/*  函数名：	viDrawLine（直线的DDA(数值微分)算法）
*	功能：		在一幅图像上画任意角度的线
*	入口参数：	Canvas:           一幅图像
*               Width,Height:     图像宽高
*               PixelFormat:      图像像素格式：24为彩色图像，8为灰度图
*               xa,ya:            直线的起点
*               xb,yb:            直线的终点
*               Color:            字符颜色，对24位彩色为0x00rrggbb，8位灰度图为0xgg
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawLine( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								  int xa, int ya, int xb, int yb, int Color );

/************************************************************************/
/*  函数名：	viDrawText
*	功能：		在一幅图像上写一串文字
*	入口参数：	Canvas:           一幅图像
*               Width,Height:     图像宽高
*               PixelFormat:      图像像素格式：24为彩色图像，8为灰度图
*               top,left:         要写的文字的左上角坐标
*               Text:             要叠加的字符串
*               w,h:              每个字符的期望宽、高（真实宽高由字体决定）
*               Color:            字符颜色，对24位彩色为0x00rrggbb，8位灰度图为0xgg
*               BkColor:          背景颜色，若为0，则不进行alpha调制
*               Alpha:            透明度（0---1）
*               Direction:        0 --- 水平显示，1 --- 垂直显示
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawText( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								  int top, int left, char * Text, int w, int h, int Color, int BkColor, 
								  float Alpha, int Direction );

/************************************************************************/
/*  函数名：	viDrawImage
*	功能：		在一幅图像的某个区域上叠加显示另一幅图像
*	入口参数：	Canvas:           一幅图像
*               Width,Height:     图像宽高
*               PixelFormat:      图像像素格式：24为彩色图像，8为灰度图
*               top, left:        要显示的图像的左上角坐标
*               w, h:             图像的宽、高
*               image:            要叠加的图像
*               ImageType:        图像类型：0 --- 二值黑白（0和255），1 --- 8位灰度，
*                                           2 --- 24位真彩色。
*               Color:            图像颜色，对24位彩色为0x00rrggbb，8位灰度图为0xgg
*               BkColor:          背景颜色，若为0，则不进行alpha调制
*               Alpha:            透明度（0---1）
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDrawImage( unsigned char * Canvas, int Width, int Height, 
								   int PixelFormat, int top, int left, int w, int h, 
								   unsigned char * image, int ImageType, int Color, 
								   int BkColor, double Alpha );

/************************************************************************/
/*  函数名：	viHistogram
*	功能：		计算彩色/灰度图像的直方图
*	入口参数：	Image:            图像数据块
*               Width, Height:    为图像宽高
*               PixelFormat:      PixelFormat为图像像素格式：24为彩色图像，8为灰度图
*               grHistogram[256]: 图像的灰度直方图
*               rHistogram[256]:  图像红色分量直方图
*               gHistogram[256]:  图像绿色分量直方图
*               bHistogram[256]:  图像兰色分量直方图
*               HistType:         直方图类型，0 --- 线性； 1 --- 对数
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viHistogram( unsigned char * Image, int Width, int Height, int PixelFormat, 
								   int grHistogram[256], int rHistogram[256], int gHistogram[256], 
								   int bHistogram[256], int HistType );

/************************************************************************/
/*  函数名：	viDisplayHistogram
*	功能：		显示彩色/灰度图像的直方图
*               一般先用viNameWindow函数创建一个窗口，然后调用本函数显示直方图，
*               最后可以用viDestroyWindow删除窗口
*	入口参数：	grHistogram[256]: 图像的灰度直方图，为NULL则不显示
*               rHistogram[256]:  图像红色分量直方图，为NULL则不显示
*               gHistogram[256]:  图像绿色分量直方图，为NULL则不显示
*               bHistogram[256]:  图像兰色分量直方图，为NULL则不显示
*               WindowName:       窗口名称，为一字符串，由viNameWindow创建
*               Type:             直方图显示类型，0 --- 折线；1 --- 竖条（bin）显示
*               HistFilename:     保存直方图文件名称，若为NULL，则表示不保存
*	返回值：	无
*/
/************************************************************************/
VI_API void __stdcall viDisplayHistogram( int grHistogram[256], int rHistogram[256], int gHistogram[256], 
										  int bHistogram[256], char * WindowName, int Type, char * HistFilename );

#endif
