using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    using UserFct_ptr = IntPtr;

    public abstract class ResourceManager
    {
        public bool isAnyKindOfResourceAvaible(string name)
        {
            return m3dfw__ResourceManager_isAnyKindOfResourceAvailable(_instance, name);
        }

        public void clearAllResources()
        {
            m3dfw__ResourceManager_clearAllResources(_instance);
        }
        
        public IntPtr get_CPP_Instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__ResourceManager();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__ResourceManager(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__ResourceManager_isAnyKindOfResourceAvailable(IntPtr o_ptr, [MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__ResourceManager_clearAllResources(IntPtr o_ptr);
        
    }

    public class ResourceManager_GC
        : ResourceManager
    {
        public ResourceManager_GC()
        {
            _instance = m3dfw__new__ResourceManager();
        }

        ~ResourceManager_GC()
        {
            m3dfw__delete__ResourceManager(_instance);
        }
    }

    public class ResourceManager_Ref
        : ResourceManager
    {
        public ResourceManager_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }
}
