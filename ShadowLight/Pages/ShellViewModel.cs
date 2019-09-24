using System;
using Stylet;

using ShadowLight.Pages.Controlls;
using ShadowLight.Pages.Controlls.Menu;

namespace ShadowLight.Pages
{
    public class ShellViewModel : Screen
    {
        public AssetBrowserViewModel assetBrowser { get; private set; }
        public MenuBarViewModel menuBar { get; private set; }

        public ShellViewModel(Model.ApplicationState state)
        {
            assetBrowser = new AssetBrowserViewModel(state);
            menuBar = new MenuBarViewModel(state);
        }
    }
}
