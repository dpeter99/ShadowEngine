using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Model
{
    public class Asset
    {
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
                    Asset c = new Asset(item, Type.Folder);
                    this.childs.Add(c);
                }


                var files = Directory.GetFiles(path);
                foreach (var item in files)
                {
                    Asset c = new Asset(item, Type.File);
                    this.childs.Add(c);
                }
            }
        }
    }
}
