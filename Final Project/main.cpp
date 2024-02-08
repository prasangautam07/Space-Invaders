#include <iostream>
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Display.h"
#include"Splash.h"
#define endlch '\n'

int main()
{
    // Ensure that application resources will be freed when the user quits.
    {
        Application app;

        app.runGameLoop();
    }

#ifdef DEBUG_ON
    std::cout << "Press any key to exit" << endlch;
    std::cin.get();
#endif

    return 0;
}
