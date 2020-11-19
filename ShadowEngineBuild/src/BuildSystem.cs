using ShadowEngineBuild.AssetPacks;
using ShadowEngineBuild.AssetPacks.Loader;
using ShadowEngineBuild.src.AssetPacks.Loader;

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ShadowEngineBuild
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
            List<AssetPack> assetPacks = new List<AssetPack>();

            List<ILoader> assetLoader = new List<ILoader>();
            assetLoader.Add(new TextureLoader());
            assetLoader.Add(new ShaderLoader());

            //Collect asset pack data
            foreach (var item in BuildEnviroment.GetAssetPackSourceDirectories())
            {
                assetPacks.Add(new AssetPack(item));
            }


            
            
            
            foreach (var pack in assetPacks)
            {
                //Transform resources if needed
                foreach (var asset in pack.files)
                {
                    foreach (var loader in assetLoader)
                    {
                        loader.LoadAsset(asset);
                    }
                }
                //Write metadata

                //Copy the assets
                DirectoryInfo outputDir = BuildEnviroment.GetAssetPackOutputRoot();
                foreach (var asset in pack.files)
                {
                    Console.WriteLine("Copying asset: " + asset.GetRelativePath());

                    asset.CopyToOutput();
                    /*
                    FileInfo output_file = asset.GetOutputFile();
                    output_file.Directory.Create();
                    asset.src.CopyTo(output_file.FullName, true);
                    */
                }


                //Write pack metadata
                pack.WritePackMetadata();
            }
            


            /*
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
            */
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
