using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ShadowEngineBuild
{
    public static class BuildEnviroment
    {
        private static string baseCodePath;

        private static DirectoryInfo assetSrc;
        private static DirectoryInfo outputPath;

        private static List<DirectoryInfo> packsSrc = new List<DirectoryInfo>();

        public static void SetBuildEnviroment(DirectoryInfo assetRoot,
                                              DirectoryInfo output)
        {

            assetSrc = assetRoot;
            outputPath = output;

            var packs = assetSrc.GetDirectories();
            foreach (var pack in packs)
            {
                Console.WriteLine("Found asset pack: " + pack.Name);
                packsSrc.Add(pack);
            }
        }

        public new static string ToString()
        {
            return "Code Folder:" + baseCodePath + "\n" +
                   "Content Folder:" + assetSrc + "\n";
        }

        public static List<DirectoryInfo> GetAssetPackSourceDirectories()
        {
            return packsSrc;
        }

        /// <summary>
        /// The root folder for the asset packs on the output side
        /// </summary>
        /// For example: ``C:\EngnieBuild\x64-Win10\Resources\``
        /// where the build folder is: ``C:\EngnieBuild\x64-Win10\``
        /// <returns></returns>
        public static DirectoryInfo GetAssetPackOutputRoot()
        {
            return new DirectoryInfo(outputPath.FullName + "/Resources/");
        }

        public static string GetMapsFolder()
        {
            return assetSrc + "/Worlds/";
        }

        public static string GetResourceSrcFolder()
        {
            return assetSrc.FullName;
        }
    }
}
