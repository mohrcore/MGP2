using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    public abstract class GfxObject
    {
        public Resource model
        {
            get { return new Resource(m3dfw__GfxObject_Get_model(_instance)); }
            set { m3dfw__GfxObject_Set_model(_instance, value.get_CPP_instance()); }
        }

        public Vec3_CS position
        {
            get { return new Vec3f_Ref(m3dfw__GfxObject_Get_position(_instance)); }
            set { m3dfw__GfxObject_Set_position(_instance, new Vec3f_GC(value.x, value.y, value.z).get_CPP_instance()); }
        }

        public Vec3_CS rotation
        {
            get { return new Vec3f_Ref(m3dfw__GfxObject_Get_rotation(_instance)); }
            set { m3dfw__GfxObject_Set_rotation(_instance, new Vec3f_GC(value.x, value.y, value.z).get_CPP_instance()); }
        }

        public Vec3_CS scale
        {
            get { return new Vec3f_Ref(m3dfw__GfxObject_Get_scale(_instance)); }
            set { m3dfw__GfxObject_Set_scale(_instance, new Vec3f_GC(value.x, value.y, value.z).get_CPP_instance()); }
        }

        public IntPtr get_CPP_instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__GfxObject(IntPtr model_r);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__GfxObject(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxObject_Get_model(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxObject_Get_position(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxObject_Get_rotation(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxObject_Get_scale(IntPtr o_ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GfxObject_Set_model(IntPtr o_ptr, IntPtr value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxObject_Set_position(IntPtr o_ptr, IntPtr value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxObject_Set_rotation(IntPtr o_ptr, IntPtr value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GfxObject_Set_scale(IntPtr o_ptr, IntPtr value);
    }

    public class GfxObject_GC
        : GfxObject
    {
        public GfxObject_GC(Resource model_r)
        {
            _instance = m3dfw__new__GfxObject(model_r.get_CPP_instance());
        }

        ~GfxObject_GC()
        {
            m3dfw__delete__GfxObject(_instance);
        }
    }

    public class GfxObject_Ref
        : GfxObject
    {
        public GfxObject_Ref(IntPtr instance_ptr)
        {
            _instance = instance_ptr;
        }
    }
}
