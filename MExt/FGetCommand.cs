//------------------------------------------------------------------------------
// <copyright file="FGetCommand.cs" company="Company">
//     Copyright (c) Company.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.ComponentModel.Design;
using System.Globalization;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

using System.Diagnostics;


namespace MExt
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class FGetCommand
    {
        #region chujmnietoboli
        /// <summary>
        /// Command ID.
        /// </summary>
        public const int CommandId = 0x0100;

        /// <summary>
        /// Command menu group (command set GUID).
        /// </summary>
        public static readonly Guid CommandSet = new Guid("fbe668c9-8c9c-405d-8b83-419453644a1a");

        /// <summary>
        /// VS Package that provides this command, not null.
        /// </summary>
        private readonly Package package;

        /// <summary>
        /// Initializes a new instance of the <see cref="FGetCommand"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        private FGetCommand(Package package)
        {
            if (package == null)
            {
                throw new ArgumentNullException("package");
            }

            this.package = package;

            OleMenuCommandService commandService = this.ServiceProvider.GetService(typeof(IMenuCommandService)) as OleMenuCommandService;
            if (commandService != null)
            {
                var menuCommandID = new CommandID(CommandSet, CommandId);
                var menuItem = new MenuCommand(this.DoThings, menuCommandID);
                commandService.AddCommand(menuItem);
            }
        }

        /// <summary>
        /// Gets the instance of the command.
        /// </summary>
        public static FGetCommand Instance
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the service provider from the owner package.
        /// </summary>
        private IServiceProvider ServiceProvider
        {
            get
            {
                return this.package;
            }
        }

        /// <summary>
        /// Initializes the singleton instance of the command.
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        public static void Initialize(Package package)
        {
            Instance = new FGetCommand(package);
        }

        #endregion

        /// <summary>
        /// This function is the callback used to execute the command when the menu item is clicked.
        /// See the constructor to see how the menu item is associated with this function using
        /// OleMenuCommandService service and MenuCommand class.
        /// </summary>
        /// <param name="sender">Event sender.</param>
        /// <param name="e">Event args.</param>
        private void MenuItemCallback(object sender, EventArgs e)
        {
            string message = string.Format(CultureInfo.CurrentCulture, "Inside {0}.MenuItemCallback()", this.GetType().FullName);
            string title = "FGetCommand";

            // Show a message box to prove we were here
            VsShellUtilities.ShowMessageBox(
                this.ServiceProvider,
                message,
                title,
                OLEMSGICON.OLEMSGICON_INFO,
                OLEMSGBUTTON.OLEMSGBUTTON_OK,
                OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST);
        }

        private void StartNotePad(object sender, EventArgs e)
        {
            Process proc = new Process();
            proc.StartInfo.FileName = "notepad.exe";
            proc.Start();
        }

        public struct CVar
        {
            public string type;
            public string name;
        }

        public CVar[][] getInfo()
        {
            EnvDTE.DTE dte = (EnvDTE.DTE)this.ServiceProvider.GetService(typeof(EnvDTE.DTE));

            EnvDTE.Solution solution = dte.Solution;

            CVar[][] vars = new CVar[solution.Projects.Count][];

            for (int i1 = 0; i1 < solution.Projects.Count; i1++)
            {
                vars[i1] = new CVar[solution.Projects.Item(i1).CodeModel.CodeElements.Count];

                for (int i2 = 0; i2 < solution.Projects.Item(i1).CodeModel.CodeElements.Count; i2++)
                {
                    vars[i1][i2].type = solution.Projects.Item(i1).CodeModel.CodeElements.Item(i2).GetType().ToString();
                    vars[i1][i2].name = solution.Projects.Item(i1).CodeModel.CodeElements.Item(i2).Name;
                }
            }

            return vars;
        }

        private void DoThings(object sender, EventArgs e)
        {

        }
    }
}
