#include <iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Display.h"
#include"Splash.h"
#define endlch '\n'

int main()
{
    /*std::string name;
    std::cout << "Enter your name:";
    std::cin >> name;*/
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
