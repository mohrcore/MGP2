//------------------------------------------------------------------------------
// <copyright file="FGetter.cs" company="Company">
//     Copyright (c) Company.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.ComponentModel.Design;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.OLE.Interop;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.Win32;

using System.Collections.Generic;
using Microsoft.VisualStudio.VCCodeModel;

namespace MExt
{
    /// <summary>
    /// This is the class that implements the package exposed by this assembly.
    /// </summary>
    /// <remarks>
    /// <para>
    /// The minimum requirement for a class to be considered a valid package for Visual Studio
    /// is to implement the IVsPackage interface and register itself with the shell.
    /// This package uses the helper classes defined inside the Managed Package Framework (MPF)
    /// to do it: it derives from the Package class that provides the implementation of the
    /// IVsPackage interface and uses the registration attributes defined in the framework to
    /// register itself and its components with the shell. These attributes tell the pkgdef creation
    /// utility what data to put into .pkgdef file.
    /// </para>
    /// <para>
    /// To get loaded into VS, the package must be referred by &lt;Asset Type="Microsoft.VisualStudio.VsPackage" ...&gt; in .vsixmanifest file.
    /// </para>
    /// </remarks>
    /// 
    [PackageRegistration(UseManagedResourcesOnly = true)]
    [InstalledProductRegistration("#110", "#112", "1.0", IconResourceID = 400)] // Info on this package for Help/About
    [Guid(FGetter.PackageGuidString)]
    [SuppressMessage("StyleCop.CSharp.DocumentationRules", "SA1650:ElementDocumentationMustBeSpelledCorrectly", Justification = "pkgdef, VS and vsixmanifest are valid VS terms")]
    [ProvideMenuResource("Menus.ctmenu", 1)]
    [ProvideToolWindow(typeof(VListWindow))]
    public sealed class FGetter : Package
    {
        /// <summary>
        /// FGetter GUID string.
        /// </summary>
        public const string PackageGuidString = "3a94d3e8-1144-444f-bcd0-fedc689d710b";

        /// <summary>
        /// Initializes a new instance of the <see cref="FGetter"/> class.
        /// </summary>
        public FGetter()
        {
            // Inside this method you can place any initialization code that does not require
            // any Visual Studio service because at this point the package object is created but
            // not sited yet inside Visual Studio environment. The place to do all the other
            // initialization is the Initialize method.
        }

        #region Package Members

        /// <summary>
        /// Initialization of the package; this method is called right after the package is sited, so this is the place
        /// where you can put all the initialization code that rely on services provided by VisualStudio.
        /// </summary>

        protected override void Initialize()
        {
            base.Initialize();
            FGetCommand.Initialize(this);
            VListWindowCommand.Initialize(this);

            IVsShell shell_service = GetService(typeof(SVsShell)) as IVsShell;

            bool test = true;

            dte2 = (EnvDTE80.DTE2)Microsoft.VisualStudio.Shell.Package.GetGlobalService(typeof(Microsoft.VisualStu‌​dio.Shell.Interop.SD‌​TE));

            _m3dfw_namespace = null;
            _getFctPtrList_function = null;

            test = false; 
        }

        public struct CppVar
        {
            public CppVar(string type, string name)
            {
                Type = type;
                Name = name;
            }

            public string Name;
            public string Type;
        }

        public class CppProj
        {
            public CppProj() { Name = null; Variables = new List<CppVar>(); Variables.Capacity = 1000000; }
            public string Name;
            public List<CppVar> Variables;
        }

        public enum M3DCppFctKind
        {
            Free,
            Member
        }

        public interface M3DCppFreeFunction
        {
            M3DCppFctKind Kind { get; }
            string FullName { get; }
            string DeclarationFile { get; }
        }

        public interface M3DCppMemberFunction
        {
            M3DCppFctKind Kind { get; }
            string FullName { get; }
            string DeclarationFile { get; }
            string ParentFullName { get; }
        }

        public class M3DCppFct
            : M3DCppFreeFunction, M3DCppMemberFunction
        {
            public M3DCppFct(M3DCppFctKind kind, string fullname, string decfile, string parent)
            {
                _kind = kind;
                _fullname = fullname;
                _decfile = decfile;
                _parent = parent;
            }

            public M3DCppFct(M3DCppFctKind kind, string fullname, string decfile)
            {
                _kind = kind;
                _fullname = fullname;
                _decfile = decfile;
                _parent = null;
            }


            public M3DCppFctKind Kind
            {
                get { return _kind; }
                private set { _kind = value; }
            }

            public string FullName
            {
                get { return _fullname; }
                set { _fullname = value; }
            }

            public string DeclarationFile
            {
                get { return _decfile; }
                set { _decfile = value; }
            }

            public string ParentFullName
            {
                get { return _parent; }
                set { _parent = value; }
            }

            private M3DCppFctKind _kind;
            private string _fullname;
            private string _decfile;
            private string _parent;
        }

        static public EnvDTE80.DTE2 dte2;
        static EnvDTE.CodeNamespace _m3dfw_namespace;
        static EnvDTE.CodeFunction _getFctPtrList_function;
        static EnvDTE.CodeFunction _getMemberFctPtrList_function;

        public static EnvDTE.CodeNamespace m3dfw_namespace
        {
            get { return _m3dfw_namespace; }
        }

        public static EnvDTE.CodeFunction getFctPtrList_function
        {
            get { return _getFctPtrList_function; }
        }

