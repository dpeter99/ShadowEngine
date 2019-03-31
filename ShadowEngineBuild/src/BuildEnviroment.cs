using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ShadowEngineBuild
{
    public static class BuildEnviroment
    {
        private static string baseCodePath;

        private static string baseContentPath;

        public static void SetBuildEnviroment(string code, string contnent)
        {
            baseCodePath = code;
            baseContentPath = contnent;
        }

        public new static string ToString()
        {
            return "Code Folder:" + baseCodePath + "\n" +
                   "Content Folder:" + baseContentPath + "\n";
        }

        public static string GetMapsFolder()
        {
            return baseContentPath + "/Worlds/";
        }

    }
}
