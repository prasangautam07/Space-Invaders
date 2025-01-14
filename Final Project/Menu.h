#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Player.h"
#include "GameState.h"

namespace State
{
	class Menu : public GameState
	{
	public:
		 Menu(Application& application);
		~Menu();

		void input() override;
		void update(const float dt) override;
		void draw() override;

	private:
		unsigned maxStars;

		sf::Text m_menuText;

		Utils::RandomNumberGenerator rng;

		GameObjects::Player* m_p_player;
		GameObjects::Player2* m_p_player2;
		sf::Texture menu;


		sf::Clock animationClock;

		std::vector<sf::CircleShape> stars;

		void FillBackground();
		void ClearObjects();
	};
}