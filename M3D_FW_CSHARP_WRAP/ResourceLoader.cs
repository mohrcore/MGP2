using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    using UserFct_ptr = IntPtr;

    public abstract class ResourceLoader
    {
        public Resource importGfxModel3d(string path, string name)
        {
            return new Resource(m3dfw__ResourceLoader_importGfxModel3d(_instance, path, name));
        }

        public Resource importGTexture2d(string path, string name)
        {
            return new Resource(m3dfw__ResourceLoader_importGTexture2d(_instance, path, name));
        }

        public Resource importGMaterial(string path, string name, ShaderManager sm)
        {
            return new Resource(m3dfw__ResourceLoader_importGMaterial(_instance, path, name, sm.get_CPP_instance()));
        }

        public IntPtr get_CPP_Instance()
        {
            return _instance;
        }

        public bool loadMaterialResourcesFromMDPFile(string path, ShaderManager sm)
        {
            return m3dfw__loadMaterialResourcesFromMDPFile(path, get_CPP_Instance(), sm.get_CPP_instance());
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__ResourceLoader(IntPtr res_mngr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__ResourceLoader(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__ResourceLoader_importGfxModel3d(IntPtr o_ptr, [MarshalAs(UnmanagedType.LPStr)] string path, [MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__ResourceLoader_importGTexture2d(IntPtr o_ptr, [MarshalAs(UnmanagedType.LPStr)] string path, [MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__ResourceLoader_importGMaterial(IntPtr o_ptr, [MarshalAs(UnmanagedType.LPStr)] string path, [MarshalAs(UnmanagedType.LPStr)] string name, IntPtr sm);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__loadMaterialResourcesFromMDPFile([MarshalAs(UnmanagedType.LPStr)] string path, IntPtr rloader, IntPtr sm);
    }

    public class ResourceLoader_GC
        : ResourceLoader
    {
        public ResourceLoader_GC(ResourceManager res_mngr)
        {
            _instance = m3dfw__new__ResourceLoader(res_mngr.get_CPP_Instance());
        }

        ~ResourceLoader_GC()
        {
            m3dfw__delete__ResourceLoader(_instance);
        }
    }

    public class ResourceLoader_Ref
        : ResourceLoader
    {
        public ResourceLoader_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }
}
