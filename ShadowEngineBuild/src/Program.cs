using ShadowEngineBuild.src;

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using TiledSharp;


namespace ShadowEngineBuild
{
    class Program
    {
        static int Main(string[] args)
        {
            //Debugger.Launch();
            Console.WriteLine("########################################################################");
            Console.WriteLine("########################################################################");
            Console.WriteLine("##############       Shadow Engine Build System      ###################");
            Console.WriteLine("########################################################################");
            Console.WriteLine("########################################################################");

            if (String.IsNullOrEmpty(args[0]) || String.IsNullOrEmpty(args[1]))
                return 1;

            BuildEnviroment.SetBuildEnviroment(args[0],args[1]);
            
            Console.WriteLine(BuildEnviroment.ToString());


            ShadowMapConverter.ConvertMaps();

            BuildSystem system = new BuildSystem();
            system.Init();
            system.Start();



#if DEBUG
            Console.WriteLine("Press enter to close...");
            Console.ReadLine();
#endif
            return 0;
        }
    }
}
