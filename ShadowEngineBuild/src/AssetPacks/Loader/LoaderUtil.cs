using ShadowEngineBuild.AssetPacks;

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.src.AssetPacks.Loader
{
    public static class LoaderUtil
    {


        public static FileInfo GetPropertyFileInfo(this ShadowFileElement element, Asset asset, string name, string ext = "")
        {
            var fullFilePath = Path.Combine(asset.src.Directory.FullName, element.GetStringProperty(name) + ext);

            return new FileInfo(fullFilePath);
        }


    }
}
