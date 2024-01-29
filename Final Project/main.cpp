//#include <iostream>
//#include<SFML/Graphics.hpp>
//#include <glew.h>
//#include "Display.h"
//#include "Application.h"
//
//#define endlch '\n'
//
//int main()
//{
//	//Ensure that application resources will be freed when user quits.
//	{
//		Application app;
//
//		glewInit();
//		if (glewIsSupported("GL_VERSION_4_5"))
//		{
//			std::cout << "OpenGL 4.5 Active" << endlch;
//		}
//
//		app.runGameLoop();
//	}
//
//
//#ifdef DEBUG_ON
//	std::cout << "Press any key to exit" << endlch;
//	std::cin.get();
//#endif
//
//	return 0;
//}
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Display.h"

#define endlch '\n'

int main()
{
    // Ensure that application resources will be freed when the user quits.
    {
        Application app;

        //sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

        // SFML handles the OpenGL context internally, so no need for GLEW.

        app.runGameLoop();
    }

#ifdef DEBUG_ON
    std::cout << "Press any key to exit" << endlch;
    std::cin.get();
#endif

    return 0;
}
