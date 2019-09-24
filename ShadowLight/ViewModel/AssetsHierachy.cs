using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.ViewModel
{
    class AssetsHierachy: INotifyPropertyChanged 
    {
        void NotifiyPropertyChanged(string property)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(property));
        }

        public event PropertyChangedEventHandler PropertyChanged;


        public string test { get; set; }="asdasd";

        private List<AsssetHierarchyElement> m_folders;
        public List<AsssetHierarchyElement> Folders
        {
            get { return m_folders; }
            set
            {
                m_folders = value;
                NotifiyPropertyChanged("Folders");
            }
        }

        public AssetsHierachy()
        {
            m_folders = new List<AsssetHierarchyElement>();

            Folders.Add(new AsssetHierarchyElement("asdasd"));
        }
    }
}
