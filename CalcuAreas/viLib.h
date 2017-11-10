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

/* 1 GUI���� */

/************************************************************************/
/*  ��������	viNamedWindow
*	���ܣ�		����һ������
*	��ڲ�����	name�������ƣ� flag�������ͣ�Ŀǰֻ֧������ GUI_WINDOW_AUTOSIZE �� GUI_WINDOW_FULLSCREEN
*	����ֵ��	void
*/
/************************************************************************/
VI_API void	__stdcall viNamedWindow( const char* name, int flag = GUI_WINDOW_AUTOSIZE ) ;

/************************************************************************/
/*  ��������	viResizeWindow
*	���ܣ�		�ı䴰�ڴ�С
*	��ڲ�����	name�������ƣ� width��height���ڿ��
*	����ֵ��	void
*/
/************************************************************************/
VI_API void	__stdcall viResizeWindow( const char* name, int width, int height ) ;


/************************************************************************/
/*  ��������	viMoveWindow
*	���ܣ�		�ı䴰��λ��
*	��ڲ�����	name�������ƣ� x��y������λ��
*	����ֵ��	void
*/
/************************************************************************/
VI_API void __stdcall viMoveWindow( const char* name, int x, int y );

/************************************************************************/
/*  ��������	viDestroyWindow
*	���ܣ�		���ٴ���
*	��ڲ�����	name��������
*	����ֵ��	void
*/
/************************************************************************/
VI_API void	__stdcall viDestroyWindow(  const char* name ) ;

/************************************************************************/
/*  ��������	viDestroyWindow
*	���ܣ�		���ٸ�Ӧ�ó���ʵ�����������д���
*	��ڲ�����	void
*	����ֵ��	void
*/
/************************************************************************/
VI_API void	__stdcall viDestroyAllWindows( void ) ;

/************************************************************************/
/*  ��������	viWaitKey
*	���ܣ�		�ȴ�����
*	��ڲ�����	delay �ȴ�ʱ�䣬��λms�� ���delay<=0��һֱ�ȵ�����
*	����ֵ��	void
*/
/************************************************************************/
VI_API int __stdcall viWaitKey( int delay );

/************************************************************************/
/*  ��������	viShowImage
*	���ܣ�		��ʾͼƬ
*	��ڲ�����	name�������ƣ� imageָ��ͼ�����ݵ�ָ�룬width��heightͼ��Ŀ��
*               pixelformat�������ͣ�8---�Ҷ�ͼ��24---24λ��ɫͼ��
                origΪ����ԭ��λ�ã�0---���Ͻǣ�1---���½�
*	����ֵ��	void
*/
/************************************************************************/
VI_API void	__stdcall viShowImage( const char* name, unsigned char * image, int width, int height, 
							       int pixelformat, int orig ) ;

/************************************************************************/
/*  ��������	viSetMouseCallback
*	���ܣ�		���������Ӧ�ص�����
*	��ڲ�����	name�������ƣ� on_mouse�ص������� �ص���������
*	����ֵ��	void
*/
/************************************************************************/
VI_API void	__stdcall viSetMouseCallback( const char* window_name, GuiMouseCallback on_mouse, void* param );

/************************************************************************/
/*  ��������	GuiCreateInputWindow
*	���ܣ�		�������봰��
*	��ڲ�����	void
*	����ֵ��	void
*/
/************************************************************************/
VI_API void	__stdcall viCreateInputWindow( void );

/************************************************************************/
/*  ��������	viCreateTrackbar
*	���ܣ�		�������ڿ�(trackbar)
*	��ڲ�����	trackbar_name���ڿ�����
*               val�󶨵���ֵ
*               minval��Сֵ
*               maxval���ֵ
*               step����
*               on_notify�ص�����
*	����ֵ��	��0���ɹ���0����ʧ��
*/
/************************************************************************/
VI_API int __stdcall viCreateTrackbar( const char * trackbar_name,  double * val, double minval,
									   double maxval, double step, GuiTrackbarCallback on_notify );

