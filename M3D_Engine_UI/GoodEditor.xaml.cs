using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Interop;
using M3D_FW_CSHARP_WRAP;

namespace M3DEngineUI
{
    /// <summary>
    /// Logika interakcji dla klasy GoodEditor.xaml
    /// </summary>
    public partial class GoodEditor : Window
    {
        ResourceManager rm;
        ResourceLoader rl;
        ShaderManager sm;

        public GoodEditor()
        {
            InitializeComponent();

            Loaded += GoodEditor_Loaded;
        }

        void GoodEditor_Loaded(object sender, RoutedEventArgs e)
        {
            viewport_host = new EngineViewportHwndHost(720, 480, this);
            ViewportBorder.Child = viewport_host;

            bool m3dsucc = M3DFWUtil.Init();

            rm = new ResourceManager_GC();
            rl = new ResourceLoader_GC(rm);
            sm = new ShaderManager_GC();

            //PROBLEM with clearing GLSL programs and possibly other unmanaged resources. Could GC be a problem?
            bool succ = rl.loadMaterialResourcesFromMDPFile("Resources/tm3.mdp", sm); // ~ S U C C ~

            //TODO ASAP: fix loading from paths other than root dir. Fix error checking!
            //EDIT: Done :)

            if (succ)
            {
                Resource tm3_model_res = rl.importGfxModel3d("Resources/tm3.mob", "tm3");
                //GfxObject model1 = new GfxObject_GC(tm3_model_res);


            }

        }

        EngineViewportHwndHost viewport_host;

        private void exit_menuitem_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            rm.clearAllResources();
        }
    }
}
