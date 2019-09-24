using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ShadowEngineBuild
{
    public static class BuildEnviroment
    {
        private static string engineFolder;
        private static string buildFolder;


        public static void SetBuildEnviroment(string engineFolder, string buildFolder)
        {
            BuildEnviroment.engineFolder = engineFolder;
            BuildEnviroment.buildFolder = buildFolder;

        }

        public new static string ToString()
        {
            return "Code Folder:" + GetCodeFolder() + "\n";
        }

        public static string GetCodeFolder()
        {
            return engineFolder + "/src";
        }

        public static string GetBuildOutput()
        {
            return buildFolder;
        }

        public static List<string> GetIncludePaths()
        {
            List<string> inc = new List<string>();
            inc.Add(engineFolder + "/dependencies/GLAD/include");
            inc.Add(engineFolder + "/dependencies/glm");
            inc.Add(engineFolder + "/dependencies/imgui");
            inc.Add(engineFolder + "/dependencies/SDL2/include");
            inc.Add(engineFolder + "/dependencies/spdlog/include");

            return inc;
        }

        public static List<string> GetHeaders()
        {
            List<string> headers = new List<string>();


            string directory = Path.GetDirectoryName(GetCodeFolder());
            headers.AddRange(Directory.GetFiles(directory, @"*.h",SearchOption.AllDirectories));
            return headers;
        }
    }
}
