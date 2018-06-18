using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    using UserFct_ptr = IntPtr;

    public abstract class GameDLib
    {
        public bool loadLibrary(string path)
        {
            return m3dfw__GameDLib_loadLibrary(_instance, path);
        }

        public UserFct_ptr getFunctionByName(string name)
        {
            return m3dfw__GameDLib_getFunctionByName(_instance, name);
        }


        public IntPtr get_CPP_Instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__GameDLib();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__GameDLib(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GameDLib_getFunctionByName(IntPtr o_ptr, [MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__GameDLib_loadLibrary(IntPtr o_ptr, [MarshalAs(UnmanagedType.LPStr)] string path);
    }

    public class GameDLib_GC
        : GameDLib
    {
        public GameDLib_GC()
        {
            _instance = m3dfw__new__GameDLib();
        }

        ~GameDLib_GC()
        {
            m3dfw__delete__GameDLib(_instance);
        }
    }

    public class GameDLib_Ref
        : GameDLib
    {
        public GameDLib_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }
}
