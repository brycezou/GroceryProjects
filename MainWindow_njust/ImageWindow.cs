using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;


namespace MainWindow_njust
{
    public partial class ImageWindow : Form
    {
        public ImageWindow(string strIP)
        {
            InitializeComponent();
            GetPicture(strIP);
        }

        private void GetPicture(string strIP)
        {
            string strURL = "http://" + strIP + ":80/cap.jpg";
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(strURL);
            request.Method = "GET";
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            if (response.StatusCode != HttpStatusCode.OK)
            {
                MessageBox.Show("获取图片失败!");
                return;
            }

            Image image = Image.FromStream(response.GetResponseStream());
            this.pictureBox.Image = image;
            response.Close();
        }

        private void ImageWindow_Load(object sender, EventArgs e)
        {

        }

    }
}
