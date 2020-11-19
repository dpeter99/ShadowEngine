using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.AssetPacks
{
    class PackFileBuildProcess: IBuildProcess
    {
        private Dictionary<DirectoryInfo, List<FileInfo>> files = new Dictionary<DirectoryInfo, List<FileInfo>>();

        private List<string> extensions = new List<string>();

        public PackFileBuildProcess()
        {
            extensions.Add(".tga");
            extensions.Add(".jpg");
            extensions.Add(".png");

            extensions.Add(".obj");
            extensions.Add(".fbx");
        }

        public void FinishSteps()
        {
            /*
            ShadowFileElement root = new ShadowFileElement();
            root.name = "Assets";

            int i = 0;
            foreach (var file in files)
            {
                string relative_file = Path.GetRelativePath(BuildEnviroment.GetResourceSrcFolder(), file);

                var file_tag = new ShadowFileElement();
                file_tag.name = i.ToString();
                file_tag.value = relative_file.Replace('\\','/');
                root.AddProperty(file_tag);
                i++;
            }


            string path = BuildEnviroment.GetResourceSrcFolder() + "/pack.spf";
            
            ShadowFileFormat.WriteFile(root, path);
            */
        }

        public void ProcessAssetPack(DirectoryInfo path)
        {
            foreach (var item in path.GetFiles("*", SearchOption.AllDirectories))
            {
                if (extensions.Contains(item.Extension))
                {
                    files[path].Add(item);
                }
            }
        }
    }
}
