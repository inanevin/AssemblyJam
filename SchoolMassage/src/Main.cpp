#include "Application.hpp"
#include "Common/Common.hpp"

int main(int argc, char** argv)
{
    using namespace SM;

    g_config.decoratedWindow = true;
    g_config.resizableWindow = true;
    g_config.fullscreenWindow = false;
    g_config.windowWidth = 1440;
    g_config.windowHeight = 960;
    g_config.windowTitle = "School Massage";
    g_config.msaaSamples = 0;

    Application app;
    app.Run();
    
    return 0;
}