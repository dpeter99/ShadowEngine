using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Model
{
    public class Asset
    {
        public string path;
        private int m_isFolder;

        public List<Asset> childs;

        public Asset(string path)
        {
            this.path = path;
            childs = new List<Asset>();
        }
    }
}
