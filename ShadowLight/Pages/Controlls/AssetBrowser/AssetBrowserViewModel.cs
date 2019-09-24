using ShadowLight.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Pages.Controlls
{
    public class AssetBrowserViewModel
    {
        ApplicationState state;

        AssetHierarchy m_assetHierarchy
        {
            get
            {
                if(state.acticeProject == null)
                {
                    return null;
                }
                else
                {
                    return state.acticeProject.AssetHierarchy;
                }
            }
        }

        public List<AssetHierachyItem> Assets { get; set; }

        public bool hasProject
        {
            get => m_assetHierarchy == null;
        }



        public AssetBrowserViewModel(ApplicationState app)
        {
            state = app;

            Assets = new List<AssetHierachyItem>();
        }
    }
}
