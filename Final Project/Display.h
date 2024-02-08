#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#define DEBUG_ON

namespace Display
{
	void init();
	void clear();
	void display();

	void checkWindowEvents();

	bool isOpen();

	sf::RenderWindow& getWindow();

	const std::string TITLE = "Space Invaders";

#ifdef DEBUG_ON
	constexpr int WIDTH = 1900;
	constexpr int HEIGHT = 1080;
#endif
}
