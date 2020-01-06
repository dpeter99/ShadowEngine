using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using System.IO;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ShadowLight.Model
{
    public class AssetHierarchy
    {
        public Asset AssetsFolder;

        private Project m_project;

        public AssetHierarchy(Project project)
        {
            m_project = project;
            UpdateAssetsList();
        }

        public void UpdateAssetsList()
        {
            AssetsFolder = new Asset(m_project.folderPath, Asset.Type.Folder);
        }

        
    }
}
