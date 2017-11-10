using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading;

namespace GpsDataReceiver
{
    class Program
    {
        static void Main(string[] args)
        {
            string strComPort = Console.ReadLine();
            ReceiveGpsData rgd = new ReceiveGpsData("COM"+strComPort);
            if (rgd.m_bSuccessful)
            {
                Console.WriteLine("successful");
                rgd.OpenComm();
            }
            while (true)
            {
                Thread.Sleep(100);
            }
        }
    }
}
