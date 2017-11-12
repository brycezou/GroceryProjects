using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TransparentWindow
{
    public partial class SettingWindow : Form
    {
        private int mAlpha;
        private Color mColor;
        private Bitmap mBmp;
        private MainWindow mMWindow;

        public SettingWindow(MainWindow mw)
        {
            InitializeComponent();
            this.mColor = Color.Black;
            this.mAlpha = 102;   //255*0.4
            this.mMWindow = mw;
            this.mBmp = new Bitmap(150, 50, PixelFormat.Format32bppArgb);
        }

        private void SettingWindow_Load(object sender, EventArgs e)
        {
            RefreshShowImage();
            this.trackBar.Value = 40;
        }

        private void button_setColor_Click(object sender, EventArgs e)
        {
            if (this.colorDialog.ShowDialog() == DialogResult.OK)
            {
                this.mColor = this.colorDialog.Color;
                RefreshShowImage();
            }
        }

        private void trackBar_ValueChanged(object sender, EventArgs e)
        {
            this.label_alpha.Text = this.trackBar.Value + "%";
            mAlpha = this.trackBar.Value*255/100;
            RefreshShowImage();
        }

        private void SetImagePureColor(Bitmap bmp, Color color, int alpha)
        {
            for (int i = 0; i < bmp.Width; i++)
            {
                for (int j = 0; j < bmp.Height; j++)
                {
                    bmp.SetPixel(i, j, Color.FromArgb(alpha, color.R, color.G, color.B));
                }
            }
        }

        private void RefreshShowImage()
        {
            SetImagePureColor(this.mBmp, this.mColor, this.mAlpha);
            this.pictureBox.Image = this.mBmp;
        }

        private void button_cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_ok_Click(object sender, EventArgs e)
        {
            SetImagePureColor(this.mMWindow.mBkgImg, this.mColor, this.mAlpha);
            this.mMWindow.UpdateMainBackgroundImage();
            this.Close();
        }
    }
}
