using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Data.SqlClient;

namespace VSuperCar
{
    class NewTcpRun
    {
        const int DISTANCE = 50000;
        const int RECV_BUFFER_SIZE = 2048;
        private string strConn = "Data Source=ZOUCHENG\\SQLEXPRESS;Initial Catalog=myDbTest;Integrated Security=True;Pooling=False";
        private Socket clientSocket;
        //private string strConn = "Data Source=.\\SQLEXPRESS;AttachDbFilename=\"C:\\Program Files\\Microsoft SQL Server\\MSSQL10.SQLEXPRESS\\MSSQL\\DATA\\myDbTest.mdf\";Integrated Security=True;Connect Timeout=30;User Instance=True";

        public NewTcpRun(Socket clntSocket)
        {
            this.clientSocket = clntSocket;
        }

        public void ProcessCustomerAndDriverRequest()
        {
            byte[] recvBytes;
            int intRecvedByte = 0;
            String strRecved;

            IPEndPoint clientInfo = (IPEndPoint)clientSocket.RemoteEndPoint;
            Console.WriteLine("\n\n终端: {0} : {1} 已连接!", clientInfo.Address.ToString(), clientInfo.Port.ToString());

            try
            {
                recvBytes = new byte[RECV_BUFFER_SIZE];
                intRecvedByte = clientSocket.Receive(recvBytes);    //receive from customers or car drivers
                strRecved = Encoding.UTF8.GetString(recvBytes, 0, intRecvedByte);
                Console.WriteLine("服务器接收到 {0} 字节:\n{1}", intRecvedByte, strRecved);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.StackTrace.ToString());
                Console.WriteLine("接收数据时发生错误!");
                if (clientSocket.Connected)
                {
                    clientSocket.Close();
                }
                return;
            }

            JObject jObj=null;
            try
            {
                jObj = JObject.Parse(strRecved);
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.StackTrace.ToString());
                Console.WriteLine("Json解析错误!");
                return;
            }