/************************************************************************/
/*  ��������	viCreateTrackbar2
*	���ܣ�		�������ڿ�(trackbar)�� ��viCreateTrackbar��֮ͬ��Ϊ�ص�����
*	��ڲ�����	trackbar_name���ڿ�����
*               val�󶨵���ֵ
*               minval��Сֵ
*               maxval���ֵ
*               step����
*               on_notify2�ص�����
*               userdata ����Ϊ�ص��������ݲ���
*	����ֵ��	��0���ɹ���0����ʧ��
*/
/************************************************************************/ 
VI_API int __stdcall viCreateTrackbar2( const char * trackbar_name,  double * val, double minval, 
									    double maxval, double step,  GuiTrackbarCallback2 on_notify2, void* userdata );

/* 2 ͼ���д���� */

/************************************************************************/
/*  ��������	viGetImageWH
*	���ܣ�		��ȡͼ��Ŀ�͸�
*	��ڲ�����	ImageFileNameͼ���ļ����� Width����ͼ��� Height����ͼ���
*	����ֵ��	1 --- ��ȷ��ã�0 --- δ��ȷ���
*/
/************************************************************************/
VI_API int __stdcall viGetImageWH( char * ImageFileName, int &Width, int &Height ) ;

/************************************************************************/
/*  ��������	viReadImageFile
*	���ܣ�		��ȡͼ������
*	��ڲ�����	ImageFileNameͼ���ļ����� 
*   ���ڲ�����  ImageData��ȡ��ͼ�����ݣ�Width����ͼ��� Height����ͼ���
*               PixelFormatͼ���ʽ��8Ϊ�Ҷ�ͼ��24Ϊ���ɫͼ��
*	����ֵ��	1 --- ��ȷ��ã�0 --- δ��ȷ���
*/
/************************************************************************/
VI_API int __stdcall viReadImageFile( char * ImageFileName, unsigned char * ImageData, int &Width, int &Height, 
							          int PixelFormat ) ;

/************************************************************************/
/*  ��������	viSaveImageFile
*	���ܣ�		����ͼ������
*	��ڲ�����	ImageFileNameͼ���ļ����� 
*   ���ڲ�����  ImageDataͼ�����ݣ�Widthͼ��� Heightͼ��ߣ�
*               PixelFormatͼ���ʽ��8Ϊ�Ҷ�ͼ��24Ϊ���ɫͼ��
*               JPEGQuality JPEGѹ��������ϵ������1-100��ȡֵ
*	����ֵ��	1 --- ��ȷ���棻0 --- δ��ȷ����
*/
/************************************************************************/
VI_API int __stdcall viSaveImageFile( char * ImageFileName, unsigned char * ImageData, int Width, int Height, 
							          int PixelFormat, int JPEGQuality ) ;

/* 3 ��Ƶ��д���� */
/*
 * ����һ�ֺ���ָ�����ͣ�pFrameΪͼ��ָ��
 */ 
/************************************************************************/
/*  ��������	viOpenVideoFile
*	���ܣ�		����ƵAVI�ļ�
*	��ڲ�����	VideoFilename��Ƶ�ļ���
*	����ֵ��	1 --- ��ȷ�򿪣�0 --- δ��ȷ��
*/
/************************************************************************/
VI_API int __stdcall viOpenVideoFile( char * VideoFilename );

/************************************************************************/
/*  ��������	viCloseVideoFile
*	���ܣ�		�رմ򿪵����ڶ�����ƵAVI�ļ�
*/
/************************************************************************/
VI_API void __stdcall viCloseVideoFile();

/************************************************************************/
/*  ��������	viReadVideoFrame
*	���ܣ�		��ȡ�򿪵�AVI�ļ��е�һ֡
*	��ڲ�����	Imageһ֡����
*	����ֵ��	1 --- ��ȷ��ã�0 --- δ��ȷ���
*/
/************************************************************************/
VI_API int __stdcall viReadVideoFrame( unsigned char * Image );

