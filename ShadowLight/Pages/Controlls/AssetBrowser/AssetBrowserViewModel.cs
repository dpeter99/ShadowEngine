using ShadowLight.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using Stylet;

namespace ShadowLight.Pages.Controlls
{
    public class AssetBrowserViewModel : Screen
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

        List<AssetHierachyItem> _assets;
        public List<AssetHierachyItem> Assets {
            get
            {
                return _assets;
            } 

            private set
            {

            }
        }

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
