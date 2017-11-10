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
        //抓图对话框类的构造函数
        public ImageWindow(string strIP)
        {
            InitializeComponent(); //初始化组件, 自动生成
            GetPicture(strIP); //抓图
        }

        //抓图功能函数
        private void GetPicture(string strIP)
        {
            string strURL = "http://" + strIP + ":80/cap.jpg"; //创建图片URL
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(strURL);
            request.Method = "GET"; //设置HTTP方法为GET
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            if (response.StatusCode != HttpStatusCode.OK) //如果HTTP请求失败
            {
                MessageBox.Show("获取图片失败!");
                return;
            }

            //从返回的数据流中构造图像
            Image image = Image.FromStream(response.GetResponseStream());
            this.pictureBox.Image = image; //显示图像
            response.Close(); //释放HTTP相应对象
        }
    }
}
