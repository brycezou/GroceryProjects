using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;

namespace GpsDataReceiver
{
    public class ReceiveGpsData
    {
        private SerialPort m_SerialPort = null;
        public bool m_bSuccessful = false;
        private StringBuilder m_strTemp = null;
        private bool m_bStart = false;
        private const int LOCATION_STATE = 2;
        private const int LOCAT_LATITUDE = 3;
        private const int LOC_LONGITUDE = 5;

        public ReceiveGpsData(string strComPort)
        {
            try
            {
                m_SerialPort = new SerialPort(strComPort, 9600, Parity.None, 8, StopBits.One);
                m_SerialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);
                m_bSuccessful = true;
            }
            catch (System.Exception)
            {
                if (m_SerialPort.IsOpen)
                {
                    m_SerialPort.Close();
                    m_SerialPort = null;
                }
                m_bSuccessful = false;
            }
        }

        public void OpenComm()
        {
            if (m_bSuccessful)
            {
                m_strTemp = new StringBuilder();
                m_SerialPort.Open();
            }
        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string strRecvd = m_SerialPort.ReadLine();
            for (int i = 0; i < strRecvd.Length; i++)
            {
                if (!m_bStart && strRecvd[i] == '$')
                {
                    m_strTemp.Clear();
                    m_bStart = true;
                    m_strTemp.Append(strRecvd[i]);
                }
                else if (m_bStart && strRecvd[i] != '$')
                {
                    m_strTemp.Append(strRecvd[i]);
                }
                else if (m_bStart && strRecvd[i] == '$')
                {
                    string strResult = m_strTemp.ToString();
                    if (strResult.IndexOf("$GPRMC") == 0)
                    {
                        ParseLocationData(strResult);
                    }
                    m_strTemp.Clear();
                    m_strTemp.Append(strRecvd[i]);
                }
            }
        }

        private void ParseLocationData(string str)
        {
            string[] strArray = str.Split(new char[] {','});
            if (strArray[LOCATION_STATE].Equals("A"))
            {
                Console.WriteLine(strArray[LOCAT_LATITUDE]+"\n"+strArray[LOC_LONGITUDE]);
            }
            else
            {
                Console.WriteLine("定位无效");
            }
        }

    }
}