/************************************************************************/
/*  ��������	viReadTheVideoFrame
*	���ܣ�		��ȡ�򿪵�AVI�ļ��е�ָ��һ֡
*	��ڲ�����	Imageһ֡���ݣ�FrameIndexΪָ��֡�ţ���1��ʼ�ƣ�
*	����ֵ��	1 --- ��ȷ��ã�0 --- δ��ȷ���
*/
/************************************************************************/
VI_API int __stdcall viReadTheVideoFrame( unsigned char * Image, int FrameIndex );

/************************************************************************/
/*  ��������	viGetVideoFrameInfo
*	���ܣ�		��ȡ��Ƶ�е�ÿ֡ͼ����ߡ����ظ�ʽ����֡��
*	��ڲ�����	Width����ͼ��� Height����ͼ��ߣ�PixelFormatͼ���ʽ��8
*               ����24��TotalFrames��֡��
*/
/************************************************************************/
VI_API void __stdcall viGetVideoFrameInfo( int & Width, int & Height, // ͼ����
								           int & PixelFormat, // ͼ���ʽ��8λ�ҶȻ���24λ��ɫ
								           int & TotalFrames  // ��Ƶ����֡��
							             );

/* ��һ����Ƶ��ȡ���� */
/************************************************************************/
/*  ��������	viOpenVideoFile2
*	���ܣ�		����Ƶ�ļ�(����ΪMPEG��AVI���ļ�)
*	��ڲ�����	VideoFilename��Ƶ�ļ���
*	����ֵ��	1 --- ��ȷ�򿪣�0 --- δ��ȷ��
*/
/************************************************************************/
VI_API int __stdcall viOpenVideoFile2( char * VideoFilename );

/************************************************************************/
/*  ��������	viCloseVideoFile2
*	���ܣ�		�رմ򿪵����ڶ�����Ƶ�ļ�
*/
/************************************************************************/
VI_API void __stdcall viCloseVideoFile2();

/************************************************************************/
/*  ��������	viReadVideoFrame2
*	���ܣ�		��ȡ�򿪵���Ƶ�ļ��е�ָ��һ֡
*	��ڲ�����	Imageһ֡���ݣ�FrameIndexΪָ��֡�ţ���0��ʼ�ƣ�
*	����ֵ��	1 --- ��ȷ��ã�0 --- δ��ȷ���
*/
/************************************************************************/
VI_API int __stdcall viReadVideoFrame2( unsigned char * Image, int FrameIndex );

/************************************************************************/
/*  ��������	viGetVideoFrameInfo2
*	���ܣ�		��ȡ��Ƶ�е�ÿ֡ͼ����ߡ����ظ�ʽ����֡��
*	��ڲ�����	Width����ͼ��� Height����ͼ��ߣ�PixelFormatͼ���ʽ��8
*               ����24��TotalFrames��֡��
*/
/************************************************************************/
VI_API void __stdcall viGetVideoFrameInfo2( int & Width, int & Height, // ͼ����
								            int & PixelFormat, // ͼ���ʽ��8λ�ҶȻ���24λ��ɫ
								            int & TotalFrames  // ��Ƶ����֡��
								          );

/************************************************************************/
/*  ��������	viSaveVideoFile
*	���ܣ�		������ƵAVI�ļ����ڱ���
*	��ڲ�����	VideoFilename��Ƶ�ļ���
*               FrameIntervalΪѹ����֡��ʱ��������λms
*               Type Ϊ�ļ����ͣ�0Ϊavi�ļ���1Ϊwmv�ļ� 
*               CompressionType ΪAVI�ļ�ѹ�����ͣ�ֻ��AVI�ļ�ѹ����Ч
*               0--��ѹ����1--MSVC��2--XVID��3--DIVX��4--MPG4��5--MP42
*	����ֵ��	1 --- ��ȷ������0 --- δ��ȷ����
*/
/************************************************************************/
VI_API int __stdcall viSaveVideoFile( char * VideoFilename, int FrameInterval, int Type, int CompressionType );

