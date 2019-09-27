using System;
using ShadowLight.Controls.AssetBrowser;
using ShadowLight.Controls.MenuBar;
using ShadowLight.Model;
using Stylet;

namespace ShadowLight.Pages
{
    public class ShellViewModel : Screen
    {
        public Project ActiveProject { get; private set; }

        public MenuBarViewModel MenuBar { get; private set; }

        public AssetBrowserViewModel AssetBrowser { get; private set; }

        public ShellViewModel()
        {
            MenuBar= new MenuBarViewModel();

        }

        public ShellViewModel(MenuBarViewModel menuBar)
        {
            menuBar.Parent = this;
            this.MenuBar = menuBar;
        }

        public void OpenProject(string path)
        {
            ActiveProject = new Project(path);
            AssetBrowser = new AssetBrowserViewModel(ActiveProject);
        }
    }
}
