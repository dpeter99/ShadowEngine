using CppSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.Interop
{
    public static class InteropGenerator
    {
        public static void Generate()
        {
            ConsoleDriver.Run(new ShadowEngineLib());
        }
    }
}
