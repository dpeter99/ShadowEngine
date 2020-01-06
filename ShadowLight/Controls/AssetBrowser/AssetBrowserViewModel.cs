using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ShadowLight.Model;
using Stylet;

namespace ShadowLight.Controls.AssetBrowser
{
    public class AssetBrowserViewModel: Screen
    {
        private AssetHierarchy assetHierarchy;

        public List<AssetViewModel> AssetsList
        {
            get
            {
                return new List<AssetViewModel>()
                {
                    new AssetViewModel(assetHierarchy.AssetsFolder)
                };
            } 
        }

        public AssetBrowserViewModel(Project p)
        {
            assetHierarchy = p.AssetHierarchy;
            //OnPropertyChanged(nameof(AssetsList));
        }

        public AssetBrowserViewModel()
        {
            
        }
    }
}
