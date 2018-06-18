using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    public class Resource
    {
        public Resource(IntPtr ptr)
        {
            _instance = m3dfw__copy__RsourceBase(ptr);
        }

        ~Resource()
        {
            m3dfw__delete__ResourceBase(_instance);
        }

        public IntPtr getResourcePtr()
        {
            return m3dfw__ResourceBase_getResourcePtr(_instance);
        }

        public IntPtr get_CPP_instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__ResourceBase();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__ResourceBase(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__ResourceBase_getResourcePtr(IntPtr o_ptr);

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__copy__RsourceBase(IntPtr ptr);
    }
}
