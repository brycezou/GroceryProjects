using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MainWindow_njust
{
    public partial class SelfMessageBox : Form
    {
        public ClientSocket m_clientSocket = null; //通信套接字

        //构造函数
        public SelfMessageBox(ClientSocket clntSocket)
        {
            InitializeComponent(); //初始化组件, 系统自动生成
            m_clientSocket = clntSocket;
        }

        //确定按钮事件
        private void button_OK_Click(object sender, EventArgs e)
        {
            this.Close(); //关闭对话框
        }

        //设置按钮事件
        private void button_set_Click(object sender, EventArgs e)
        {
            this.Hide(); //隐藏对话框
            //创建并显示环境设置对话框
            EnviromentSelectionForm esf = new EnviromentSelectionForm(m_clientSocket);
            esf.ShowDialog(this.ParentForm);
            this.Close(); //关闭对话框
        }
    }
}
