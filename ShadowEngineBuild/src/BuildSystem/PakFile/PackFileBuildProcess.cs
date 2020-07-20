using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.src
{
    class PackFileBuildProcess: IBuildProcess
    {
        private List<string> files = new List<string>();

        private List<string> extensions = new List<string>();

        public PackFileBuildProcess()
        {
            extensions.Add(".tga");
        }

        public void FinishSteps()
        {
            ShadowFileElement root = new ShadowFileElement();
            root.name = "Assets";

            int i = 0;
            foreach (var file in files)
            {
                string relative_file = Path.GetRelativePath(BuildEnviroment.GetResourceFolder(), file);

                var file_tag = new ShadowFileElement();
                file_tag.name = i.ToString();
                file_tag.value = relative_file;
                root.AddProperty(file_tag);
                i++;
            }


            string path = BuildEnviroment.GetResourceFolder() + "/pack.spf";
            
            ShadowFileFormat.WriteFile(root, path);
        }

        public void ProcessResourceFile(string path)
        {
            if (extensions.Contains(Path.GetExtension(path)))
            {
                files.Add(path);
            }
        }
    }
}
