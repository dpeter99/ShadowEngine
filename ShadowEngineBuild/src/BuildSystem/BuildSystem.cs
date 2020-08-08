using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ShadowEngineBuild.src
{
    class BuildSystem
    {
        List<IBuildProcess> processes = new List<IBuildProcess>();

        public void Init()
        {
            processes.Add(new PackFileBuildProcess());
        }


        public void Start()
        {
            ProcessResources();

            FinishSteps();
        }


        void ProcessResources()
        {


            string path = BuildEnviroment.GetResourceFolder();

            var files = System.IO.Directory.GetFiles(path, "**",
                SearchOption.AllDirectories);

            foreach (var item in files)
            {
                foreach (var process in processes)
                {
                    process.ProcessResourceFile(item);
                }
            }
        }

        void FinishSteps()
        {
            
            foreach (var process in processes)
            {
                process.FinishSteps();
            }
            
        }

}
}
