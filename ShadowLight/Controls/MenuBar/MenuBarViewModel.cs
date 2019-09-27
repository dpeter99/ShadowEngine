using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;
using ShadowLight.Pages;
using Stylet;

namespace ShadowLight.Controls.MenuBar
{
    public class MenuBarViewModel : Screen
    {
        public MenuBarViewModel()
        {
                   
        }

        public void OpenProject()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                ((ShellViewModel)this.Parent).OpenProject(openFileDialog.FileName);
            }
        }
    }
}
