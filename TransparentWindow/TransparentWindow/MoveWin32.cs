using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;


namespace TransparentWindow
{
    class MoveWin32
    {
        //无边框窗体移动
        private const int SC_MOVE = 0xF010;
        private const int HTCAPTION = 0x0002;
        private const int WM_SYSCOMMAND = 0x0112;

        [DllImport("user32.dll")]
        private static extern bool ReleaseCapture();
        [DllImport("user32.dll")]
        private static extern bool SendMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);

        public static void Move(IntPtr hwnd)
        {
            ReleaseCapture();
            SendMessage(hwnd, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }

    }
}
