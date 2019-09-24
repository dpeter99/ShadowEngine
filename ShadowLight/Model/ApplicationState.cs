using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Model
{
    public class ApplicationState
    {
        private Project m_activeProject;

        public Project acticeProject
        {
            get => m_activeProject;
        }

        public void OpenProject(string path)
        {
            m_activeProject = new Project(path);
        }
    }
}
