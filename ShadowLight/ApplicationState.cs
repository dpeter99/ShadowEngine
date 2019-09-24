using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ShadowLight.Model;

namespace ShadowLight
{
    class ApplicationState
    {
        public Project activeProject;

        public ApplicationState()
        {
            
        }

        public void LoadProject(string path)
        {
            activeProject = new Project(path);
        }
    }
}
