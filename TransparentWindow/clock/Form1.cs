/************************************************************************************
*源码来自(C#源码世界)  www.HelloCsharp.com
*如果对该源码有问题可以直接点击下方的提问按钮进行提问哦
*站长将亲自帮你解决问题
*C#源码世界-找到你需要的C#源码，交流和学习
************************************************************************************/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;


namespace clock
{
    public partial class Form1 : Form
    {
        Bitmap b = new Bitmap(global::clock.Properties.Resources.bkg);
        Bitmap h = new Bitmap(global::clock.Properties.Resources.met2000);
        Bitmap m = new Bitmap(global::clock.Properties.Resources.met2002);
        Bitmap s = new Bitmap(global::clock.Properties.Resources.met2004);

        public Form1()
        {
            InitializeComponent();
        }

        public static Bitmap Rotate(Bitmap b, int angle)//图片旋转
        {
            angle =360 - angle % 360;

            double radian = angle * Math.PI / 180.0;
            double cos = Math.Cos(radian);
            double sin = Math.Sin(radian);

            //目标位图
            Bitmap dsImage = new Bitmap(b.Width, b.Height);
            Graphics g = Graphics.FromImage(dsImage);
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.Bilinear;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

            ////构造图像显示区域：让图像的中心与窗口的中心点一致
            Rectangle rect = new Rectangle(0, 0, b.Width, b.Height);
            Point center = new Point(rect.X + rect.Width / 2, rect.Y + rect.Height / 2);
            g.TranslateTransform(center.X, center.Y);
            g.RotateTransform(360 - angle);
            //恢复图像在水平和垂直方向的平移
            g.TranslateTransform(-center.X, -center.Y);
            g.DrawImage(b, rect);
            //重至绘图的所有变换
            g.ResetTransform();
            g.Dispose();
            return dsImage;
        }

        #region 窗体移动
        [DllImport("user32.dll")]
        public static extern bool ReleaseCapture();
        [DllImport("user32.dll")]
        public static extern bool SendMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);
        public const int WM_SYSCOMMAND = 0x0112;
        public const int SC_MOVE = 0xF010;      //无边框窗体移动
        public const int HTCAPTION = 0x0002;    
        #endregion

        #region 调用UpdateLayeredWindow函数
        protected override CreateParams CreateParams
        {
            //重载窗体的CreateParams方法
            get
            {
                const int WS_MINIMIZEBOX = 0x00020000;  //Winuser.h中定义   
                CreateParams cp = base.CreateParams;
                cp.Style = cp.Style | WS_MINIMIZEBOX;       //允许最小化操作
                cp.ExStyle |= 0x00080000;                                //WS_EX_LAYERED
                return cp;
            }
        }
        public void SetBits(Bitmap bitmap)//调用UpdateLayeredWindow（）方法。this.BackgroundImage为你事先准备的带透明图片。
        {
            //if (!haveHandle) return;

            if (!Bitmap.IsCanonicalPixelFormat(bitmap.PixelFormat) || !Bitmap.IsAlphaPixelFormat(bitmap.PixelFormat))
                throw new ApplicationException("图片必须是32位带Alhpa通道的图片。");

            IntPtr oldBits = IntPtr.Zero;
            IntPtr screenDC = Win32.GetDC(IntPtr.Zero);
            IntPtr hBitmap = IntPtr.Zero;
            IntPtr memDc = Win32.CreateCompatibleDC(screenDC);

            try
            {
                Win32.Point topLoc = new Win32.Point(Left, Top);
                Win32.Size bitMapSize = new Win32.Size(bitmap.Width, bitmap.Height);
                Win32.BLENDFUNCTION blendFunc = new Win32.BLENDFUNCTION();
                Win32.Point srcLoc = new Win32.Point(0, 0);

                hBitmap = bitmap.GetHbitmap(Color.FromArgb(0));
                oldBits = Win32.SelectObject(memDc, hBitmap);

                blendFunc.BlendOp = Win32.AC_SRC_OVER;
                blendFunc.SourceConstantAlpha = 255;
                blendFunc.AlphaFormat = Win32.AC_SRC_ALPHA;
                blendFunc.BlendFlags = 0;

                Win32.UpdateLayeredWindow(Handle, screenDC, ref topLoc, ref bitMapSize, memDc, ref srcLoc, 0, ref blendFunc, Win32.ULW_ALPHA);
            }
            finally
            {
                if (hBitmap != IntPtr.Zero)
                {
                    Win32.SelectObject(memDc, oldBits);
                    Win32.DeleteObject(hBitmap);
                }
                Win32.ReleaseDC(IntPtr.Zero, screenDC);
                Win32.DeleteDC(memDc);
            }
        }
        #endregion

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage(this.Handle, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);    //窗体移动
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Bitmap bmp = new Bitmap(b);
            Graphics g = Graphics.FromImage(bmp);
            g.DrawImage(Rotate(h, DateTime.Now.Hour % 12 * 30 + DateTime.Now.Minute / 2),27,25);//时
            g.DrawImage(Rotate(m, DateTime.Now.Minute * 6),27,25);//分
            g.DrawImage(Rotate(s, DateTime.Now.Second * 6),27,25);//秒针

