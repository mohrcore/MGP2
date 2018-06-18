using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using M3D_FW_CSHARP_WRAP;
using System.Windows;

namespace M3DEngineUI
{
    public class EngineViewportHwndHost
        : HwndHost/*, IKeyboardInputSink*/
    {
        int hostHeight, hostWidth;
        Window parent;
        Int32 viewport_window;

        public EngineViewportHwndHost(double height, double width, Window parent_window)
        {
            hostHeight = (int)height;
            hostWidth = (int)width;
            parent = parent_window;
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            viewport_window = Win32Util.createEngineViewPortWindow(hostWidth, hostHeight, new WindowInteropHelper(parent).Handle.ToInt32());

            return new HandleRef(this, new IntPtr(viewport_window));
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            //DO NOTHING AND LEAK THE MEMORY BWAHBWABHWABHHHHHHAHAHAHHA!!!!
        }
    }
}
