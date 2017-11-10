using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;


namespace CtServer
{
    class GlobalVariable
    {
        public static int SERVER_PORT = 3122;
        public static int RECV_BUFFER_SIZE = 4096;
        public static Dictionary<int, Socket> gMap_Id2Sock = new Dictionary<int, Socket>();
        public static Dictionary<Socket, int> gMap_Sock2Id = new Dictionary<Socket, int>();

    }
}
