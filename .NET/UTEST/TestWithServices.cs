using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Microsoft.Testing.Platform.Configurations;
using System;
using System.Collections.Generic;
using System.Text;

namespace KUBC.DAYZ.ITEMS;

public abstract class TestWithServices : TestWithConfig
{
    /// <summary>
    /// Провайдер сервисов
    /// </summary>
    public IServiceProvider ServiceProvider;

    /// <summary>
    /// Инициализируем сервисы теста
    /// </summary>
    public TestWithServices()
    {
        var services = new ServiceCollection();
        services.AddLogging((builder) =>
        {
            var output = TestContext.Current.TestOutputHelper;
            Assert.NotNull(output);
            builder.AddXUnit(output, options =>
            {
                options.TimestampFormat = "HH:mm:ss.fffffff";
            });
            builder.AddConfiguration(Configuration.GetSection("Logging"));
        });
        AddTestServices(services);
        ServiceProvider = services.BuildServiceProvider();
    }
    /// <summary>
    /// Добавляем сервисы теста
    /// </summary>
    /// <param name="services"></param>
    protected virtual void AddTestServices(ServiceCollection services) { }

    public virtual DirectoryInfo SampleDirectory => new DirectoryInfo("Sample");
}
