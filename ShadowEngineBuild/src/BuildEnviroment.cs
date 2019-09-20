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
        private static string includePaths;

        public static void SetBuildEnviroment(string engineFolder, string buildFolder, string includePaths)
        {
            BuildEnviroment.engineFolder = engineFolder;
            BuildEnviroment.buildFolder = buildFolder;
            BuildEnviroment.includePaths = includePaths;
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
    }
}
