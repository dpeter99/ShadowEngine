using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Model
{

    public class AssetTypeAttribute : Attribute
    {
        public string ext;

        public AssetTypeAttribute(string extention)
        {
            this.ext = extention;
        }
    }
}
