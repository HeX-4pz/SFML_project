#include <iostream>
#include "Application.h"

int main()
{
    try
    {
        Application app;
        app.Run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    

    return 0;
}
