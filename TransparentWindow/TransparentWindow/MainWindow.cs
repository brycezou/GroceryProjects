using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TransparentWindow
{
    public partial class MainWindow : Form
    {
        public Bitmap mBkgImg = new Bitmap(global::TransparentWindow.Properties.Resources.bkg_gray);

        public MainWindow()
        {
            InitializeComponent();
            DrawImage2Window();
            this.notifyIcon.ShowBalloonTip(2, "提示", "时刻准备保护小主的眼睛！\n右击 召唤我 ^_^\n", ToolTipIcon.Info);
            this.WindowState = FormWindowState.Maximized;
            this.Visible = true;
        }

        private void DrawImage2Window()
        {
            //Bitmap bmp = new Bitmap(mBkgImg);
            //Graphics gfks = Graphics.FromImage(bmp);
            //gfks.DrawImage(new Bitmap(global::TransparentWindow.Properties.Resources.red), 0, 0);
            //gfks.DrawString("Hello World!", new Font("Times New Roman", 44f), Brushes.Yellow, new PointF(100, 20));
            //SetBitmaps(bmp);
            //gfks.Dispose();
            //bmp.Dispose();
            SetBitmaps(mBkgImg);
        }

        private void MainWindow_MouseDown(object sender, MouseEventArgs e)
        {
            //MoveWin32.Move(this.Handle);
        }

        #region 调用UpdateLayeredWindow函数
        protected override CreateParams CreateParams
        {
            get     //重载窗体的CreateParams方法
            {
                const int WS_MINIMIZEBOX = 0x00020000;  //Winuser.h中定义   
                CreateParams cp = base.CreateParams;
                cp.Style = cp.Style | WS_MINIMIZEBOX;       //允许最小化操作
                cp.ExStyle |= 0x00080000;                                //WS_EX_LAYERED
                return cp;
            }
        }
        //调用UpdateLayeredWindow方法，bitmap为带透明度的图片
        public void SetBitmaps(Bitmap bitmap)
        {
            if (!Bitmap.IsCanonicalPixelFormat(bitmap.PixelFormat) || !Bitmap.IsAlphaPixelFormat(bitmap.PixelFormat))
            {
                MessageBox.Show("图片必须是32位带Alhpa通道的图片");
                return;
            }

            IntPtr oldBits = IntPtr.Zero;
            IntPtr hBitmap = IntPtr.Zero;
            IntPtr screenDc = DrawWin32.GetDC(IntPtr.Zero);
            IntPtr memDc = DrawWin32.CreateCompatibleDC(screenDc);

            try
            {
                DrawWin32.BLENDFUNCTION blendFunc = new DrawWin32.BLENDFUNCTION();
                blendFunc.BlendFlags = 0;
                blendFunc.SourceConstantAlpha = 255;
                blendFunc.BlendOp = DrawWin32.AC_SRC_OVER;
                blendFunc.AlphaFormat = DrawWin32.AC_SRC_ALPHA;

                DrawWin32.POINT srcLoc = new DrawWin32.POINT(0, 0);
                DrawWin32.POINT topLoc = new DrawWin32.POINT(Left, Top);
                DrawWin32.SIZE bitMapSize = new DrawWin32.SIZE(bitmap.Width, bitmap.Height);
                hBitmap = bitmap.GetHbitmap(Color.FromArgb(0));
                oldBits = DrawWin32.SelectObject(memDc, hBitmap);

                DrawWin32.UpdateLayeredWindow(Handle, screenDc, ref topLoc, ref bitMapSize, memDc, ref srcLoc, 0, ref blendFunc, DrawWin32.ULW_ALPHA);
            }
            finally
            {
                if (hBitmap != IntPtr.Zero)
                {
                    DrawWin32.SelectObject(memDc, oldBits);
                    DrawWin32.DeleteObject(hBitmap);
                }
                DrawWin32.ReleaseDC(IntPtr.Zero, screenDc);
                DrawWin32.DeleteDC(memDc);
            }
        }
        #endregion

        private void 最大化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Maximized;
            this.Visible = true;
        }

        private void 最小化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
            this.Visible = false;
        }

        private void 设置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SettingWindow sw = new SettingWindow(this);
            sw.Show();
        }

        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public void UpdateMainBackgroundImage()
        {
            SetBitmaps(mBkgImg);
            this.WindowState = FormWindowState.Minimized;
            this.Visible = false;
            this.WindowState = FormWindowState.Maximized;
            this.Visible = true;
        }
    }
}
