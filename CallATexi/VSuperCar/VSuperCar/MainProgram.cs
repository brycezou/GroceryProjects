using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace VSuperCar
{
    class MainProgram
    {
        static void Main(string[] args)
        {
            String strHostName = Dns.GetHostName();
            IPAddress ipServerIP = Dns.Resolve(strHostName).AddressList[0];
            String strPort = "51115";
            IPEndPoint serverHost = new IPEndPoint(ipServerIP, Int32.Parse(strPort));
            Console.WriteLine("服务器信息:   {0} : {1}", serverHost.Address.ToString(), strPort);
            try
            {
                TcpListener myListener = new TcpListener(ipServerIP, Int32.Parse(strPort));
                myListener.Start();
                NewTcpListen ntl = new NewTcpListen(myListener);
                ThreadStart serverThreadStart = new ThreadStart(ntl.myServerThreadProc);
                Thread serverThread = new Thread(serverThreadStart);
                serverThread.Start();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace.ToString());
            }
            finally
            {

            }
            Console.ReadKey();
        }
    }
}
