using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    public class M3DFWUtil
    {
        public static bool Init()
        {
            return m3dfw__init();
        }

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__init();
    }
}
