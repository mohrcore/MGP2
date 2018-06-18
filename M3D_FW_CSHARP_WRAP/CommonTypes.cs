using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    public struct Vec2_CS
    {
        public float x, y;

        public float length
        {
            get { return (float)Math.Sqrt(x * x + y * y); }
        }

        public static Vec2_CS operator+(Vec2_CS v1, Vec2_CS v2)
        {
            return new Vec2_CS() { x = v1.x + v2.x, y = v1.x + v2.x };
        }

        public static Vec2_CS operator-(Vec2_CS v1, Vec2_CS v2)
        {
            return new Vec2_CS() { x = v1.x - v2.x, y = v1.x - v2.x };
        }

        public static float operator^(Vec2_CS v1, Vec2_CS v2)
        {
            return v1.x * v2.y - v1.y * v2.x;
        }

        public static float operator*(Vec2_CS v1, Vec2_CS v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        public static Vec2_CS operator*(Vec2_CS v, float scale)
        {
            return new Vec2_CS() { x = v.x * scale, y = v.y * scale };
        }

        public static Vec2_CS operator/(Vec2_CS v, float div)
        {
            return new Vec2_CS() { x = v.x / div, y = v.y / div };
        }
    }

    public struct Vec3_CS
    {
        public float x, y, z;

        public float length
        {
            get { return (float)Math.Sqrt(x * x + y * y + z * z); }
        }

        public static Vec3_CS operator+(Vec3_CS v1, Vec3_CS v2)
        {
            return new Vec3_CS() { x = v1.x + v2.x, y = v1.y + v2.y, z = v1.z + v2.z };
        }

        public static Vec3_CS operator-(Vec3_CS v1, Vec3_CS v2)
        {
            return new Vec3_CS() { x = v1.x - v2.x, y = v1.y - v2.y, z = v1.z - v2.z };
        }

        public static Vec3_CS operator^(Vec3_CS v1, Vec3_CS v2)
        {
            return new Vec3_CS() { x = v1.y * v2.z - v1.z * v2.y, y = v1.z * v2.x - v1.x * v2.z, z = v1.x * v2.y - v1.y * v2.x };
        }

        public static float operator*(Vec3_CS v1, Vec3_CS v2)
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }

        public static Vec3_CS operator*(Vec3_CS v, float scale)
        {
            return new Vec3_CS() { x = v.x * scale, y = v.y * scale, z = v.z * scale };
        }

        public static Vec3_CS operator/(Vec3_CS v, float div)
        {
            return new Vec3_CS() { x = v.x / div, y = v.y / div, z = v.z / div };
        }
    }

    public struct Vec4_CS
    {
        public float x, y, z, w;

        public float length
        {
            get { return (float)Math.Sqrt(x * x + y * y + z * z + w * w); }
        }

        public static Vec4_CS operator+(Vec4_CS v1, Vec4_CS v2)
        {
            return new Vec4_CS() { x = v1.x + v2.x, y = v1.y + v2.y, z = v1.z + v2.z, w = v1.w + v2.w };
        }

        public static Vec4_CS operator-(Vec4_CS v1, Vec4_CS v2)
        {
            return new Vec4_CS() { x = v1.x - v2.x, y = v1.y - v2.y, z = v1.z - v2.z, w = v1.w - v2.w };
        }

        public static float operator*(Vec4_CS v1, Vec4_CS v2)
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
        }

        public static Vec4_CS operator*(Vec4_CS v, float scale)
        {
            return new Vec4_CS() { x = v.x * scale, y = v.y * scale, z = v.z * scale, w = v.w * scale };
        }

        public static Vec4_CS operator/(Vec4_CS v, float div)
        {
            return new Vec4_CS() { x = v.x / div, y = v.y / div, z = v.z / div, w = v.w / div };
        }
    }

    public abstract class Vec2f
    {
        public float x
        {
            get { return m3dfw__Vec2f_Get_x(_instance); }
            set { m3dfw__Vec2f_Set_x(_instance, value); }
        }

        public float y
        {
            get { return m3dfw__Vec2f_Get_y(_instance); }
            set { m3dfw__Vec2f_Set_y(_instance, value); }
        }

        public float length
        {
            get { return m3dfw__Vec2f_length(_instance); }
        }

        public static implicit operator Vec2_CS(Vec2f v)
        {
            return new Vec2_CS() { x = v.x, y = v.y };
        }

        public IntPtr get_CPP_instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__Vec2f();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__Vec2f__arg_float_float(float v_x, float v_y);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__Vec2f(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec2f_Add(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec2f_Sub(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec2f_Scl(IntPtr ptr, float scale);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec2f_Div(IntPtr ptr, float div);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec2f_Dot(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec2f_length(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec2f_Get_x(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec2f_Get_y(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec2f_Set_x(IntPtr ptr, float value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec2f_Set_y(IntPtr ptr, float value);
    }

    public class Vec2f_GC
        : Vec2f
    {
        public Vec2f_GC()
        {
            _instance = m3dfw__new__Vec2f();
        }

        public Vec2f_GC(float v_x, float v_y)
        {
            _instance = m3dfw__new__Vec2f__arg_float_float(v_x, v_y);
        }

        ~Vec2f_GC()
        {
            m3dfw__delete__Vec2f(_instance);
        }
    }

    public class Vec2f_Ref
        : Vec2f
    {
        public Vec2f_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }

    public abstract class Vec3f
    {
        public float x
        {
            get { return m3dfw__Vec3f_Get_x(_instance); }
            set { m3dfw__Vec3f_Set_x(_instance, value); }
        }

        public float y
        {
            get { return m3dfw__Vec3f_Get_y(_instance); }
            set { m3dfw__Vec3f_Set_y(_instance, value); }
        }

        public float z
        {
            get { return m3dfw__Vec3f_Get_z(_instance); }
            set { m3dfw__Vec3f_Set_z(_instance, value); }
        }

        public float length
        {
            get { return m3dfw__Vec3f_length(_instance); }
        }

        public static implicit operator Vec3_CS(Vec3f v)
        {
            return new Vec3_CS() { x = v.x, y = v.y, z = v.z };
        }

        public IntPtr get_CPP_instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__Vec3f();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__Vec3f__arg_float_float_float(float v_x, float v_y, float v_z);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__Vec3f(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec3f_Add(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec3f_Sub(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec3f_Cross(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec3f_Dot(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec3f_Scl(IntPtr ptr, float scale);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void m3dfw__Vec3f_Div(IntPtr ptr, float div);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern float m3dfw__Vec3f_length(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern float m3dfw__Vec3f_Get_x(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern float m3dfw__Vec3f_Get_y(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern float m3dfw__Vec3f_Get_z(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void m3dfw__Vec3f_Set_x(IntPtr ptr, float value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void m3dfw__Vec3f_Set_y(IntPtr ptr, float value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void m3dfw__Vec3f_Set_z(IntPtr ptr, float value);
    }

    public class Vec3f_GC
        : Vec3f
    {
        public Vec3f_GC()
        {
            _instance = m3dfw__new__Vec3f();
        }

        public Vec3f_GC(float v_x, float v_y, float v_z)
        {
            _instance = m3dfw__new__Vec3f__arg_float_float_float(v_x, v_y, v_z);
        }

        ~Vec3f_GC()
        {
            m3dfw__delete__Vec3f(_instance);
        }
    }

    public class Vec3f_Ref
        : Vec3f
    {
        public Vec3f_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }

    public abstract class Vec4f
    {
        public float x
        {
            get { return m3dfw__Vec4f_Get_x(_instance); }
            set { m3dfw__Vec4f_Set_x(_instance, value); }
        }

        public float y
        {
            get { return m3dfw__Vec4f_Get_y(_instance); }
            set { m3dfw__Vec4f_Set_y(_instance, value); }
        }

        public float z
        {
            get { return m3dfw__Vec4f_Get_z(_instance); }
            set { m3dfw__Vec4f_Set_z(_instance, value); }
        }

        public float w
        {
            get { return m3dfw__Vec4f_Get_w(_instance); }
            set { m3dfw__Vec4f_Set_w(_instance, value); }
        }
        
        public float length
        {
            get { return m3dfw__Vec4f_length(_instance); }
        }

        public static implicit operator Vec4_CS(Vec4f v)
        {
            return new Vec4_CS() { x = v.x, y = v.y, z = v.z, w = v.w };
        }

        public IntPtr get_CPP_instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__Vec4f();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__Vec4f__arg_float_float_float_float(float v_x, float v_y, float v_z, float v_w);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__Vec4f(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Add(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Sub(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec4f_Dot(IntPtr ptr, IntPtr right);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Scl(IntPtr ptr, float scale);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Div(IntPtr ptr, float div);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec4f_length(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec4f_Get_x(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec4f_Get_y(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec4f_Get_z(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern float m3dfw__Vec4f_Get_w(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Set_x(IntPtr ptr, float value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Set_y(IntPtr ptr, float value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Set_z(IntPtr ptr, float value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__Vec4f_Set_w(IntPtr ptr, float value);
    }

    public class Vec4f_GC
        : Vec4f
    {
        public Vec4f_GC()
        {
            _instance = m3dfw__new__Vec4f();
        }

        public Vec4f_GC(float v_x, float v_y, float v_z, float v_w)
        {
            _instance = m3dfw__new__Vec4f__arg_float_float_float_float(v_x, v_y, v_z, v_w);
        }

        ~Vec4f_GC()
        {
            m3dfw__delete__Vec4f(_instance);
        }
    }

    public class Vec4f_Ref
        : Vec4f
    {
        public Vec4f_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }
}
