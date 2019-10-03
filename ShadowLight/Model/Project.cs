using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ShadowLight.Services;

namespace ShadowLight.Model
{
    public class Project
    {
        private int _UID;
        public int UID
        {
            get { return _UID; }
            set { _UID = value; }
        }

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
            ShadowFormatParser.Element root = Services.ShadowFormatParser.LoadFile(path);

            UID = int.Parse(root.properties["Asset"].properties["UID"].value);

            var p = root.properties["Project"];

            m_folderPath = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(path), p.GetStringProperty("AssetsFolder"));
            m_assetHierarchy = new AssetHierarchy(this);
        }
    }
}
