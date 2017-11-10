using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace MainWindow_njust
{
    public class ClientSocket
    {
        public string m_strIP = null;
        public int m_intPort = 1400;
        public Socket m_clientSocket = null;
        const int RECV_BUFFER_SIZE = 4096;

        public ClientSocket(string adress, int port)
        {
            m_strIP = adress;
            m_intPort = port;
        }

        public bool ConnectServer()
        {
            bool bConnected = false;
            try
            {
                IPAddress hostAddress = IPAddress.Parse(m_strIP);
                IPEndPoint epHost = new IPEndPoint(hostAddress, m_intPort);
                m_clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                m_clientSocket.Connect(epHost);
                bConnected = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace.ToString());
                m_clientSocket = null;
                bConnected = false;
            }
            return bConnected;
        }

        public void ClientSend(string strToSend)
        {
            byte[] byteToSend = Encoding.UTF8.GetBytes(strToSend.ToCharArray());
            m_clientSocket.Send(byteToSend, byteToSend.Length, 0);
        }

        public string ClientRecv()
        {
            byte[] recvBytes = new byte[RECV_BUFFER_SIZE];
            int intRecvedByte = m_clientSocket.Receive(recvBytes, recvBytes.Length, 0);
            string strRecved = Encoding.UTF8.GetString(recvBytes, 0, intRecvedByte);
            return strRecved;
        }

        public bool GetSocketState()
        {
            return m_clientSocket.Connected;
        }

        public void CloseSocket()
        {
            m_clientSocket.Shutdown(SocketShutdown.Both);
            m_clientSocket.Close();
            m_clientSocket = null;
        }

    }
}