            SetBits(bmp);
            g.Dispose();
            bmp.Dispose();
            GC.Collect();
        }


        private void 绿色ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            b = new Bitmap(global::clock.Properties.Resources.bkg);
            h = new Bitmap(global::clock.Properties.Resources.met2000);
            m = new Bitmap(global::clock.Properties.Resources.met2002);
            s = new Bitmap(global::clock.Properties.Resources.met2004);
            蓝色ToolStripMenuItem.Checked = false;
            金属ToolStripMenuItem.Checked = false;
            黄色ToolStripMenuItem.Checked = false;
        }
        private void 蓝色ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            b = new Bitmap(global::clock.Properties.Resources.bkg1);
            h = new Bitmap(global::clock.Properties.Resources.met20001);
            m = new Bitmap(global::clock.Properties.Resources.met20021);
            s = new Bitmap(global::clock.Properties.Resources.met20041);
            绿色ToolStripMenuItem.Checked = false;
            金属ToolStripMenuItem.Checked = false;
            黄色ToolStripMenuItem.Checked = false;
        }
        private void 金属ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            b = new Bitmap(global::clock.Properties.Resources.bkg2);
            h = new Bitmap(global::clock.Properties.Resources.met20002);
            m = new Bitmap(global::clock.Properties.Resources.met20022);
            s = new Bitmap(global::clock.Properties.Resources.met20042);
            绿色ToolStripMenuItem.Checked = false;
            蓝色ToolStripMenuItem.Checked = false;
            黄色ToolStripMenuItem.Checked = false;
        }
        private void 黄色ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            b = new Bitmap(global::clock.Properties.Resources.bkg3);
            h = new Bitmap(global::clock.Properties.Resources.met20003);
            m = new Bitmap(global::clock.Properties.Resources.met20023);
            s = new Bitmap(global::clock.Properties.Resources.met20043);
            绿色ToolStripMenuItem.Checked = false;
            蓝色ToolStripMenuItem.Checked = false;
            金属ToolStripMenuItem.Checked = false;
        }
        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }

    #region Win32 API声明
    class Win32
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Size
        {
            public Int32 cx;
            public Int32 cy;

            public Size(Int32 x, Int32 y)
            {
                cx = x;
                cy = y;
            }
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct BLENDFUNCTION
        {
            public byte BlendOp;
            public byte BlendFlags;
            public byte SourceConstantAlpha;
            public byte AlphaFormat;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Point
        {
            public Int32 x;
            public Int32 y;

            public Point(Int32 x, Int32 y)
            {
                this.x = x;
                this.y = y;
            }
        }

        public const byte AC_SRC_OVER = 0;
        public const Int32 ULW_ALPHA = 2;
        public const byte AC_SRC_ALPHA = 1;

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr CreateCompatibleDC(IntPtr hDC);

        [DllImport("user32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr GetDC(IntPtr hWnd);

        [DllImport("gdi32.dll", ExactSpelling = true)]
        public static extern IntPtr SelectObject(IntPtr hDC, IntPtr hObj);

        [DllImport("user32.dll", ExactSpelling = true)]
        public static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern int DeleteDC(IntPtr hDC);

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern int DeleteObject(IntPtr hObj);

        [DllImport("user32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern int UpdateLayeredWindow(IntPtr hwnd, IntPtr hdcDst, ref Point pptDst, ref Size psize, IntPtr hdcSrc, ref Point pptSrc, Int32 crKey, ref BLENDFUNCTION pblend, Int32 dwFlags);

        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr ExtCreateRegion(IntPtr lpXform, uint nCount, IntPtr rgnData);
    }
    #endregion

}
