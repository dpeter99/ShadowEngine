using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Model
{
    public class Asset
    {
        public static Dictionary<string, System.Type> _assetTypeDictionary;
        public static Dictionary<string, System.Type> AssetTypeDictionary
        {
            get
            {
                if (_assetTypeDictionary == null)
                {
                    var typesWithMyAttribute =
                        // Note the AsParallel here, this will parallelize everything after.
                        from a in AppDomain.CurrentDomain.GetAssemblies().AsParallel()
                        from t in a.GetTypes()
                        let attributes = t.GetCustomAttributes(typeof(AssetTypeAttribute), true)
                        where attributes != null && attributes.Length > 0
                        select new { Type = t, Attribute = ((AssetTypeAttribute)attributes[0]) };
                    _assetTypeDictionary = typesWithMyAttribute.ToDictionary(a => a.Attribute.ext, a => a.Type);
                }

                return _assetTypeDictionary;

            }
        }

        public enum Type
        {
            Folder,
            File
        }

        public Type _Type;

        public string _path;
        public string _name;

        public List<Asset> childs;

        public Asset(string path, Type type)
        {
            this._Type = type;
            if (_Type == Type.Folder)
                this._name = Path.GetFileName(path);
            else
                this._name = Path.GetFileName(path);

            this._path = path;
            childs = new List<Asset>();

            if (type == Type.Folder)
            {
                var folders = Directory.GetDirectories(path);
                foreach (var item in folders)
                {
                    var owningFile = Directory.GetFiles(item).FirstOrDefault(a => Path.GetFileNameWithoutExtension(a) == Path.GetFileName(item));
                    if (owningFile != null)
                    {
                        var c = InstanciateCorrectAsset(item);
                        if (c == null)
                        {
                            c = new Asset(item, Type.Folder);
                            this.childs.Add(c);
                        }
                        else
                        {
                            this.childs.Add(c);
                        }
                    }
                    else
                    {
                        Asset c = new Asset(item, Type.Folder);
                        this.childs.Add(c);
                    }
                }


                var files = Directory.GetFiles(path);
                foreach (var item in files)
                {
                    if (Path.GetFileName(item) == _name)
                    {
                        var c = InstanciateCorrectAsset(item);
                        this.childs.Add(c);
                    }
                }
            }
        }

        Asset InstanciateCorrectAsset(string item)
        {
            string ext = Path.GetExtension(item);

            if (AssetTypeDictionary.ContainsKey(ext))
            {
                System.Type t = AssetTypeDictionary[ext];

                Asset c = Activator.CreateInstance(t, item, Type.File) as Asset;

                //Asset c = new Asset(item, Type.File);
                return c;
            }
            else
            {
                //TODO: no correct asset
                return null;
            }
        }
    }
}
