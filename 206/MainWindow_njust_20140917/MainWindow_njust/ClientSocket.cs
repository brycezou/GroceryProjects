using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace MainWindow_njust
{
    //网络通信类
    public class ClientSocket
    {
        public string m_strIP = null; //IP地址
        public int m_intPort = 1400; //端口号
        public Socket m_clientSocket = null; //本地套接字
        const int RECV_BUFFER_SIZE = 4096; //接收缓冲区大小

        //通信类的构造函数
        public ClientSocket(string adress, int port)
        {
            //初始化IP地址和端口号
            m_strIP = adress; 
            m_intPort = port;
        }

        //连接服务器
        public bool ConnectServer()
        {
            bool bConnected = false; //标志是否连接成功
            try
            {
                //创建套接字
                IPAddress hostAddress = IPAddress.Parse(m_strIP); 
                IPEndPoint epHost = new IPEndPoint(hostAddress, m_intPort);
                m_clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                m_clientSocket.Connect(epHost); //连接到服务器
                bConnected = true; //连接成功
            }
            catch (Exception ex) //如果发生错误
            {
                Console.WriteLine(ex.StackTrace.ToString());
                m_clientSocket = null;
                bConnected = false; //连接失败
            }
            return bConnected;
        }

        //发送数据的函数
        public void ClientSend(string strToSend)
        {
            //编码字符串为UTF8编码
            byte[] byteToSend = Encoding.UTF8.GetBytes(strToSend.ToCharArray());
            //发送数据
            m_clientSocket.Send(byteToSend, byteToSend.Length, 0); 
        }

        //接收数据的函数
        public string ClientRecv()
        {
            byte[] recvBytes = new byte[RECV_BUFFER_SIZE];
            //接收数据
            int intRecvedByte = m_clientSocket.Receive(recvBytes, recvBytes.Length, 0);
            //编码字符串为UTF8编码
            string strRecved = Encoding.UTF8.GetString(recvBytes, 0, intRecvedByte);
            return strRecved;
        }

        //得到网络连接状态
        public bool GetSocketState()
        {
            return m_clientSocket.Connected;
        }

        //关闭套接字
        public void CloseSocket()
        {
            //关闭通信套接字
            m_clientSocket.Shutdown(SocketShutdown.Both);
            //关闭套接字
            m_clientSocket.Close(); 
            m_clientSocket = null;
        }

    }
}
