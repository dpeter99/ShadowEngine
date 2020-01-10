using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sledge.Providers.GameData
{
    [Export("SHa", typeof(IGameDataProvider))]
    class SHSceneProvider : IGameDataProvider
    {
        public DataStructures.GameData.GameData GetGameDataFromFiles(IEnumerable<string> files)
        {
            throw new NotImplementedException();
        }

        public bool IsValidForFile(string filename)
        {
            throw new NotImplementedException();
        }
    }
}
