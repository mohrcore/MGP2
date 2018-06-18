//------------------------------------------------------------------------------
// <copyright file="VListWindowControl.xaml.cs" company="Company">
//     Copyright (c) Company.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

namespace MExt
{
    using System.Collections.Generic;
    using System.Diagnostics.CodeAnalysis;
    using System.Windows;
    using System.Windows.Controls;

    /// <summary>
    /// Interaction logic for VListWindowControl.
    /// </summary>
    public partial class VListWindowControl : UserControl
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VListWindowControl"/> class.
        /// </summary>
        public VListWindowControl()
        {
            this.InitializeComponent();

            content_list = new List<FGetter.M3DCppFct>();
        }

        /// <summary>
        /// Handles click on the button by displaying a message box.
        /// </summary>
        /// <param name="sender">The event sender.</param>
        /// <param name="e">The event args.</param>
        [SuppressMessage("Microsoft.Globalization", "CA1300:SpecifyMessageBoxOptions", Justification = "Sample code")]
        [SuppressMessage("StyleCop.CSharp.NamingRules", "SA1300:ElementMustBeginWithUpperCaseLetter", Justification = "Default event handler naming pattern")]

        private List<FGetter.M3DCppFct> content_list;

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            //MessageBox.Show(
            //    string.Format(System.Globalization.CultureInfo.CurrentUICulture, "Invoked '{0}'", this.ToString()),
            //    "VListWindow");

            //EnvDTE80.DTE2 dte2 = (EnvDTE80.DTE2)System.Runtime.InteropServices.Marshal.GetActiveObject("VisualStudio.DTE.14.0");

            //List<FGetter.CppProj> projects = FGetter.getSolutionStruct();

            EnvDTE.Projects projects = FGetter.GetProjects();

            content_list.Clear();

            foreach (EnvDTE.Project project in projects)
            {
                content_list.AddRange(FGetter.ListProjectVariables(project));
            }

            List<string> name_list = new List<string>();

            foreach(FGetter.M3DCppFct fct in content_list)
            {
                name_list.Add(fct.FullName);
            }

            ResListBox.ItemsSource = name_list;

        }

        private void ResListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void button_Click_c_ex_btn(object sender, RoutedEventArgs e)
        {
            EnvDTE.Projects projects = FGetter.GetProjects();
            if (projects.Count == 0)
                return;

            //projects.Item(1).ProjectItems.AddFolder("M3D AutoExport");
            string template_path = ((EnvDTE80.Solution2)FGetter.dte2.Solution).GetProjectItemTemplate("Mext Cpp Export File.zip", "VC");
            if (!CheckForProjectItem(projects.Item(1), "M3D_export.cpp"))
                projects.Item(1).ProjectItems.AddFromTemplate(template_path, "M3D_export.cpp");
            else
                MessageBox.Show(string.Format(System.Globalization.CultureInfo.CurrentUICulture, "File already exists"), "Can't create file!");
        }

        private void button_Click_add_to_export(object sender, RoutedEventArgs e)
        {
            EnvDTE80.DTE2 dte2 = FGetter.dte2;

            if (!dte2.Solution.IsOpen)
            {
                MessageBox.Show(string.Format(System.Globalization.CultureInfo.CurrentUICulture, "No solution is opened!"), "Couldn't find a solution");
                return;
            }
            if (dte2.Solution.Projects.Count == 0)
            {
                MessageBox.Show(string.Format(System.Globalization.CultureInfo.CurrentUICulture, "No projects is opened!"), "Couldn't find a project");
                return;
            }

            EnvDTE.Project project = dte2.Solution.Projects.Item(1);

            if (!CheckForProjectItem(project, "M3D_export.cpp"))
            {
                MessageBoxResult create_export_file = MessageBox.Show(
                    string.Format(System.Globalization.CultureInfo.CurrentUICulture, "Couldn't find M3D_export.cpp file. Would you like to create one?"),
                    "No export file", MessageBoxButton.OKCancel
                    );

                if (create_export_file != MessageBoxResult.OK)
                    return;

                button_Click_c_ex_btn(sender, e);
            }

            if (!FGetter.GetM3DFWStuff())
            {
                MessageBox.Show(string.Format(System.Globalization.CultureInfo.CurrentUICulture, "Couldn't find proper M3D definitions.\nDid you mess with the export file?"), "No proper definitions found!");
                return;
            }

            EnvDTE.EditPoint start_point1 = FGetter.getFctPtrList_function.GetStartPoint().CreateEditPoint();
            EnvDTE.EditPoint end_point1 = FGetter.getFctPtrList_function.GetEndPoint().CreateEditPoint();
            EnvDTE.EditPoint start_point2 = FGetter.getMemberFctPtrList_function.GetStartPoint().CreateEditPoint();
            EnvDTE.EditPoint end_point2 = FGetter.getMemberFctPtrList_function.GetEndPoint().CreateEditPoint();

            //EnvDTE.EditPoint place_to_write = end_point;

            if (!start_point1.FindPattern("//Body to be generated", 0, start_point1) || !start_point2.FindPattern("//Body to be generated", 0, start_point2))
            {
                MessageBox.Show(string.Format(System.Globalization.CultureInfo.CurrentUICulture, "Function definition requires the\n\"//Body to be generated\" comment\nto be properly recognized"), "No proper definitions found!");
                return;
            }

            start_point1.CharRight(22);
            start_point2.CharRight(22);

            if (content_list[ResListBox.SelectedIndex].Kind == FGetter.M3DCppFctKind.Free)
                start_point1.Insert("\n\t\tdata.push_back(m3dfw::UFctInfo(\"" + ResListBox.SelectedItem.ToString() + "\", (UserFct_ptr)" + ResListBox.SelectedItem.ToString() + ");");
            else if(content_list[ResListBox.SelectedIndex].Kind == FGetter.M3DCppFctKind.Member)
                start_point2.Insert("\n\t\tdata.push_back(m3dfw::UMemberFctInfo(\"" + ResListBox.SelectedItem.ToString() + "\", CAST_TO_ACTOR_MEMBER(" + ResListBox.SelectedItem.ToString() + "));");

            //EnvDTE.Document doc = dte2.Documents.Item("M3D_export.cpp").ProjectItem.FileCodeModel.CodeElements.Item;
        }

        bool CheckForProjectItem(EnvDTE.Project project, string item_name)
        {
            return System.IO.File.Exists(project.FullName.Trim((project.Name + ".vcxproj").ToCharArray()) + item_name);
        }

        //bool CheckForInclude(EnvDTE.CodeElements c_elements, string include)
        //{
        //    foreach(EnvDTE.CodeElement c_element in c_elements)
        //    {
        //        if(c_element.Kind == EnvDTE.vsCMElement.vsCMElementIncludeStmt)
        //        {

        //        }
        //    }
        //}
    }
}