#include "GameOver.h"
#include "Menu.h"
#include "Application.h"
#include "Display.h"

State::GameOver::GameOver(Application& application, int playerScore,int player2Score) :
	GameState(application),
	m_playerScore(playerScore),
	m_player2Score(player2Score)
{
	this->m_gameOverText.setFont(this->getFont(Shared::FontId::F_UI));
	this->m_gameOverText.setFillColor(sf::Color::Red);
	this->m_gameOverText.setCharacterSize(30);
	this->m_gameOverText.setString("GAME OVER!");

	this->m_playerScoreText.setFont(this->getFont(Shared::FontId::F_UI));
	this->m_playerScoreText.setFillColor(sf::Color::White);
	this->m_playerScoreText.setCharacterSize(30);
	this->m_playerScoreText.setString("PLAYER1 SCORE: " + std::to_string(playerScore));

	//player2 score display
	this->m_player2ScoreText.setFont(this->getFont(Shared::FontId::F_UI));
	this->m_player2ScoreText.setFillColor(sf::Color::White);
	this->m_player2ScoreText.setCharacterSize(30);
	this->m_player2ScoreText.setString("\nPLAYER2 SCORE: " + std::to_string(player2Score));


	if (player2Score > playerScore) {
		this->highScore.setFont(this->getFont(Shared::FontId::F_UI));
		this->highScore.setFillColor(sf::Color::Blue);
		this->highScore.setCharacterSize(25);
		this->highScore.setString("      PLAYER 2 WINS");

	}
	if (playerScore > player2Score) {
		this->highScore.setFont(this->getFont(Shared::FontId::F_UI));
		this->highScore.setFillColor(sf::Color::Red);
		this->highScore.setCharacterSize(25);
		this->highScore.setString("      PLAYER 1 WINS");
	}

	this->m_newGameText.setFont(this->getFont(Shared::FontId::F_UI));
	this->m_newGameText.setFillColor(sf::Color::Red);
	this->m_newGameText.setCharacterSize(25);
	this->m_newGameText.setString("Press 'N' to start new game");
}

State::GameOver::~GameOver()
{
}

void State::GameOver::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
	{
		this->m_p_application->changeState(std::make_unique<Menu>(*this->m_p_application));
	}
}

void State::GameOver::update(const float dt)
{
	float centerH = Display::getWindow().getSize().x / 2.f;

	this->m_gameOverText.setPosition(centerH - this->m_gameOverText.getGlobalBounds().width / 2, Display::getWindow().getSize().y / 2.f - 100.f);



	this->m_playerScoreText.setPosition(centerH - this->m_playerScoreText.getGlobalBounds().width / 2, this->m_gameOverText.getGlobalBounds().top + this->m_gameOverText.getGlobalBounds().height + 5.f);
	//player2
	this->m_player2ScoreText.setPosition(centerH - this->m_player2ScoreText.getGlobalBounds().width / 2, this->m_gameOverText.getGlobalBounds().top + this->m_gameOverText.getGlobalBounds().height + 10.f);
	
	this->m_newGameText.setPosition(centerH - this->m_newGameText.getGlobalBounds().width / 2, this->m_playerScoreText.getGlobalBounds().top + this->m_playerScoreText.getGlobalBounds().height + 20.f);
	this->highScore.setPosition(centerH - this->m_newGameText.getGlobalBounds().width / 2, this->m_playerScoreText.getGlobalBounds().top + this->m_playerScoreText.getGlobalBounds().height + 50.f);

	//player2
	this->m_newGameText.setPosition(centerH - this->m_newGameText.getGlobalBounds().width / 2, this->m_player2ScoreText.getGlobalBounds().top + this->m_player2ScoreText.getGlobalBounds().height + 45.f);


}

void State::GameOver::draw()
{
	Display::getWindow().draw(this->m_gameOverText);
	Display::getWindow().draw(this->m_playerScoreText);

	//displaying player2score
	Display::getWindow().draw(this->m_player2ScoreText);

	Display::getWindow().draw(this->highScore);

	Display::getWindow().draw(this->m_newGameText);
}
