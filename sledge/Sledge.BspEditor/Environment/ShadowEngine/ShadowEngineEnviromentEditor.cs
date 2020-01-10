using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Sledge.BspEditor.Environment.Goldsource;
using Sledge.Common.Translations;

namespace Sledge.BspEditor.Environment.ShadowEngine
{
    public partial class ShadowEngineEnviromentEditor : UserControl, IEnvironmentEditor
    {
        public event EventHandler EnvironmentChanged;
        public Control Control => this;

        public IEnvironment Environment
        {
            get => GetEnvironment();
            set => SetEnvironment(value as ShadowEngineEnviroment);
        }

        public ShadowEngineEnviromentEditor()
        {
            InitializeComponent();

           
        }

        public ShadowEngineEnviroment GetEnvironment()
        {
            return new ShadowEngineEnviroment()
            {
                BaseDirectory = txtGameDir.Text,
            };
        }

        private void SetEnvironment(ShadowEngineEnviroment value)
        {
            if (value == null) value = new ShadowEngineEnviroment();

            txtGameDir.Text = value.BaseDirectory;
        }

        public void Translate(ITranslationStringProvider strings)
        {
            CreateHandle();
            var prefix = GetType().FullName;

            grpDirectories.Text = strings.GetString(prefix, "Directories");
        }
    }
}
