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

        public static string ToString()
        {
            return "Code Folder:\t" + baseCodePath + "\n" +
                   "Content Folder:\t" + baseContentPath + "\n";
        }

        public static string GetMapsFolder()
        {
            return baseContentPath + "\\Worlds\\";
        }

    }
}
