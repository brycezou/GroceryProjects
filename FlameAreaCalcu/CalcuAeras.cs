using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;


namespace FlameAreaCalcu
{
    public class CalcuAeras
    {
        public bool bSuccessful = false;
        public static double PIX_DIS_RATIO;
        public static string AERA_UNIT;
        public const string LIB_PATH = "CalcuAreas.dll";
        public Bitmap mHistImg = new Bitmap(256, 200, PixelFormat.Format24bppRgb);
        public static int HIST_LOW_VALUE;
        public static int HIST_HIGH_VALUE;

        [DllImport(LIB_PATH, EntryPoint = "?releaseImage@@YAXXZ")]
        private static extern void releaseImage();
        public void NReleaseImage()
        {
            if (bSuccessful)
            {
                releaseImage();
                bSuccessful = false;
            }
        }

        [DllImport(LIB_PATH, EntryPoint = "?getSrcImage@@YAPAEXZ")]
        unsafe private static extern byte* getSrcImage();
        unsafe public Bitmap NGetSrcImage()
        {
            int width = getWidth();
            int height = getHeight();
            byte* dst = getSrcImage();

            Bitmap outImg = new Bitmap(width, height, PixelFormat.Format24bppRgb);
            BitmapData data = outImg.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            IntPtr Scan0 = data.Scan0;
            int stride = data.Stride;
            unsafe
            {
                byte* p = (byte*)Scan0;
                int offset = stride - width * 3;
                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        int index = 3 * (y * width + x);
                        p[0] = dst[index + 2];
                        p[1] = dst[index + 1];
                        p[2] = dst[index];
                        p += 3;
                    }
                    p += offset;
                }
            }
            outImg.UnlockBits(data);

            return outImg;
        }

        [DllImport(LIB_PATH, EntryPoint = "?getDstImage@@YAPAEXZ")]
        unsafe private static extern byte* getDstImage();
        unsafe public Bitmap NGetDstImage2()
        {
            int width = getWidth();
            int height = getHeight();
            byte* dst = getDstImage();

            Bitmap outImg = new Bitmap(width, height, PixelFormat.Format24bppRgb);
            BitmapData data = outImg.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            IntPtr Scan0 = data.Scan0;
            int stride = data.Stride;
            unsafe
            {
                byte* p = (byte*)Scan0;
                int offset = stride - width * 3;
                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        int index = 3 * (y * width + x);
                        p[0] = dst[index+2];
                        p[1] = dst[index+1];
                        p[2] = dst[index];
                        p += 3;
                    }
                    p += offset;
                }
            }
            outImg.UnlockBits(data);

            return outImg;
        }

        [DllImport(LIB_PATH, EntryPoint = "?getWidth@@YAHXZ")]
        private static extern int getWidth();
        public int NGetWidth()
        {
            return getWidth();
        }

        [DllImport(LIB_PATH, EntryPoint = "?getHeight@@YAHXZ")]
        private static extern int getHeight();
        public int NGetHeight()
        {
            return getHeight();
        }

        [DllImport(LIB_PATH, EntryPoint = "?getAera@@YANXZ")]
        private static extern double getAera();
        public double NGetAera()
        {
            return getAera();
        }

        [DllImport(LIB_PATH, EntryPoint = "?loadImage_2Threshold@@YA_NPAD@Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool loadImage_2Threshold(string filePath);
        public void NLoadImage_2Threshold(string filePath)
        {
            bSuccessful = loadImage_2Threshold(filePath);
        }

        [DllImport(LIB_PATH, EntryPoint = "?binaryImage_2Threshold@@YAXMPAD0HH@Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern void binaryImage_2Threshold(float ratio, string strUnit, string strPrefix, int lowT, int highT);
        public void NBinaryImage_2Threshold(float ratio, string strUnit, string strPrefix, int lowT, int highT)
        {
            if (bSuccessful)
            {
                binaryImage_2Threshold(ratio, strUnit, strPrefix, lowT, highT);
            }
        }

        [DllImport(LIB_PATH, EntryPoint = "?setText_2Threshold@@YAXPADM_NHHHH@Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern void setText_2Threshold(string strPrefix, float len, bool bLeft, int x1, int y1, int x2, int y2);
        public void NSetText_2Threshold(string strPrefix, float len, bool bLeft, int x1, int y1, int x2, int y2)
        {
            if (bSuccessful)
            {
                setText_2Threshold(strPrefix, len, bLeft, x1, y1, x2, y2);
            }
        }

        public void NGetHistImage(Bitmap bmp)
        {
            int gray;
            int[] histArray = new int[256];
            for (int i = 0; i < bmp.Height; i++)
            {
                for (int j = 0; j < bmp.Width; j++ )
                {
                    int index = 3 * (i * bmp.Width + j);
                    Color color = bmp.GetPixel(j, i);
                    int r = Convert.ToInt32(color.R);
                    int g = Convert.ToInt32(color.G);
                    int b = Convert.ToInt32(color.B);
                    gray = (int)(0.2990 * r + 0.5870 * g + 0.1140 * b);
                    histArray[gray]++;
                }
            }

            int maxValue = 1, ValueY;
            for (int i = 0; i < 256; i++)
                maxValue = maxValue < histArray[i] ? histArray[i] : maxValue;

            // 清空直方图
            for (int x = 0; x < 256; x++)
            {
                for (int y = 0; y < 200; y++)
                {
                    mHistImg.SetPixel(x, y, Color.Black);
                }
            }

            // 绘制直方图
            for (int x = 0; x < 256; x++)
            {
                ValueY = histArray[x] * 200 / maxValue;
                ValueY = ValueY <= 0 ? 0 : (ValueY > 199 ? 199 : ValueY); // 限制在0-200间
                for (int y = 199; y >= (199 - ValueY); y--)
                {
                    mHistImg.SetPixel(x, y, Color.White);
                }
            }
        }

    }
}
