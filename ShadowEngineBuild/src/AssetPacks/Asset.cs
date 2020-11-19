using System;
using System.Collections.Generic;
using System.IO;

namespace ShadowEngineBuild.AssetPacks
{
    /// <summary>
    /// Represents an asset
    /// </summary>
    public class Asset
    {
        /// <summary>
        /// The metadata file that connects all the parts
        /// </summary>
        public FileInfo src;

        public ShadowFileElement data_root;

        string relative;

        /// <summary>
        /// Extra files that are needed for the asset
        /// </summary>
        /// Like the texture files for a cube map
        public List<FileInfo> sourceFiles = new List<FileInfo>();

        public Asset(FileInfo srcFile)
        {
            src = srcFile;

            data_root = ShadowFileFormat.LoadFile(src.FullName);

            relative = Path.GetRelativePath(BuildEnviroment.GetResourceSrcFolder(), srcFile.FullName);
        }

        public void CopyToOutput()
        {
            var output_file = GetOutputFile();
            output_file.Directory.Create();
            src.CopyTo(output_file.FullName, true);

            foreach (var file in sourceFiles)
            {
                var path = Path.GetRelativePath(BuildEnviroment.GetResourceSrcFolder(), file.FullName);
                //var path = Path.Combine(src.Directory.FullName, file.FullName);
                var copy_to = Path.Combine(BuildEnviroment.GetAssetPackOutputRoot().FullName, path);

                try
                {
                    file.CopyTo(copy_to, true);
                }
                catch(Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        public FileInfo GetOutputFile()
        {
            return new FileInfo(Path.Combine(BuildEnviroment.GetAssetPackOutputRoot().FullName, relative));
        }

        public string GetRelativePath()
        {
            return relative;
        }
    }
}
