using System;
using Stylet;
using StyletIoC;
using ShadowLight.Pages;
using ShadowLight.Model;

namespace ShadowLight
{
    public class Bootstrapper : Bootstrapper<ShellViewModel>
    {
        protected override void ConfigureIoC(IStyletIoCBuilder builder)
        {
            // Configure the IoC container in here
            builder.Bind<ApplicationState>().ToInstance(new ApplicationState());
        }

        protected override void Configure()
        {
            // Perform any other configuration before the application starts
        }
    }
}
