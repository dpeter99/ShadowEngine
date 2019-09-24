using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Model
{
    public class Project
    {
        private string m_folderPath;
        public string folderPath
        {
            get => m_folderPath;
        }


        private string m_name;

        private AssetHierarchy m_assetHierarchy;

        public AssetHierarchy AssetHierarchy
        {
            get => m_assetHierarchy;
        }

        public Project(string path)
        {
            m_folderPath = System.IO.Path.GetDirectoryName(path);
            m_assetHierarchy = new AssetHierarchy(this);
        }
    }
}
