using System;
using TiledSharp;


namespace ShadowEngineBuild
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Shadow Engine Build System");

            BuildEnviroment.SetBuildEnviroment(args[0],args[1]);
            
            Console.WriteLine(BuildEnviroment.ToString());


            ShadowMapConverter.ConvertMaps();


#if DEBUG
            Console.WriteLine("Press enter to close...");
            Console.ReadLine();
#endif
        }
    }
}
