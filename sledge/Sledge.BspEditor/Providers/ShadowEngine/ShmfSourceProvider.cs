using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using Sledge.BspEditor.Environment;
using Sledge.BspEditor.Primitives;
using Sledge.BspEditor.Primitives.MapObjectData;
using Sledge.BspEditor.Primitives.MapObjects;
using Sledge.Common.Shell.Documents;

namespace Sledge.BspEditor.Providers.ShadowEngine
{
    [Export(typeof(IBspSourceProvider))]
    class ShmfSourceProvider: IBspSourceProvider
    {

        private static readonly IEnumerable<Type> SupportedTypes = new List<Type>
        {
            // Map Object types
            typeof(Solid),
            typeof(Entity),

            // Map Object Data types
            typeof(EntityData),
        };

        public IEnumerable<Type> SupportedDataTypes => SupportedTypes;

        public IEnumerable<FileExtensionInfo> SupportedFileExtensions { get; } = new[]
        {
            new FileExtensionInfo("Shadow Map Format", ".shmf"),
        };

        /// <summary>
        /// Load a map from a stream
        /// </summary>
        /// <param name="stream">The stream</param>
        /// <param name="environment">The environment to load the map into</param>
        /// <returns>Completion task for the map</returns>
        public Task<BspFileLoadResult> Load(Stream stream, IEnvironment environment)
        {
            return Task.Factory.StartNew(() =>
            {
                return LoadWorld(stream, environment);
            });


            


            return null;
        }

        private BspFileLoadResult LoadWorld(Stream stream, IEnvironment environment)
        {
            var top = ShadowLight.Services.ShadowFormatParser.LoadFile(stream);

            var scene = top.properties["Scene"];

            BspFileLoadResult result = new BspFileLoadResult();

            if (scene.properties["Type"].value == "3D")
            {

            }

            

            var solids = scene.properties["Solids"];

            foreach (var solid in solids.properties.Values)
            {
                List<Face> faces;
                int id = int.Parse(solid.properties["ID"].value);
                Solid s = new Solid(id);

                foreach (var face in solid.properties.Values)
                {
                    if (face.name.StartsWith("Face"))
                    {
                        Face f;
                        
                    }
                }

                faces.Add()
                
            }


            return result;
        }


        /// <summary>
        /// Save the map to a stream
        /// </summary>
        /// <param name="stream">The stream</param>
        /// <param name="map">The map to write</param>
        /// <returns>Completion task for the save</returns>
        public Task Save(Stream stream, Map map)
        {
            return Task.Factory.StartNew(() =>
            {
                using (var writer = new StreamWriter(stream, Encoding.ASCII, 1024, true))
                {
                    WriteWorld(writer, map.Root);
                }
            });
        }

        private string FormatVector3(Vector3 c)
        {
            return "x:" + c.X.ToString("0.000", CultureInfo.InvariantCulture) 
                 + "y:" + c.Y.ToString("0.000", CultureInfo.InvariantCulture)
                 + "z:" + c.Z.ToString("0.000", CultureInfo.InvariantCulture);
        }

        private void WriteFace(StreamWriter sw, Face face, int i)
        {
            // ( -128 64 64 ) ( -64 64 64 ) ( -64 0 64 ) AAATRIGGER [ 1 0 0 0 ] [ 0 -1 0 0 ] 0 1 1

            sw.WriteLine("\t\t\t Side{"+i+"}:{");
            sw.WriteLine("\t\t\t Points:{");
            

            var strings = face.Vertices.Take(4).Select(x => "\t\t\t\t Point:{ " + FormatVector3(x) + ", u:0,v:0}").ToList();

            sw.WriteLine("\t\t\t }");
            sw.WriteLine("\t\t\t }");

            sw.WriteLine(String.Join("\n", strings));
        }

        private void WriteSolid(StreamWriter sw, Solid solid)
        {
            sw.WriteLine("\t\t Solid:{");
            sw.WriteLine("\t\t ID: "+solid.ID);
            int i = 0;
            foreach (var face in solid.Faces)
            {
                
                WriteFace(sw, face,i);
                i++;
            }
            sw.WriteLine("\t\t }");
        }

        private void WriteWorld(StreamWriter writer, Root mapRoot)
        {
            var solids = new List<Solid>();
            CollectSolids(solids, mapRoot);

            writer.WriteLine("ShadowFormat_0_0_1");
            writer.WriteLine("Asset:{");
            writer.WriteLine("\t UID:00001,");
            writer.WriteLine("\t Type:Scene,");
            writer.WriteLine("}");

            writer.WriteLine("Scene:{");
            writer.WriteLine("\t Type: 3D,");
            writer.WriteLine("\t Solids:{");

            solids.ForEach(x => WriteSolid(writer, x));

            writer.WriteLine("\t }");
            writer.WriteLine("}");
        }

        private void CollectSolids(List<Solid> solids, IMapObject parent)
        {
            foreach (var obj in parent.Hierarchy.SelectMany(x => x.Decompose(SupportedTypes)))
            {
                if (obj is Solid s) solids.Add(s);
                else if (obj is Group) CollectSolids(solids, obj);
            }
        }
    }
}
