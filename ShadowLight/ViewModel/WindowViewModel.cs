using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.ViewModel
{
    class WindowViewModel
    {
        ApplicationState applicationState;

        public bool projectLoaded
        {
            get
            {
                if (applicationState != null)
                {
                    return applicationState.activeProject != null;
                }
                else
                {
                    return false;
                }
            }
        }

        public string projectName
        {
            get
            {
                return projectLoaded ? applicationState.activeProject.name : "";
            }
        }

        public void OpenProject(string path)
        {
            applicationState.LoadProject(path);
        }
    }
}
