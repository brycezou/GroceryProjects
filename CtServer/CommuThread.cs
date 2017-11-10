using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;


namespace CtServer
{
    partial class CommuThread
    {
        private int m_uid;
        private Socket m_clientSocket = null;
        private Exception m_exception = null;

        public CommuThread(Socket clientSocket)
        {
            m_uid = -1;
            m_clientSocket = clientSocket;
        }

        public void HandleConnection()
        {
            //输出显示客户端信息
            IPEndPoint clientInfo = (IPEndPoint)m_clientSocket.RemoteEndPoint;
            Console.WriteLine("Client : {0}:{1} Connected!", clientInfo.Address.ToString(), clientInfo.Port.ToString());

            while (true)
            {
                string strRecved;
                if ((strRecved = RecvRequest()).Equals("null"))
                {
                    Console.WriteLine("接收数据时发生错误!\n" + m_exception.StackTrace.ToString());
                    break;
                }
                else if (strRecved.Equals(""))
                {
                    Console.WriteLine("client logout!");
                    break;
                }
                else
                {
                    Console.WriteLine(strRecved);
                    if (!ParseJsonData(strRecved))
                    {
                        Console.WriteLine("Json解析错误!\n" + m_exception.StackTrace.ToString());
                        break;
                    }
                }
            }

            if (m_clientSocket!=null)
            {
                m_clientSocket.Close(); 
                m_clientSocket = null;
                m_exception = null;
            }
        }

        //接收请求数据，且发生错误时将释放套接字，后面不需要重复释放
        private string RecvRequest()
        {
            byte[] recvBytes;
            int intRecvedByte = 0;
            string strRecved;
            try
            {
                //接收数据
                recvBytes = new byte[GlobalVariable.RECV_BUFFER_SIZE];
                intRecvedByte = m_clientSocket.Receive(recvBytes, recvBytes.Length, 0);
                strRecved = Encoding.UTF8.GetString(recvBytes, 0, intRecvedByte);
            }
            catch (Exception ex)
            {
                if (m_clientSocket.Connected)
                {
                    m_clientSocket.Close();
                    m_clientSocket = null;
                }
                m_exception = ex;
                strRecved = "null";
            }
            return strRecved;
        }

        //解析Json数据，解析成功后处理请求，否则不处理
        private bool ParseJsonData(string strRequest)
        {
            bool bResult = true;
            JObject jObj = null;
            try
            {
                jObj = JObject.Parse(strRequest);
            }
            catch (Exception ex)
            {
                m_exception = ex;
                bResult = false;
            }

            if (bResult)
                HandleRequest(jObj);

            return bResult;
        }

    }
}
