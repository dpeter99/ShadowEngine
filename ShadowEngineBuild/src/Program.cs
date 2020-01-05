using System;
using System.Diagnostics;
using TiledSharp;


namespace ShadowEngineBuild
{
    class Program
    {
        static int Main(string[] args)
        {
            //Debugger.Launch();

            Console.WriteLine("Shadow Engine Build System");

            if (String.IsNullOrEmpty(args[0]) || String.IsNullOrEmpty(args[1]))
                return 1;

            BuildEnviroment.SetBuildEnviroment(args[0],args[1]);
            
            Console.WriteLine(BuildEnviroment.ToString());


            ShadowMapConverter.ConvertMaps();


#if DEBUG
            Console.WriteLine("Press enter to close...");
            Console.ReadLine();
#endif
            return 0;
        }
    }
}