/************************************************************************/
/*  ��������	viCloseSaveVideo
*	���ܣ�		�رմ򿪵����ڱ������ƵAVI�ļ�
*/
/************************************************************************/
VI_API void __stdcall viCloseSaveVideo();

/************************************************************************/
/*  ��������	viWriteVideoFrame
*	���ܣ�		����һ֡ͼ��AVI�ļ���
*	��ڲ�����	Imageһ֡���ݣ�Widthͼ���Heightͼ���
*	����ֵ��	1 --- ��ȷ���棻0 --- δ��ȷ����
*/
/************************************************************************/
VI_API int __stdcall viWriteVideoFrame( unsigned char * Image, int Width, int Height );

/************************************************************************/
/*  ��������	viCameraNumbers
*	���ܣ�		����ϵͳ�е�����ͷ����
*	��ڲ�����	��
*	����ֵ��	����ͷ����
*/
/************************************************************************/
VI_API int __stdcall viCameraNumbers( void );

/************************************************************************/
/*  ��������	viOpenCapture
*	���ܣ�		������ͷ
*	��ڲ�����	DeviceIDΪ����ͷ�ı�ţ���Ϊ-1ʱ����ϵͳ�Զ�Ѱ�ҵ�һ������ͷ
*               Width, HeightΪ����ͷ�Ŀ�͸ߣ���Width��HeightΪ0������ȱʡֵ
*	����ֵ��	-1 --- δ������ͷ��>= 0 --- �򿪵�����ͷID��
*/
/************************************************************************/
VI_API int __stdcall viOpenCapture( int DeviceID, int Width, int Height );

/************************************************************************/
/*  ��������	viGetCaptureWH
*	���ܣ�		��òɼ�ͼ��Ŀ�͸�
*	���ڲ�����	Width, HeightΪͼ����
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viGetCaptureWH( int & Width, int & Height );

/************************************************************************/
/*  ��������	viCaptureFrame
*	���ܣ�		�ɼ�һ֡ͼ��
*	���ڲ�����	unsigned char * ImageΪ24λɫͼ��Width, HeightΪͼ����
*               PixelFormatΪ��ɫ��                 
*	����ֵ��	1 --- �ɹ���0 --- ʧ��
*/
/************************************************************************/
VI_API int __stdcall viCaptureFrame( unsigned char * Image, int & Width, int & Height, int & PixelFormat );

/************************************************************************/
/*  ��������	viCloseCapture
*	���ܣ�		�ر�ͼ��ɼ��豸
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viCloseCapture();

/************************************************************************/
/*  ��������	viOpenTwoCapture
*	���ܣ�		��˫����ͷ
*	��ڲ�����	DeviceLeftID��DeviceRightIDΪ����ͷ�ı�ţ�������һ��Ϊ-1ʱ����ϵͳ
*               �Զ�Ѱ�ҷ�������ͷ��Width, HeightΪ���õ�����ͷ�Ŀ�͸ߣ�����
*               ����ͷ�Ŀ�����һ�£���Width��HeightΪ0�����ø�����ͷ��ȱʡֵ
*	����ֵ��	-1 --- δ������ͷ��>= 0 --- �򿪵�����ͷ����
*/
/************************************************************************/
VI_API int __stdcall viOpenTwoCapture( int DeviceLeftID, int DeviceRightID, int Width, int Height );

