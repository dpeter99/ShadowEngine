using System;
using System.Diagnostics;
using TiledSharp;

using ShadowEngineBuild.Interop;

namespace ShadowEngineBuild
{
    class Program
    {
        static int Main(string[] args)
        {
            //Debugger.Launch();

            Console.WriteLine("Shadow Engine Build System");

            BuildEnviroment.SetBuildEnviroment(args[0],args[1], args[2]);
            
            Console.WriteLine(BuildEnviroment.ToString());


            Interop.InteropGenerator.Generate();


#if HZ_DEBUG
            Console.WriteLine("Press enter to close...");
            Console.ReadLine();
#endif
            return 0;
        }
    }
}
