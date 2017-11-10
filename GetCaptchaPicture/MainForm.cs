using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.IO;


namespace GetCaptchaPicture
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            this.textBox_prefix.Text = "default";
        }

        private long GetUnixTime(DateTime nowTime)
        {
            DateTime startTime = TimeZone.CurrentTimeZone.ToLocalTime(new DateTime(1970, 1, 1, 0, 0, 0, 0));
            return (long)Math.Round((nowTime - startTime).TotalMilliseconds, MidpointRounding.AwayFromZero);
        }

        private void button_get_Click(object sender, EventArgs e)
        {
            string strUrl = this.textBox_url.Text.Trim();
            if (!strUrl.Equals(""))
            {
                try
                {
                    Uri uri = new Uri(strUrl);
                    HttpWebRequest request = (HttpWebRequest) HttpWebRequest.Create(uri);
                    HttpWebResponse response = (HttpWebResponse) request.GetResponse();
                    Stream stream = response.GetResponseStream();
                    Bitmap bmp = new Bitmap(stream);
                    this.pictureBox.Image = bmp;
                    string strPrefix = this.textBox_prefix.Text.Trim();
                    if (strPrefix.Equals(""))
                        bmp.Save(String.Format("{0}_{1}.bmp", "default", GetUnixTime(DateTime.Now)));
                    else
                        bmp.Save(String.Format("{0}_{1}.bmp", strPrefix, GetUnixTime(DateTime.Now)));
                }
                catch (System.Exception)
                {
                    MessageBox.Show("获取失败, 请检查验证码链接!");
                }
            }
        }
    }
}