/************************************************************************/
/*  ��������	viGetLeftCaptureWH
*	���ܣ�		���������ͷ�ɼ�ͼ��Ŀ�͸�
*	���ڲ�����	Width, HeightΪͼ����
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viGetLeftCaptureWH( int & Width, int & Height );

/************************************************************************/
/*  ��������	viGetRightCaptureWH
*	���ܣ�		���������ͷ�ɼ�ͼ��Ŀ�͸�
*	���ڲ�����	Width, HeightΪͼ����
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viGetRightCaptureWH( int & Width, int & Height );

/************************************************************************/
/*  ��������	viCaptureTwoFrame
*	���ܣ�		ͬʱ��Լ1/֡�ʵ����ɼ���������ͷ��һ֡ͼ��
*	���ڲ�����	unsigned char * LeftImage, * RightImageΪ24λɫͼ��                 
*	����ֵ��	1 --- �ɹ���0 --- ʧ��
*/
/************************************************************************/
VI_API int __stdcall viCaptureTwoFrame( unsigned char * LeftImage, unsigned char * RightImage );

/************************************************************************/
/*  ��������	viCloseTwoCapture
*	���ܣ�		�ر�������ͷ
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viCloseTwoCapture();

/************************************************************************/
/*
   ͨ������ص������������Ƶ�ļ��е�ÿ֡ͼ�񣬲���Ӧ�ó����н��д���
   �������ͣ��ص���������ָ��
   ���У�
   unsigned char * pImage:  Ϊ������ͼ������
   int Width, Height:       Ϊͼ�����ݵĿ�͸�
   int PixelFormat:         Ϊͼ�����ݵĸ�ʽ��Ϊ24
   ���麯����ʹ�ù������£�
   ��1������Ƶ�ļ��ļ�
   viOpenVideoFile2( "Demo.avi" );
   ��2������ļ��Ŀ�ߵ���Ϣ
   viGetVideoFrameInfo2( Width, Height, PixelFormat, TotalFrames );
   ��3�� ����һ������������
   void Processing( unsigned char * pImage, int Width, int Height, int PixelFormat);
   ��4���������ú���
   viSetVIPCallback( Processing );
   ��5��������Ƶ�ļ����ڴ˹����У�����ͼ��
   viPlayVideoFile();
   ��6���ر���Ƶ�ļ�
   viCloseVideoFile2();
   ��7���ͷŻص�����(��ѡ)
   viSetVIPCallback( NULL );
*/
/************************************************************************/
typedef void ( __stdcall * VIP_FuncPtr )( unsigned char * pImage, int Width, int Height,
									      int PixelFormat );

/************************************************************
   ��������������Ƶ����ص�����
   ��ڲ������ص������ĺ���ָ��
 ************************************************************/
VI_API int __stdcall viSetVIPCallback( VIP_FuncPtr vipFunAddress );

/************************************************************
   �����������Ŵ򿪵���Ƶ�ļ�
   ����ֵ����ȷ���� --- 1��δ���� --- 0
 ************************************************************/
VI_API int __stdcall viPlayVideoFile( long BeginFrame );

