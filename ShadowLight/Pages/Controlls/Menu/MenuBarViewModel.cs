using Microsoft.Win32;
using ShadowLight.Model;
using Stylet;

namespace ShadowLight.Pages.Controlls.Menu
{
    public class MenuBarViewModel : Screen 
    {
        private IEventAggregator events;

        private ApplicationState app;

        public MenuBarViewModel(IEventAggregator events, ApplicationState state)
        {
            this.events = events;
            this.app = state;
        }

        public void OpenProject()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                app.OpenProject(openFileDialog.FileName);
            }
                
        }
    }
}