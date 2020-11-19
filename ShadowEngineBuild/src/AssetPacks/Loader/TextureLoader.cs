using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using ShadowEngineBuild.src.AssetPacks.Loader;

namespace ShadowEngineBuild.AssetPacks.Loader
{
    class TextureLoader : ILoader
    {
        public void LoadAsset(Asset asset)
        {
            ShadowFileElement root = asset.data_root;

            if (root.properties.ContainsKey("CubeMap"))
            {
                var cubeMap = root.properties["CubeMap"];

                //var fullFilePath = Path.Combine(asset.src.Directory.FullName, cubeMap.GetStringProperty("up"));

                asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "up"));
                asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "down"));
                asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "front"));
                asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "back"));
                asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "left"));
                asset.sourceFiles.Add(cubeMap.GetPropertyFileInfo(asset, "right"));

            }
        }
    }
}
