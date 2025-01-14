#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include"Playing.h"

namespace State
{
	class GameOver : public GameState
	{
	public:
	 GameOver(Application& application, int playerScore,int player2Score);
		~GameOver();

		void input() override;
		void update(const float dt) override;
		void draw() override;

	private:
		int m_playerScore;

		sf::Text m_gameOverText;
		sf::Text m_playerScoreText;
		sf::Text m_newGameText;
		sf::Text highScore;

		int m_player2Score;

		sf::Text m_player2ScoreText;

	};
  
}
