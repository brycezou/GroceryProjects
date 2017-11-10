using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;


namespace CtServer
{
    class AcceptThread
    {
        private Socket m_serverSocket = null;

        public AcceptThread(Socket sock)
        {
            this.m_serverSocket = sock;
        }

        public void AcceptThreadRun()
        {
            while (true)
            {
                Socket clientSocket = null;
                try
                {
                    clientSocket = m_serverSocket.Accept();
                    CommuThread comThread = new CommuThread(clientSocket);
                    ThreadStart threadStart = new ThreadStart(comThread.HandleConnection);
                    Thread thread = new Thread(threadStart);
                    thread.Start();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace.ToString());
                    if (clientSocket.Connected)
                    {
                        clientSocket.Close();
                        clientSocket = null;
                    }
                }
            }
        }

    }
}
