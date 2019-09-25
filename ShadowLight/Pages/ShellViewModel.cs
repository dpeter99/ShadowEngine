using System;
using Stylet;

using ShadowLight.Pages.Controlls;
using ShadowLight.Pages.Controlls.Menu;
using ShadowLight.Model;

namespace ShadowLight.Pages
{
    public class ShellViewModel : Screen
    {
        ApplicationState app;

        private AssetBrowserViewModel m_assetBrowser;
        public AssetBrowserViewModel assetBrowser { 
            get {
                if(app.acticeProject == null)
                {
                    return null;
                }
                return m_assetBrowser;
            }
            private set
            {

            }
        }

        public MenuBarViewModel menuBar { get; private set; }

        public ShellViewModel(Model.ApplicationState state, MenuBarViewModel barViewModel)
        {
            assetBrowser = new AssetBrowserViewModel(state);
            menuBar = barViewModel;
        }
    }
}
