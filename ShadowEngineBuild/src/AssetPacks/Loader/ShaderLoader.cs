using ShadowEngineBuild.AssetPacks;
using ShadowEngineBuild.AssetPacks.Loader;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.src.AssetPacks.Loader
{
    class ShaderLoader : ILoader
    {
        public void LoadAsset(Asset asset)
        {
            ShadowFileElement root = asset.data_root;

            if (root.properties.ContainsKey("Shader"))
            {
                var cubeMap = root.properties["Shader"];

                //var fullFilePath = Path.Combine(asset.src.Directory.FullName, cubeMap.GetStringProperty("up"));

                //asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "VertexShader", ".hlsl"));
                //asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "FragmentShader", ".hlsl"));
                

            }
        }
    }
}
