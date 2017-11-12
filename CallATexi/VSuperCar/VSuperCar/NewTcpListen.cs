using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace VSuperCar
{
    class NewTcpListen
    {
        private TcpListener myListener;
        private Socket clientSocket;
        public static Dictionary<string, Socket> sockDictionary;

         static NewTcpListen()
        {
            sockDictionary=new Dictionary<string, Socket>();
        }

        public NewTcpListen(TcpListener listener)
        {
            this.myListener = listener;
        }

        public void myServerThreadProc()
        {
            while (true)
            {
                try
                {
                    clientSocket = myListener.AcceptSocket();

                    NewTcpRun ntr = new NewTcpRun(clientSocket);
                    ThreadStart serverThreadStart = new ThreadStart(ntr.ProcessCustomerAndDriverRequest);
                    Thread serverThread = new Thread(serverThreadStart);
                    serverThread.Start();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace.ToString());
                    if (clientSocket.Connected)
                    {
                        clientSocket.Close();
                    }
                }
            }
        }
    }
}
