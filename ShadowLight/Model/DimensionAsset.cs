using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Model
{
    [ShadowLight.Model.AssetType(".sdf")]
    public class DimensionAsset :Asset
    {
        public DimensionAsset(string path, Type type) : base(path, type)
        {
        }
    }
}
