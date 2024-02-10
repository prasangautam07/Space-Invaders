#pragma once
#include <SFML/Graphics.hpp>

namespace GameObjects
{
	class UI
	{
	public:
		explicit UI(sf::Font const& uiFont);
		~UI();

		void update(int playerScore, int playerHp, const float dt);
		void update2(int player2Score, int player2Hp, const float dt);

		void draw() const;
		void draw2() const;

	private:
		sf::Font m_uiFont;
		sf::Text m_scoreDisplay;
		sf::Text m_score2Display;
	};
}