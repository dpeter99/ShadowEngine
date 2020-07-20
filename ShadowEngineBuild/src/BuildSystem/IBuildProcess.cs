using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowEngineBuild.src
{
    interface IBuildProcess
    {
        void ProcessResourceFile(string path);

        void FinishSteps();
    }
}