/* 4 ͼ�κ���������2D��3D��ͼ�����ݿ��ӻ��ȣ� */
/************************************************************************/
/*  ��������	viDrawRectangle
*	���ܣ�		��һ������ͼ���ϻ�һ������
*   ��ڲ���:   CanvasΪһ��ͼ��Width��HeightΪͼ���ߣ�PixelFormatΪͼ��
*               ���ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ��top��left��w��h�ֱ�Ϊ����
*               ���ε����Ͻ�����;��ο�ߣ�ThicknessΪ�߿�Ϊ1-3������ɫΪ
*               Color����24λ��ɫͼ��ʽΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawRectangle( unsigned char * Canvas, int Width, int Height, int PixelFormat, 
						               int top, int left, int w, int h, int Thickness, int Color );

/************************************************************************/
/*  ��������	viDrawRectangle2
*	���ܣ�		��һ��ͼ���ϻ�һ������Ƕ���ת�ľ���
*   ��ڲ���:   Canvas:           Ϊһ��ͼ��
*               Width,Height:     Ϊͼ����
*               PixelFormat:      Ϊͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ��
*               x0, y0, wh, hh:   �ֱ�Ϊ�������ε���������;��ΰ���
*               Theta:            ������б�ǣ��Ƕ�Ϊ��λ����y�᷽��нǣ�˳ʱ��Ϊ��
*               Thickness:        Ϊ�߿�Ϊ1-3
*               Color:            ����ɫ����24λ��ɫͼ��ʽΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawRectangle2( unsigned char * Canvas, int Width, int Height, int PixelFormat, 
										int x0, int y0, int wh, int hh, double Theta, int Thickness, int Color );

/************************************************************************/
/*  ��������	viDrawEllipse
*	���ܣ�		��һ��ͼ���ϻ�һ������Ƕ���ת�ľ���
*   ��ڲ���:   Canvas:           Ϊһ��ͼ��
*               Width,Height:     Ϊͼ����
*               PixelFormat:      Ϊͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ��
*               Xc, Yc:           �ֱ�Ϊ������Բ������X��Y����
*               a,b:              Ϊ��Բ�İ볤��Ͱ����
*               Theta:            ��Բ��б�ǣ��Ƕ�Ϊ��λ����y�᷽��нǣ�˳ʱ��Ϊ��
*               Thickness:        Ϊ�߿�Ϊ1-3
*               Color:            ����ɫ����24λ��ɫͼ��ʽΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawEllipse( unsigned char * Canvas, int Width, int Height, int PixelFormat,
									 int Xc, int Yc, int a, int b, double Theta, int Thickness, int Color );

/************************************************************************/
/*  ��������	viDrawCross
*	���ܣ�		��һ��ͼ���ϻ�һ��ʮ��
*   ��ڲ���:   Canvas:           Ϊһ��ͼ��
*               Width,Height:     Ϊͼ����
*               PixelFormat:      Ϊͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ��
*               Xc, Yc:           �ֱ�Ϊ����ʮ�ֵ�����X��Y����
*               a, b:             Ϊʮ�ֵİ볤
*               Thickness:        Ϊ�߿�Ϊ1-3
*               Color:            ����ɫ����24λ��ɫͼ��ʽΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawCross( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								   int Xc, int Yc, int a, int b, int Thickness, int Color );

/************************************************************************/
/*  ��������	viDrawLine2��ֱ�ߵ�Bresenham�㷨��
*	���ܣ�		��һ��ͼ���ϻ�����Ƕȵ���
*	��ڲ�����	Canvas:           һ��ͼ��
*               Width,Height:     ͼ����
*               PixelFormat:      ͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*               xa,ya:            ֱ�ߵ����
*               xb,yb:            ֱ�ߵ��յ�
*               Color:            �ַ���ɫ����24λ��ɫΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawLine2( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								   int xa, int ya, int xb, int yb, int Color );

/************************************************************************/
/*  ��������	viDrawLine��ֱ�ߵ�DDA(��ֵ΢��)�㷨��
*	���ܣ�		��һ��ͼ���ϻ�����Ƕȵ���
*	��ڲ�����	Canvas:           һ��ͼ��
*               Width,Height:     ͼ����
*               PixelFormat:      ͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*               xa,ya:            ֱ�ߵ����
*               xb,yb:            ֱ�ߵ��յ�
*               Color:            �ַ���ɫ����24λ��ɫΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawLine( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								  int xa, int ya, int xb, int yb, int Color );

/************************************************************************/
/*  ��������	viDrawText
*	���ܣ�		��һ��ͼ����дһ������
*	��ڲ�����	Canvas:           һ��ͼ��
*               Width,Height:     ͼ����
*               PixelFormat:      ͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*               top,left:         Ҫд�����ֵ����Ͻ�����
*               Text:             Ҫ���ӵ��ַ���
*               w,h:              ÿ���ַ����������ߣ���ʵ��������������
*               Color:            �ַ���ɫ����24λ��ɫΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*               BkColor:          ������ɫ����Ϊ0���򲻽���alpha����
*               Alpha:            ͸���ȣ�0---1��
*               Direction:        0 --- ˮƽ��ʾ��1 --- ��ֱ��ʾ
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawText( unsigned char * Canvas, int Width, int Height, int PixelFormat,
								  int top, int left, char * Text, int w, int h, int Color, int BkColor, 
								  float Alpha, int Direction );

/************************************************************************/
/*  ��������	viDrawImage
*	���ܣ�		��һ��ͼ���ĳ�������ϵ�����ʾ��һ��ͼ��
*	��ڲ�����	Canvas:           һ��ͼ��
*               Width,Height:     ͼ����
*               PixelFormat:      ͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*               top, left:        Ҫ��ʾ��ͼ������Ͻ�����
*               w, h:             ͼ��Ŀ���
*               image:            Ҫ���ӵ�ͼ��
*               ImageType:        ͼ�����ͣ�0 --- ��ֵ�ڰף�0��255����1 --- 8λ�Ҷȣ�
*                                           2 --- 24λ���ɫ��
*               Color:            ͼ����ɫ����24λ��ɫΪ0x00rrggbb��8λ�Ҷ�ͼΪ0xgg
*               BkColor:          ������ɫ����Ϊ0���򲻽���alpha����
*               Alpha:            ͸���ȣ�0---1��
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDrawImage( unsigned char * Canvas, int Width, int Height, 
								   int PixelFormat, int top, int left, int w, int h, 
								   unsigned char * image, int ImageType, int Color, 
								   int BkColor, double Alpha );

/************************************************************************/
/*  ��������	viHistogram
*	���ܣ�		�����ɫ/�Ҷ�ͼ���ֱ��ͼ
*	��ڲ�����	Image:            ͼ�����ݿ�
*               Width, Height:    Ϊͼ����
*               PixelFormat:      PixelFormatΪͼ�����ظ�ʽ��24Ϊ��ɫͼ��8Ϊ�Ҷ�ͼ
*               grHistogram[256]: ͼ��ĻҶ�ֱ��ͼ
*               rHistogram[256]:  ͼ���ɫ����ֱ��ͼ
*               gHistogram[256]:  ͼ����ɫ����ֱ��ͼ
*               bHistogram[256]:  ͼ����ɫ����ֱ��ͼ
*               HistType:         ֱ��ͼ���ͣ�0 --- ���ԣ� 1 --- ����
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viHistogram( unsigned char * Image, int Width, int Height, int PixelFormat, 
								   int grHistogram[256], int rHistogram[256], int gHistogram[256], 
								   int bHistogram[256], int HistType );

/************************************************************************/
/*  ��������	viDisplayHistogram
*	���ܣ�		��ʾ��ɫ/�Ҷ�ͼ���ֱ��ͼ
*               һ������viNameWindow��������һ�����ڣ�Ȼ����ñ�������ʾֱ��ͼ��
*               ��������viDestroyWindowɾ������
*	��ڲ�����	grHistogram[256]: ͼ��ĻҶ�ֱ��ͼ��ΪNULL����ʾ
*               rHistogram[256]:  ͼ���ɫ����ֱ��ͼ��ΪNULL����ʾ
*               gHistogram[256]:  ͼ����ɫ����ֱ��ͼ��ΪNULL����ʾ
*               bHistogram[256]:  ͼ����ɫ����ֱ��ͼ��ΪNULL����ʾ
*               WindowName:       �������ƣ�Ϊһ�ַ�������viNameWindow����
*               Type:             ֱ��ͼ��ʾ���ͣ�0 --- ���ߣ�1 --- ������bin����ʾ
*               HistFilename:     ����ֱ��ͼ�ļ����ƣ���ΪNULL�����ʾ������
*	����ֵ��	��
*/
/************************************************************************/
VI_API void __stdcall viDisplayHistogram( int grHistogram[256], int rHistogram[256], int gHistogram[256], 
										  int bHistogram[256], char * WindowName, int Type, char * HistFilename );

#endif
