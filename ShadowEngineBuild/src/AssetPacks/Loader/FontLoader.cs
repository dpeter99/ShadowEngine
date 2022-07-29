using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.AssetPacks.Loader
{
    class FontLoader : ILoader
    {
        public void LoadAsset(Asset asset)
        {
            ShadowFileElement root = asset.data_root;
        }
    }
}
