
#include <Application.hpp>
#include <stdexcept>
#include <iostream>

int main()
{
    try
    {
        Application app;
        app.Init();
        app.Run();
    }
    catch(std::exception& e)
    {
        std::cout << "/nEXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
