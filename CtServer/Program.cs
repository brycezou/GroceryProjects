using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace CtServer
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                IPEndPoint serverHost = new IPEndPoint(IPAddress.Any, GlobalVariable.SERVER_PORT);
                Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                serverSocket.Bind(serverHost);
                serverSocket.Listen(10);
                Console.WriteLine("服务器信息:   {0} : {1}", serverHost.Address.ToString(), GlobalVariable.SERVER_PORT);

                AcceptThread akcptThread = new AcceptThread(serverSocket);
                ThreadStart threadStart = new ThreadStart(akcptThread.AcceptThreadRun);
                Thread thread = new Thread(threadStart);
                thread.Start();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace.ToString());
            }
            Console.ReadKey();
        }
    }
}
