using Stylet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadowLight.Events
{
    class ProjectLoadedEvent : PropertyChangedBase
    {
        private string _project;
        public string Project
        {
            get { return this._project; }
            set { SetAndNotify(ref this._project, value); }
        }
    }
}
