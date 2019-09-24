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
        Asset assetroot;

        private Project m_project;

        public AssetHierarchy(Project project)
        {
            m_project = project;
            assetroot = new Asset(m_project.folderPath);
            UpdateAssetsList();
        }

        public void UpdateAssetsList()
        {
            RecursiveAssetDiscovery(assetroot);
        }

        public void RecursiveAssetDiscovery(Asset asset)
        {
            var folders = Directory.GetDirectories(asset.path);
            foreach (var item in folders)
            {
                Asset c = new Asset(item);
                RecursiveAssetDiscovery(c);
                asset.childs.Add(c);
            }
        }
    }
}
