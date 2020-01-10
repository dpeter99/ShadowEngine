using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Sledge.Common.Translations;

namespace Sledge.BspEditor.Environment.ShadowEngine
{
    [Export(typeof(IEnvironmentFactory))]
    [AutoTranslate]
    class ShadowEngineEnviromentFactory : IEnvironmentFactory
    {
        public Type Type { get; }
        public string TypeName { get; }
        public string Description { get; }

        private T GetVal<T>(Dictionary<string, string> dictionary, string key, T def = default(T))
        {
            if (dictionary.TryGetValue(key, out var val))
            {
                try
                {
                    return (T)Convert.ChangeType(val, typeof(T), CultureInfo.InvariantCulture);
                }
                catch
                {
                    //
                }
            }
            return def;
        }

        public IEnvironment Deserialise(SerialisedEnvironment environment)
        {
            var gse = new ShadowEngineEnviroment()
            {
                ID = environment.ID,
                Name = environment.Name,
                BaseDirectory = GetVal(environment.Properties, "BaseDirectory", ""),
            };

            return gse;
        }

        public SerialisedEnvironment Serialise(IEnvironment environment)
        {
            var env = (ShadowEngineEnviroment)environment;
            var se = new SerialisedEnvironment
            {
                ID = environment.ID,
                Name = environment.Name,
                Type = TypeName,
                Properties =
                {
                    {"BaseDirectory", env.BaseDirectory}
                }
            };

            return se;

        }

        public IEnvironment CreateEnvironment()
        {
            return new ShadowEngineEnviroment();
        }

        public IEnvironmentEditor CreateEditor()
        {
            return new ShadowEngineEnviromentEditor();
        }
    }
}
