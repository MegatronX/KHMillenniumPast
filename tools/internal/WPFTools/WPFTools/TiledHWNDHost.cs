using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using System.Windows.Forms;

using Microsoft.Win32;
namespace WPFTools
{
    class TiledHWNDHost : HwndHost
    {
        [DllImport("User32.dll")]
        public static extern Int32 FindWindow(String lpClassName, String lpWindowName);
        [DllImport("User32.dll")]
        private static extern IntPtr GetWindowLong(IntPtr hWnd, int nIndex); 

        public IntPtr hwndHost;
        private IntPtr hookId = new IntPtr(3);
        private HookProc hookProc;
        private Process appProc;

        /*protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            appProc = new Process();
            appProc.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            appProc.StartInfo.FileName = @"F:\Kingdom Hearts MP\Tools\External\Tiled\Tiled.exe";
            appProc.Start();
            Thread.Sleep(300);
            hwndHost = appProc.MainWindowHandle;
            uint oldStyle = GetWindowLong(hwndHost, 
            //throw new NotImplementedException();
        }*/

    }
}
