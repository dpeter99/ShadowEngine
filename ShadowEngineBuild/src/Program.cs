using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

using System.CommandLine;


namespace ShadowEngineBuild
{
    class Program
    {



        static int Main(string[] args)
        {
            RootCommand rootCommand = new RootCommand();
            Option<DirectoryInfo> assetRootOption = new Option<DirectoryInfo>(
                    "--asset-root",
                    getDefaultValue: (() => null),
                    description: "An option whose argument is parsed as an int"
                    );
            Option<DirectoryInfo> output = new Option<DirectoryInfo>(
                    "--output",
                    getDefaultValue: (() => null),
                    description: "An option whose argument is parsed as an int"
                    );

            rootCommand.Add(assetRootOption);
            rootCommand.Add(output);

            //Debugger.Launch();
            Console.WriteLine("########################################################################");
            Console.WriteLine("########################################################################");
            Console.WriteLine("##############       Shadow Engine Build System      ###################");
            Console.WriteLine("########################################################################");
            Console.WriteLine("########################################################################");

            var res = rootCommand.Parse(args);

            var assetRoot = res.ValueForOption(assetRootOption);
            var outFolder = res.ValueForOption(output);


            BuildEnviroment.SetBuildEnviroment(assetRoot: assetRoot, output:outFolder);

            Console.WriteLine(BuildEnviroment.ToString());


            //ShadowMapConverter.ConvertMaps();

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
