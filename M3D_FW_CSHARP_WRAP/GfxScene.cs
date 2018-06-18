using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    using UserFct_ptr = IntPtr;

    public abstract class GfxScene
    {
        public void load(IntPtr data_buffer)
        {
            m3dfw__GfxScene_load(_instance, data_buffer);
        }

        //public void clear()
        //{
        //    m3dfw__GfxScene_clear(_instance);
        //}

        public void GetObject(uint id)
        {
            new GfxScene_Ref(m3dfw__GfxScene_getObject(_instance, id));
        }

        //public uint getObjCount()
        //{
        //    return m3dfw__GfxScene_getObjCount();
        //}

        public IntPtr get_CPP_Instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__GfxScene();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__GfxScene(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxScene_getObject(IntPtr o_ptr, uint id);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__GfxScene_load(IntPtr o_ptr, IntPtr data_buffer);
    }

    public class GfxScene_GC
        : GfxScene
    {
        public GfxScene_GC()
        {
            _instance = m3dfw__new__GfxScene();
        }

        ~GfxScene_GC()
        {
            m3dfw__delete__GfxScene(_instance);
        }
    }

    public class GfxScene_Ref
        : GfxScene
    {
        public GfxScene_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }
}