            /******************************************received from customers********************************************************/
            if (String.Equals(jObj["From"].ToString(), "\"customer\""))
            {
                if (String.Equals(jObj["Function"].ToString(), "\"query\""))             //received from customer to query the near cars
                {
                    ToQueryNearCars_Customer(jObj);
                }
                else if (String.Equals(jObj["Function"].ToString(), "\"callcar\""))     //received from customer to call a car
                {
                    ToCallOneCar_Customer(jObj);
                }
                else if (String.Equals(jObj["Function"].ToString(), "\"update_both\""))     //received from customer to update his location for the called car
                {
                    ToUpdateBothLocation_Customer(jObj);
                }
                else if (String.Equals(jObj["Function"].ToString(), "\"force_exit\""))     //received from customer to force exit and stop communicating with the driver
                {
                    ToForceExit_Customer(jObj);
                }
            }
            /******************************************received from drivers********************************************************/
            else if (String.Equals(jObj["From"].ToString(), "\"driver\""))
            {
                if (String.Equals(jObj["Function"].ToString(), "\"update\""))
                {
                    ToUpdateCarLocation_Driver(jObj);
                }
                else if (String.Equals(jObj["Function"].ToString(), "\"reply\""))
                {
                    ToReplyCallCarRequest_Driver(jObj);
                }
                else if (String.Equals(jObj["Function"].ToString(), "\"update_both\""))
                {
                    ToUpdateBothLocation_Driver(jObj);
                }
            }
        }

        //car_State:  -1停运，0空车，1即将载客，2下班，3被叫

        //服务器根据乘客的位置信息，查询其附近所有空车的位置，并将结果返回给乘客
        //若乘客附近没有空车，则返回字符串"NoNearCars"
        private void ToQueryNearCars_Customer(JObject jObj)
        {
            //乘客的位置
            double dbLatitude = Convert.ToDouble(jObj["Latitude"].ToString().Replace("\"", ""));
            double dbLongitude = Convert.ToDouble(jObj["Longitude"].ToString().Replace("\"", ""));  

            //根据乘客的位置查询符合要求的数据
            SqlConnection conn = new SqlConnection(strConn);
            conn.Open();
            string strQuery = String.Format("SELECT car_Num, car_X, car_Y  FROM mySuperCar WHERE (car_State =0) AND (car_X > {0}) AND (car_X < {1}) AND (car_Y > {2}) AND (car_Y < {3})", dbLatitude - DISTANCE, dbLatitude + DISTANCE, dbLongitude - DISTANCE, dbLongitude + DISTANCE);
            SqlCommand cmd = new SqlCommand(strQuery, conn);
            SqlDataReader sdr = cmd.ExecuteReader();

            if (sdr.Read())     //若乘客附近有空车
            {
                string strToSendJson = "{\"Info\":[";
                strToSendJson += "{\"Num\":\"" + sdr["car_Num"].ToString() + "\",\"Latitude\":\"" + sdr["car_X"].ToString() + "\",\"Longitude\":\"" + sdr["car_Y"].ToString() + "\"},";
                while (sdr.Read())
                {
                    strToSendJson += "{\"Num\":\"" + sdr["car_Num"].ToString() + "\",\"Latitude\":\"" + sdr["car_X"].ToString() + "\",\"Longitude\":\"" + sdr["car_Y"].ToString() + "\"},";
                }
                conn.Close();

                strToSendJson = (strToSendJson + "]}").Replace(",]", "]");
                byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray()); //send to customer the near cars' position
                clientSocket.Send(byteToSend, byteToSend.Length, 0);

                Console.WriteLine("服务器向乘客发送:\n" + strToSendJson);
            }
            else                    //若乘客附近没有空车              
            {
                conn.Close();

                string strToSendJson = "NoNearCars";
                byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray()); 
                clientSocket.Send(byteToSend, byteToSend.Length, 0);

                Console.WriteLine("服务器向乘客发送: " + strToSendJson);
            }

            clientSocket.Shutdown(SocketShutdown.Both);
            clientSocket.Close();
        }

        private void ToCallOneCar_Customer(JObject jObj)
        {
            double dbLatitude = Convert.ToDouble(jObj["Latitude"].ToString().Replace("\"", ""));                
            double dbLongitude = Convert.ToDouble(jObj["Longitude"].ToString().Replace("\"", ""));           //乘客的地理位置
            int intCarNum = Convert.ToInt32(jObj["CarNumber"].ToString().Replace("\"", ""));                   //乘客所叫的出租车的编号
            int personNum = Convert.ToInt32(jObj["PersonNumber"].ToString().Replace("\"", ""));             //乘客的人数
            string strDestin = jObj["Destination"].ToString().Replace("\"", "\'");                                           //乘客的目的地
            string strIMEI = jObj["IMEI"].ToString().Replace("\"", "\'");                                                     //乘客手机的IMEI号码，用于唯一标识乘客

            //查询被叫车的状态
            SqlConnection conn = new SqlConnection(strConn);
            conn.Open();
            string strQuery = String.Format("SELECT car_State  FROM mySuperCar WHERE (car_Num = {0})", intCarNum);   
            SqlCommand cmd = new SqlCommand(strQuery, conn);
            SqlDataReader sdr = cmd.ExecuteReader();
            if (sdr.Read())
            {
                int intCarStare=Convert.ToInt32(sdr["car_State"].ToString());
                if (intCarStare == 3)           //如果车已经被叫       car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                {
                    conn.Close();
                    Console.WriteLine("抱歉, 该车刚刚被人预定!");
                }
                else if (intCarStare == 0)    //如果车还未被叫       car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                {
                    conn.Close();

                    //更新叫车记录到表callCarInfo
                    conn.Open();
                    strQuery = String.Format("UPDATE callCarInfo SET  p_X = {0}, p_Y = {1}, p_Num = {2}, p_Destin = {3}, p_IMEI = {4} WHERE car_Num = {5}", dbLatitude, dbLongitude, personNum, strDestin, strIMEI, intCarNum);
                    cmd = new SqlCommand(strQuery, conn);
                    cmd.ExecuteNonQuery();
                    conn.Close();

                    //更新车的状态为“被叫”到表mySuperCar       car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                    conn.Open();            
                    strQuery = String.Format("UPDATE mySuperCar SET car_State = 3 WHERE car_Num = {0}", intCarNum);    
                    cmd = new SqlCommand(strQuery, conn);
                    cmd.ExecuteNonQuery();
                    conn.Close();
                    Console.WriteLine("预定车 {0} 成功!",  intCarNum);

                    //保存与当前乘客通信的Socket
                    string strImei = jObj["IMEI"].ToString().Replace("\"", "");
                    NewTcpListen.sockDictionary.Add(strImei, clientSocket);
                }
            }
        }

        private void ToUpdateCarLocation_Driver(JObject jObj)
        {
            double dbLatitude = Convert.ToDouble(jObj["Latitude"].ToString().Replace("\"", ""));
            double dbLongitude = Convert.ToDouble(jObj["Longitude"].ToString().Replace("\"", ""));
            int intCarNum = Convert.ToInt32(jObj["CarNumber"].ToString().Replace("\"", ""));
            string strToSendJson = "";

            //更新出租车的当前位置到表mySuperCar
            SqlConnection conn = new SqlConnection(strConn);
            conn.Open();
            string strQuery = String.Format("UPDATE mySuperCar SET car_X = {0}, car_Y = {1} WHERE car_Num = {2}", dbLatitude, dbLongitude, intCarNum);
            SqlCommand cmd = new SqlCommand(strQuery, conn);
            cmd.ExecuteNonQuery();
            conn.Close();
            Console.WriteLine("出租车 {0} 更新位置 : {1}, {2}", intCarNum, dbLatitude, dbLongitude);

            //查询该车的状态
            conn.Open();
            strQuery = String.Format("SELECT car_State  FROM mySuperCar WHERE (car_Num = {0})", intCarNum); 
            cmd = new SqlCommand(strQuery, conn);
            SqlDataReader sdr = cmd.ExecuteReader();
            if (sdr.Read())
            {
                int intCarStare = Convert.ToInt32(sdr["car_State"].ToString());
                if (intCarStare == 3)       //如果车被叫                       car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                {
                    conn.Close();

                    //查询叫车乘客的信息并返回给司机
                    conn.Open();
                    strQuery = String.Format("SELECT p_X, p_Y, p_Num, p_Destin  FROM callCarInfo WHERE (car_Num = {0})", intCarNum);
                    cmd = new SqlCommand(strQuery, conn);
                    sdr = cmd.ExecuteReader();
                    if (sdr.Read())
                    {
                        strToSendJson = "{\"IsCalled\":\"yes\",\"Latitude\":\"" + sdr["p_X"].ToString() + "\",\"Longitude\":\"" + sdr["p_Y"].ToString() + "\",\"PersonNumber\":\"" + sdr["p_Num"].ToString() + "\",\"Destination\":\"" + sdr["p_Destin"].ToString() + "\"}";
                        conn.Close();

                        byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray());
                        clientSocket.Send(byteToSend, byteToSend.Length, 0);    //send to drivers that someone is calling his car

                        Console.WriteLine("服务器向出租车 {0} 发送:\n{1}", intCarNum, strToSendJson);
                        Console.WriteLine("出租车 {0} 已被呼叫!", intCarNum);

                        //更新车的状态为“即将载客”到表mySuperCar        car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                        conn.Open();           
                        strQuery = String.Format("UPDATE mySuperCar SET car_State = 1 WHERE car_Num = {0}", intCarNum);   
                        cmd = new SqlCommand(strQuery, conn);
                        cmd.ExecuteNonQuery();
                        conn.Close();
                        Console.WriteLine("出租车 {0} 即将载客!", intCarNum);
                    }
                }
                else if (intCarStare == 0)      //如果车还未被叫          car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                {
                    conn.Close();

                    strToSendJson = "{\"IsCalled\":\"no\"}";
                    byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray());
                    clientSocket.Send(byteToSend, byteToSend.Length, 0); //send to drivers that none is calling his car

                    Console.WriteLine("服务器向出租车 {0} 发送: {1}", intCarNum, strToSendJson);
                    Console.WriteLine("出租车 {0} 还在空驶!", intCarNum);
                }
                else if (intCarStare == 1)
                {
                    conn.Close();

                    conn.Open();
                    strQuery = String.Format("UPDATE mySuperCar SET car_State = 0 WHERE car_Num = {0}", intCarNum);
                    cmd = new SqlCommand(strQuery, conn);
                    cmd.ExecuteNonQuery();
                    conn.Close();

                    strToSendJson = "{\"IsCalled\":\"no\"}";
                    byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray());
                    clientSocket.Send(byteToSend, byteToSend.Length, 0);

                    Console.WriteLine("服务器向出租车 {0} 发送: {1}", intCarNum, strToSendJson);
                    Console.WriteLine("出租车 {0} 还在空驶!", intCarNum);
                }

                clientSocket.Shutdown(SocketShutdown.Both);
                clientSocket.Close();
            }
        }

        private void ToReplyCallCarRequest_Driver(JObject jObj)
        {
            int intCarNum = Convert.ToInt32(jObj["CarNumber"].ToString().Replace("\"", ""));
            string strReply = jObj["Reply"].ToString().Replace("\"", "");
            string strIMEI = "";

            //根据被叫车的编号查询IMEI号码
            SqlConnection conn = new SqlConnection(strConn);
            conn.Open();
            string strQuery = String.Format("SELECT p_IMEI  FROM callCarInfo WHERE (car_Num = {0})", intCarNum);
            SqlCommand cmd = new SqlCommand(strQuery, conn);
            SqlDataReader sdr = cmd.ExecuteReader();

            if (sdr.Read())
            {
                strIMEI = sdr["p_IMEI"].ToString();
                conn.Close();
                string strToCustomer = "";

                if (NewTcpListen.sockDictionary.ContainsKey(strIMEI))
                {
                    Socket sockTemp = NewTcpListen.sockDictionary[strIMEI];
                    if (strReply.Equals("yes"))         //如果司机同意载客
                    {
                        strToCustomer = "yes";
                        byte[] byteToSend = Encoding.UTF8.GetBytes(strToCustomer.ToCharArray());    //send to customers the reply from the driver
                        sockTemp.Send(byteToSend, byteToSend.Length, 0);
                        sockTemp.Shutdown(SocketShutdown.Both);
                        sockTemp.Close();
                        NewTcpListen.sockDictionary.Remove(strIMEI);

                        //更新车的状态为“即将载客”到表mySuperCar        car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                        conn.Open();           
                        strQuery = String.Format("UPDATE mySuperCar SET car_State = 1 WHERE car_Num = {0}", intCarNum);    
                        cmd = new SqlCommand(strQuery, conn);
                        cmd.ExecuteNonQuery();
                        conn.Close();
                    }
                    else if (strReply.Equals("no"))     //如果司机拒绝载客
                    {
                        strToCustomer = "no";
                        byte[] byteToSend = Encoding.UTF8.GetBytes(strToCustomer.ToCharArray());     //send to customers the reply from the driver
                        sockTemp.Send(byteToSend, byteToSend.Length, 0);
                        sockTemp.Shutdown(SocketShutdown.Both);
                        sockTemp.Close();
                        NewTcpListen.sockDictionary.Remove(strIMEI);

                        //更新车的状态为“空车”到表mySuperCar        car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                        conn.Open();           
                        strQuery = String.Format("UPDATE mySuperCar SET car_State = 0 WHERE car_Num = {0}", intCarNum);    
                        cmd = new SqlCommand(strQuery, conn);
                        cmd.ExecuteNonQuery();
                        conn.Close();
                    }
                }
                else
                    Console.WriteLine("错误, 未找到乘客源!\n");
            }
        }

        private void ToUpdateBothLocation_Customer(JObject jObj)
        {
            double dbLatitude = Convert.ToDouble(jObj["Latitude"].ToString().Replace("\"", ""));
            double dbLongitude = Convert.ToDouble(jObj["Longitude"].ToString().Replace("\"", ""));           //乘客的地理位置
            int intCarNum = Convert.ToInt32(jObj["CarNumber"].ToString().Replace("\"", ""));                   //乘客所叫的出租车的编号
            string strIMEI = jObj["IMEI"].ToString().Replace("\"", "\'");                                                     //乘客手机的IMEI号码，用于唯一标识乘客

            //更新乘客的位置到表callCarInfo
            SqlConnection conn = new SqlConnection(strConn);
            conn.Open(); 
            string strQuery = String.Format("UPDATE callCarInfo SET  p_X = {0}, p_Y = {1}  WHERE  p_IMEI = {2} AND car_Num = {3}", dbLatitude, dbLongitude, strIMEI, intCarNum);
            SqlCommand cmd = new SqlCommand(strQuery, conn);
            cmd.ExecuteNonQuery();
            conn.Close();
            Console.WriteLine("乘客 {0} 更新位置!", strIMEI);

            //查询乘客所叫车的位置信息
            conn.Open();
            strQuery = String.Format("SELECT car_Num, car_X, car_Y  FROM mySuperCar WHERE car_Num = {0}", intCarNum);
            cmd = new SqlCommand(strQuery, conn);
            SqlDataReader sdr = cmd.ExecuteReader();
            if (sdr.Read())
            {
                string strToSendJson = "{\"Info\":[ {\"Num\":\"" + sdr["car_Num"].ToString() + "\",\"Latitude\":\"" + sdr["car_X"].ToString() + "\",\"Longitude\":\"" + sdr["car_Y"].ToString() + "\"} ]}";
                conn.Close();

                byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray());    //send to customer the called car's location
                clientSocket.Send(byteToSend, byteToSend.Length, 0);

                Console.WriteLine("服务器向乘客发送:\n" + strToSendJson);
            }

            clientSocket.Shutdown(SocketShutdown.Both);
            clientSocket.Close();
        } 

        private void ToUpdateBothLocation_Driver(JObject jObj)
        {
            double dbLatitude = Convert.ToDouble(jObj["Latitude"].ToString().Replace("\"", ""));
            double dbLongitude = Convert.ToDouble(jObj["Longitude"].ToString().Replace("\"", ""));
            int intCarNum = Convert.ToInt32(jObj["CarNumber"].ToString().Replace("\"", ""));
            string strToSendJson = "";

            //更新出租车的当前位置到表mySuperCar
            SqlConnection conn = new SqlConnection(strConn);
            conn.Open(); 
            string strQuery = String.Format("UPDATE mySuperCar SET car_X = {0}, car_Y = {1} WHERE car_Num = {2}", dbLatitude, dbLongitude, intCarNum);
            SqlCommand cmd = new SqlCommand(strQuery, conn);
            cmd.ExecuteNonQuery();
            conn.Close();
            Console.WriteLine("出租车 {0} 更新位置 : {1}, {2}", intCarNum, dbLatitude, dbLongitude);

            //查询被叫车的状态
            conn.Open();                  
            strQuery = String.Format("SELECT car_State  FROM mySuperCar WHERE (car_Num = {0})", intCarNum); 
            cmd = new SqlCommand(strQuery, conn);
            SqlDataReader sdr = cmd.ExecuteReader();
            if (sdr.Read())
            {
                int intCarStare = Convert.ToInt32(sdr["car_State"].ToString());
                if (intCarStare == 1)        //如果车即将载客            car_State:  -1停运，0空车，1即将载客，2下班，3被叫
                {
                    conn.Close();
                    
                    //查询叫车乘客的位置信息
                    conn.Open();
                    strQuery = String.Format("SELECT p_X, p_Y, IsForceExit FROM callCarInfo WHERE (car_Num = {0})", intCarNum);
                    cmd = new SqlCommand(strQuery, conn);
                    sdr = cmd.ExecuteReader();
                    if (sdr.Read())
                    {
                        if (Convert.ToInt32(sdr["IsForceExit"].ToString()) == 1)
                        {
                            conn.Close();

                            conn.Open();
                            strQuery = String.Format("UPDATE mySuperCar SET car_State = 0 WHERE car_Num = {0}", intCarNum);
                            cmd = new SqlCommand(strQuery, conn);
                            cmd.ExecuteNonQuery();
                            conn.Close();

                            strToSendJson = "{\"IsCalled\":\"force_exit\"}";
                            byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray());
                            clientSocket.Send(byteToSend, byteToSend.Length, 0);
                            Console.WriteLine("服务器向出租车 {0} 发送:\n{1}\n乘客强制退出!", intCarNum, strToSendJson);

                            conn.Open();
                            strQuery = String.Format("UPDATE callCarInfo SET  IsForceExit = 0  WHERE  car_Num = {0}", intCarNum);
                            cmd = new SqlCommand(strQuery, conn);
                            cmd.ExecuteNonQuery();
                            conn.Close();
                        }
                        else
                        {
                            strToSendJson = "{\"IsCalled\":\"yes\",\"Latitude\":\"" + sdr["p_X"].ToString() + "\",\"Longitude\":\"" + sdr["p_Y"].ToString() + "\"}";
                            conn.Close();

                            byte[] byteToSend = Encoding.UTF8.GetBytes(strToSendJson.ToCharArray());
                            clientSocket.Send(byteToSend, byteToSend.Length, 0);    //send to drivers that someone is calling his car

                            Console.WriteLine("服务器向出租车 {0} 发送:\n{1}", intCarNum, strToSendJson);
                            Console.WriteLine("出租车 {0} 正在赶往叫车乘客!", intCarNum);
                        }
                    }
                }

                clientSocket.Shutdown(SocketShutdown.Both);
                clientSocket.Close();
            }
        }

        private void ToForceExit_Customer(JObject jObj)
        {
            string strIMEI = jObj["IMEI"].ToString().Replace("\"", "\'");
            int intCarNum = Convert.ToInt32(jObj["CarNumber"].ToString().Replace("\"", ""));

            //更新乘客强制退出信息到表callCarInfo
            SqlConnection conn = new SqlConnection(strConn);
            conn.Open();
            string strQuery = String.Format("UPDATE callCarInfo SET  IsForceExit = 1  WHERE  p_IMEI = {0} AND car_Num = {1}",  strIMEI, intCarNum);
            SqlCommand cmd = new SqlCommand(strQuery, conn);
            cmd.ExecuteNonQuery();
            conn.Close();
            Console.WriteLine("乘客 {0} 强制退出!", strIMEI);
        }

    }
}
