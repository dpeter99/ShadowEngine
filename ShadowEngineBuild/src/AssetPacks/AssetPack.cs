using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.AssetPacks
{
    public class AssetPack
    {
        public DirectoryInfo srcDir;
        public string name;

        public List<Asset> files = new List<Asset>();

        public AssetPack(DirectoryInfo srcDirectory)
        {
            srcDir = srcDirectory;

            name = srcDirectory.Name;

            foreach (var item in srcDir.GetFiles("*.sff", SearchOption.AllDirectories))
            {
                files.Add(new Asset(item));
            }
        }

        public void WritePackMetadata()
        {
            ShadowFileElement root = new ShadowFileElement();
            root.name = "Assets";

            int i = 0;
            foreach (var file in files)
            {
                string relative_file = Path.GetRelativePath(srcDir.FullName, file.src.FullName);

                var file_tag = new ShadowFileElement();
                file_tag.name = i.ToString();
                file_tag.value = relative_file.Replace('\\', '/');
                root.AddProperty(file_tag);
                i++;
            }


            string path = BuildEnviroment.GetAssetPackOutputRoot() + $"/{name}/pack.spf";

            ShadowFileFormat.WriteFile(root, path);
        }
    }
}
