using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CppSharp;
using CppSharp.AST;
using CppSharp.Generators;

namespace ShadowEngineBuild.Interop
{
    class ShadowEngineLib : ILibrary
    {
        public void Setup(Driver driver)
        {
            var parseroptions = driver.ParserOptions;
            parseroptions.EnableRTTI = true;
            parseroptions.AddArguments("-fcxx-exceptions");

            var options = driver.Options;
            options.GeneratorKind = GeneratorKind.CSharp;
            

            var module = options.AddModule("ShadowEngine");
            module.IncludeDirs.Add(BuildEnviroment.GetCodeFolder());
            module.IncludeDirs.AddRange(BuildEnviroment.GetIncludePaths());

            module.Headers.Add("ShadowWindow.h");

            module.LibraryDirs.Add(BuildEnviroment.GetBuildOutput());
            module.Libraries.Add("ShadowEngine.lib");
            module.Libraries.Add("SDL2.dll");
        }

        public void Postprocess(Driver driver, ASTContext ctx)
        {
            
        }

        public void Preprocess(Driver driver, ASTContext ctx)
        {
            
        }

        public void SetupPasses(Driver driver)
        {
            
        }
    }
}
