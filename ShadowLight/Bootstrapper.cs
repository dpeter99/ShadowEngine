using System;
using System.Reflection;
using Stylet;
using StyletIoC;
using ShadowLight.Pages;

namespace ShadowLight
{
    public class Bootstrapper : Bootstrapper<ShellViewModel>
    {
        protected override void ConfigureIoC(IStyletIoCBuilder builder)
        {
            // Configure the IoC container in here
        }

        protected override void Configure()
        {
            // Perform any other configuration before the application starts
            var viewManager = this.Container.Get<ViewManager>();
            viewManager.NamespaceTransformations.Add("Pages","Controls");
            viewManager.ViewAssemblies.Add(Assembly.GetAssembly(typeof(ShadowLight.Controls.MenuBar.MenuBarView)));
        }
    }
}
