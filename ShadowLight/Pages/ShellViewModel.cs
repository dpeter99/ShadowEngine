using System;
using ShadowLight.Controls.AssetBrowser;
using ShadowLight.Controls.MenuBar;
using Stylet;

namespace ShadowLight.Pages
{
    public class ShellViewModel : Screen
    {
        private MenuBarViewModel _menuBar;

        public MenuBarViewModel MenuBar { get; private set; }
        public AssetBrowserViewModel AssetBrowser { get; private set; }

        public ShellViewModel(MenuBarViewModel menuBar)
        {
            this.MenuBar = menuBar;
        }
    }
}
