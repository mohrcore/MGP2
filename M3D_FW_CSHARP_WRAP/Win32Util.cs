using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    public class Win32Util
    {
        public static Int32 prepareWinCtx(Int32 window)
        {
            return m3dfw_win32__prepareWinCtx(window);
        }

        public static Int32 createEngineViewPortWindow(int w, int h, Int32 parent)
        {
            return m3dfw_win32__createWindow(w, h, parent);
        }

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 m3dfw_win32__createWindow(int w, int h, Int32 parent);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 m3dfw_win32__prepareWinCtx(Int32 window);
    }
}
