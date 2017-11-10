using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Data.SqlClient;


namespace CtServer
{
    partial class CommuThread
    {

        //处理客户端的请求
        private void HandleRequest(JObject jObj)
        {
            string strFuc =  jObj["fuc"].ToString();
            //Console.WriteLine(strFuc);
            if (strFuc.Equals("\"register\""))
            {
                dealWithRequest_Register(jObj);
            }
            else if (strFuc.Equals("\"login\""))
            {
                dealWithRequest_Login(jObj);
            }
            else if (strFuc.Equals("\"setprefer\""))
            {
                dealWithRequest_SetPreference(jObj);
            }
            else if (strFuc.Equals("\"getnearest\""))
            {
                dealWithRequest_GetNearestActivities(jObj);
            }
            else if (strFuc.Equals("\"join\""))
            {
                dealWithRequest_JoinExistingActivities(jObj);
            }
            else if (strFuc.Equals("\"session\""))
            {
                dealWithRequest_BeginSession(jObj);
            }
            else if (strFuc.Equals("\"joined\""))
            {
                dealWithRequest_GetJoinedActivities(jObj);
            }
            else if (strFuc.Equals("\"startact\""))
            {
                dealWithRequest_BeginOneActivity(jObj);
            }
        }

        private void dealWithRequest_Register(JObject jObj)
        {
            //客户端发来用户名和密码，服务器查看用户名是否已存在
            //若已存在，告知注册失败
            //若不存在，添加到数据库，分配ID，并将ID返回给客户端
            string strUsrname = jObj["usrname"].ToString();
            string strPwd = jObj["pwd"].ToString();
        }

        private void dealWithRequest_Login(JObject jObj)
        {

        }

        private void dealWithRequest_SetPreference(JObject jObj)
        {
            //客户端发来偏好信息，服务器解析ID，为相应的客户设置偏好
            string strUsrid = jObj["usrid"].ToString();
            string strGrade = jObj["grade"].ToString();
        }

        private void dealWithRequest_GetNearestActivities(JObject jObj)
        {
            //客户端发来经纬度信息和偏好信息，服务器解析ID，
            //更新相应客户的地理坐标信息，然后根据经纬度信息和偏好信息
            //查找位于附近的活动，以JSON数组形式返回
            string strUsrid = jObj["usrid"].ToString();
            string strLongi = jObj["longi"].ToString();
            string strLat = jObj["lat"].ToString();
            string strPrefer = jObj["prefer"].ToString();
        }

        private void dealWithRequest_JoinExistingActivities(JObject jObj)
        {

        }

        private void dealWithRequest_BeginSession(JObject jObj)
        {

        }

        private void dealWithRequest_GetJoinedActivities(JObject jObj)
        {

        }

        private void dealWithRequest_BeginOneActivity(JObject jObj)
        {

        }        

        //回复请求，且发生错误时将释放套接字，后面不需要重复释放
        private bool ReplyRequest(String strToSend)
        {
            bool bResult = true;
            try
            {
                //发送数据
                byte[] byteToSend = Encoding.UTF8.GetBytes(strToSend.ToCharArray());
                m_clientSocket.Send(byteToSend, byteToSend.Length, 0);
            }
            catch (System.Exception ex)
            {
                if (m_clientSocket.Connected)
                {
                    m_clientSocket.Close();
                    m_clientSocket = null;
                }
                m_exception = ex;
                bResult = false;
            }
            return bResult;
        }

    }
}
