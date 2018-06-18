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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;

namespace M3DEngineUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        private void CloseProgram(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void OpenFile(object sender, RoutedEventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = ".mob files|*.mob|.mmt files|*.mmt|Bitmap files|*.bmp|PNG files|*.png|.mdp files|*.mdp|.vert files|*.vert|.frag files|*.frag|All files|*.*";
            open.ShowDialog();          
        }

        private void NewFile(object sender, RoutedEventArgs e)
        {
            MainWindow a = new MainWindow();
            this.Close();
            a.Show();
        }

        private void SaveFile(object sender, RoutedEventArgs e)
        {
            SaveFileDialog zapis = new SaveFileDialog();
            zapis.Filter = "Text file (*.txt)|*.txt|C# file (*.cs)|*.cs";
            zapis.ShowDialog();

        }
    }
}
