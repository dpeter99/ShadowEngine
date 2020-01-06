using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ShadowLight.Model;
using Stylet;

namespace ShadowLight.Controls.AssetBrowser
{
    public class AssetViewModel
    {
        private Asset _asset { get; set; }

        public List<AssetViewModel> Assets
        {
            get
            {
                var list = new List<AssetViewModel>();
                foreach (var asset in _asset.childs)
                {
                    list.Add(new AssetViewModel(asset));
                }

                return list;
            }
        }

        public Asset.Type type
        {
            get { return _asset._Type; }
        }

        public string name
        {
            get { return _asset._name; }
        }

        public AssetViewModel(Asset asset)
        {
            _asset = asset;
        }

        public AssetViewModel()
        {
            
        }
    }
}