        public static EnvDTE.CodeFunction getMemberFctPtrList_function
        {
            get { return _getMemberFctPtrList_function; }
        }

        static public List<CppProj> getSolutionStruct()
        {
            List<CppProj> proj_list = new List<CppProj>();

            VCCodeModel codemodel = null;

            Console.WriteLine(dte2.Solution.FullName);

            int u = dte2.Solution.Count;

            for (int i1 = 1; i1 <= dte2.Solution.Count; i1++)
            {
                CppProj proj = new CppProj();
                proj.Name = dte2.Solution.Item(i1).Name;

                proj_list.Add(proj);

                for(int i2 = 1; i2 <= dte2.Solution.Item(i1).CodeModel.CodeElements.Count; i2++)
                {
                    EnvDTE.CodeElement code_element = dte2.Solution.Item(i1).CodeModel.CodeElements.Item(i2);
                    CppVar var;
                    if(code_element.Kind == EnvDTE.vsCMElement.vsCMElementFunction)
                        var = new CppVar(((EnvDTE.CodeFunction)dte2.Solution.Item(i1).CodeModel.CodeElements.Item(i2)).Type.AsFullName, ((VCCodeElement)dte2.Solution.Item(i1).CodeModel.CodeElements.Item(i2)).FullName);
                    else
                        var = new CppVar(dte2.Solution.Item(i1).CodeModel.CodeElements.Item(i2).Kind.ToString(), ((VCCodeElement)dte2.Solution.Item(i1).CodeModel.CodeElements.Item(i2)).FullName);

                    proj_list[i1 - 1].Variables.Add(var);
                }
            }

            return proj_list;
        }

        static public List<M3DCppFct> ListProjectVariables(EnvDTE.Project project)
        {
            List<M3DCppFct> var_list = new List<M3DCppFct>();

            //EnvDTE.CodeElements c_elements = project.CodeModel.CodeElements;

            foreach(EnvDTE.Document doc in dte2.Documents)
            {
                EnvDTE.CodeElements c_elements = doc.ProjectItem.FileCodeModel.CodeElements;
                GetCompatibleFunctions(var_list, c_elements, doc.FullName);
            }

            return var_list;
        }

        static public void GetCompatibleFunctions(List<M3DCppFct> list, EnvDTE.CodeElements code_elements, string filename, M3DCppFctKind d_kind=M3DCppFctKind.Free, string parent=null)
        {
            foreach(EnvDTE.CodeElement c_element in code_elements)
            {

                if (c_element.Kind == EnvDTE.vsCMElement.vsCMElementFunction)
                {
                    if (IsFunctionM3DCompatible(c_element as EnvDTE.CodeFunction))
                    {
                        list.Add(new M3DCppFct(d_kind, (c_element as EnvDTE.CodeFunction).FullName, filename, parent));
                    }
                }
                else if (c_element.Kind == EnvDTE.vsCMElement.vsCMElementClass)
                {
                    if((c_element as EnvDTE.CodeClass).IsDerivedFrom["m3d::Actor"])
                        GetCompatibleFunctions(list, (c_element as EnvDTE.CodeClass).Members, filename, M3DCppFctKind.Member, (c_element as EnvDTE.CodeClass).FullName);
                }
            }
        }

        static bool IsFunctionM3DCompatible(EnvDTE.CodeFunction function)
        {
            if(function.Type.AsFullName == "void" && function.Parameters.Count == 2)
            {
                if (((EnvDTE.CodeParameter)function.Parameters.Item(1)).Type.AsFullName == "SenderObject &" && ((EnvDTE.CodeParameter)function.Parameters.Item(2)).Type.AsFullName == "UsrInputData &")
                {
                    return true;
                }
            }
            return false;
        }

        public static EnvDTE.Projects GetProjects()
        {
            return dte2.Solution.Projects;
        }

        public static bool GetM3DFWStuff()
        {
            if (!dte2.Solution.IsOpen)
                return false;
            if (dte2.Solution.Projects.Count == 0)
                return false;

            if (_m3dfw_namespace != null && _getFctPtrList_function != null && _getMemberFctPtrList_function != null)
                return true;

            EnvDTE.CodeElements c_elements = dte2.Solution.Projects.Item(1).CodeModel.CodeElements;

            foreach(EnvDTE.CodeElement c_element in c_elements)
            {
                if(c_element.Kind == EnvDTE.vsCMElement.vsCMElementNamespace)
                {
                    if (c_element.FullName == "m3dfw")
                    {
                        _m3dfw_namespace = c_element as EnvDTE.CodeNamespace;
                        foreach (EnvDTE.CodeElement namespace_element in c_element.Children)
                        {
                            if(namespace_element.Kind == EnvDTE.vsCMElement.vsCMElementFunction)
                            {
                                if(namespace_element.FullName == "m3dfw::getFctPtrList")
                                {
                                    _getFctPtrList_function = namespace_element as EnvDTE.CodeFunction;
                                }
                                else if(namespace_element.FullName == "m3dfw::getMemberFctPtrList")
                                {
                                    _getMemberFctPtrList_function = namespace_element as EnvDTE.CodeFunction;
                                }
                            }
                        }
                    }
                }
                if (_m3dfw_namespace != null && _getFctPtrList_function != null && _getMemberFctPtrList_function != null)
                    return true;
            }

            return false;
        }

        #endregion
    }
}
