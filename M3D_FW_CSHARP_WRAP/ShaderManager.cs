using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace M3D_FW_CSHARP_WRAP
{
    using GLSL_UniHandle = Int32;
    using GLSLProgramCompatibility = Int32;
    using GLSLProgramErrorEnum_CPP = Int32;

    public enum GLSLProgramErrorEnum
    {
        None,
        ErrorOpeningFile_Vertex,
        ErrorOpeningFile_Fragment,
        ShaderCompilationError_Vertex,
        ShaderCompilationError_Fragment,
        ProgramLinkingError
    }

    public abstract class GLSLProgramError
    {
        public GLSLProgramErrorEnum type
        {
            get { return (GLSLProgramErrorEnum)Enum.ToObject(typeof(GLSLProgramErrorEnum), m3dfw__GLSLProgramError_type(_instance)); }
        }

        public string details
        {
            get { return m3dfw__GLSLProgramError_details(_instance); }
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__GLSLProgramError();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__GLSLProgramError__arg_GLSLProgramErrorEnum_CStr(GLSLProgramErrorEnum_CPP t, [MarshalAs(UnmanagedType.LPStr)] string d);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__GLSLProgramError(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__new__GLSLProgramError(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern GLSLProgramErrorEnum_CPP m3dfw__GLSLProgramError_type(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        protected static extern string m3dfw__GLSLProgramError_details(IntPtr ptr);
    }

    public class GLSLProgramError_GC
        : GLSLProgramError
    {
        public GLSLProgramError_GC()
        {
            _instance = m3dfw__new__GLSLProgramError();
        }

        public GLSLProgramError_GC(GLSLProgramErrorEnum t, string d)
        {
            _instance = m3dfw__new__GLSLProgramError__arg_GLSLProgramErrorEnum_CStr((Int32)t, d);
        }

        ~GLSLProgramError_GC()
        {
            m3dfw__delete__GLSLProgramError(_instance);
        }
    }

    public class GLSLProgramError_Ref
        : GLSLProgramError
    {
        public GLSLProgramError_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }

    public abstract class GLSLProgram
    {
        public bool compileFromSrc(string v_src, string f_src)
        {
            return m3dfw__GLSLProgram_complileFromSrc(_instance, v_src, f_src);
        }

        public void clear()
        {
            m3dfw__GLSLProgram_clear(_instance);
        }

        public void bind()
        {
            m3dfw__GLSLProgram_bind(_instance);
        }

        GLSL_UniHandle getUniformHandle(string name)
        {
            return m3dfw__GLSLProgram_getUniformHandle(_instance, name);
        }

        public void setUniformFloat(GLSL_UniHandle loc, float val)
        {
            m3dfw__GLSLProgram_setUniformFloat(_instance, loc, val);
        }

        public void setUniformVec2(GLSL_UniHandle loc, Vec2_CS value)
        {
            m3dfw__GLSLProgram_setUniformVec2(_instance, loc, value.x, value.y);
        }

        public void setUniformVec3(GLSL_UniHandle loc, Vec3_CS value)
        {
            m3dfw__GLSLProgram_setUniformVec3(_instance, loc, value.x, value.y, value.z);
        }

        public void setUniformVec4(GLSL_UniHandle loc, Vec4_CS value)
        {
            m3dfw__GLSLProgram_setUniformVec4(_instance, loc, value.x, value.y, value.z, value.w);
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__GLSLProgram();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__GLSLProgram(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__GLSLProgram_complileFromSrc(IntPtr ptr, [MarshalAs(UnmanagedType.LPStr)] string v_src, [MarshalAs(UnmanagedType.LPStr)] string f_src);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_clear(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_bind(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern GLSL_UniHandle m3dfw__GLSLProgram_getUniformHandle(IntPtr ptr, [MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformFloat(IntPtr ptr, GLSL_UniHandle loc, float val);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformVec2(IntPtr ptr, GLSL_UniHandle loc, float x, float y);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformVec3(IntPtr ptr, GLSL_UniHandle loc, float x, float y, float z);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformVec4(IntPtr ptr, GLSL_UniHandle loc, float x, float y, float z, float w);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformInt(IntPtr ptr, GLSL_UniHandle loc, int val);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformMat2(IntPtr ptr, GLSL_UniHandle loc, IntPtr data);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformMat3(IntPtr ptr, GLSL_UniHandle loc, IntPtr data);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformMat4(IntPtr ptr, GLSL_UniHandle loc, IntPtr data);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__GLSLProgram_setUniformSampler2D(IntPtr ptr, GLSL_UniHandle loc, uint value);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern ulong m3dfw__GLSLProgram_getShaderCompatibilityKey(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern GLSLProgramCompatibility m3dfw__GLSLProgram_compare(IntPtr ptr, IntPtr other);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GLSLProgram_getError(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__GLSLProgram_getInfo(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__GLSLProgram_good(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected static extern bool m3dfw__GLSLProgram_compiled(IntPtr ptr);
    }

    public class GLSLProgram_GC
        : GLSLProgram
    {
        public GLSLProgram_GC()
        {
            _instance = m3dfw__new__GLSLProgram();
        }

        ~GLSLProgram_GC()
        {
            m3dfw__delete__GLSLProgram(_instance);
        }
    }

    public class GLSLProgram_Ref
        : GLSLProgram
    {
        public GLSLProgram_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }

    public abstract class ShaderManager
    {
        public void clear()
        {
            m3dfw__ShaderManager_clear(_instance);
        }

        public void unbindProgram()
        {
            m3dfw__ShaderManager_unbindProgram(_instance);
        }

        public uint loadProgram(string v_src, string f_src, string name)
        {
            return m3dfw__ShaderManager_loadProgram(_instance, v_src, f_src, name);
        }

        public void deleteProgram(uint id)
        {
            m3dfw__ShaderManager_deleteProgram(_instance, id);
        }

        public GLSLProgram_Ref getProgram(uint id)
        {
            return new GLSLProgram_Ref(m3dfw__ShaderManager_getProgram(_instance, id));
        }

        public uint getID(string name)
        {
            return m3dfw__ShaderManager_getID(_instance, name);
        }

        public bool isShaderAvaible(string name)
        {
            return m3dfw__ShaderManager_isShaderAvaible(_instance, name);
        }

        public IntPtr get_CPP_instance()
        {
            return _instance;
        }

        protected IntPtr _instance;

        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__new__ShaderManager();
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__delete__ShaderManager(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__ShaderManager_clear(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__ShaderManager_unbindProgram(IntPtr ptr);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern uint m3dfw__ShaderManager_loadProgram(IntPtr ptr, [MarshalAs(UnmanagedType.LPStr)] string v_src, [MarshalAs(UnmanagedType.LPStr)] string f_src, [MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void m3dfw__ShaderManager_deleteProgram(IntPtr ptr, uint id);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern IntPtr m3dfw__ShaderManager_getProgram(IntPtr ptr, uint id);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern uint m3dfw__ShaderManager_getID(IntPtr ptr, [MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("m3dfw_unwrap.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern bool m3dfw__ShaderManager_isShaderAvaible(IntPtr ptr, [MarshalAs(UnmanagedType.LPStr)] string name);
    }

    public class ShaderManager_GC
        : ShaderManager
    {
        public ShaderManager_GC()
        {
            _instance = m3dfw__new__ShaderManager();
        }

        ~ShaderManager_GC()
        {
            m3dfw__delete__ShaderManager(_instance);
        }
    }

    public class ShaderManager_Ref
        : ShaderManager
    {
        public ShaderManager_Ref(IntPtr instance_pointer)
        {
            _instance = instance_pointer;
        }
    }
}
