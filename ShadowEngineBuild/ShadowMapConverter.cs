using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ShadowEngineBuild
{
    public static class ShadowMapConverter
    {
        public static bool ConvertMaps()
        {
            Console.WriteLine("Converting Map Files");

            string path = BuildEnviroment.GetMapsFolder();

            var files = System.IO.Directory.GetFiles(path, "*.tmx",
                SearchOption.AllDirectories);

            foreach (var item in files)
            {
                ConvertMap(item);
            }

            return true;
        }

        static bool ConvertMap(string name)
        {
            Console.WriteLine("Converting map:\t"+ name);

            var importMap = new TiledSharp.TmxMap(name);

            ShadowFileElement map = new ShadowFileElement();
            map.isBlock = true;
            map.name = "ASDASD";
            
            map.AddProperty("Width",importMap.Width.ToString());
            map.AddProperty("Height", importMap.Height.ToString());

            map.AddProperty("TileWidth", importMap.TileWidth.ToString());
            map.AddProperty("TileHeight", importMap.TileHeight.ToString());

            ShadowFileElement layers = new ShadowFileElement();
            layers.name = "Layers";
            layers.isBlock = true;

            foreach (var layer in importMap.Layers)
            {
                ShadowFileElement layerElement = new ShadowFileElement();
                layerElement.isBlock = true;

                layerElement.name = layer.Name;
                layerElement.AddProperty("Visible", layer.Visible.ToString());

                string data = "";
                for (int i = 0; i < layer.Tiles.Count; i++)
                {
                    data += layer.Tiles[i].Gid;
                    if (i != layer.Tiles.Count-1) data += ".";
                }

                layerElement.AddProperty("map",data);

                layers.AddProperty(layerElement);
            }

            map.AddProperty(layers);


            string destFile = name;
            destFile = destFile.Replace(".tmx", ".sef");
            destFile = destFile.Replace(oldValue:".tmx", newValue:".sef");

            ShadowFileFormat.WriteFile(map,destFile);

            return true;
        }
    }
}
