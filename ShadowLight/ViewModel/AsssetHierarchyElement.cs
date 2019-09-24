using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.ViewModel
{
    class AsssetHierarchyElement
    {
        public string FullPath { get; }
        public string Name { get; }
        public List<AsssetHierarchyElement> Folders { get; }

        public AsssetHierarchyElement(string name)
        {
            Name = name;
        }
    }
}
