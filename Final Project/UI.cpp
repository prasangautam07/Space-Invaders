#include "UI.h"
#include "Display.h"

GameObjects::UI::UI(sf::Font const& uiFont) :
	m_uiFont(uiFont)
{
	this->m_scoreDisplay.setFont(this->m_uiFont);
	this->m_scoreDisplay.setFillColor(sf::Color::Red);
	this->m_scoreDisplay.setCharacterSize(35);
	this->m_scoreDisplay.setPosition(5.f, 5.f);

	this->m_score2Display.setFont(this->m_uiFont);
	this->m_score2Display.setFillColor(sf::Color::Blue);
	this->m_score2Display.setCharacterSize(35);
	this->m_score2Display.setPosition(1650.f, 5.f);

	m_timeDisplay.setFont(m_uiFont);
	m_timeDisplay.setFillColor(sf::Color::White);
	m_timeDisplay.setCharacterSize(45);
	m_timeDisplay.setPosition(800.f, 60.f);
}

GameObjects::UI::~UI()
{
}

void GameObjects::UI::update(int playerScore, int playerHp,sf::Time remainingTime, const float dt)
{
	//	std::string uiString("PLAYER1:\nHP: " + std::to_string(playerHp) + "    SCORE: " + std::to_string(playerScore));

	std::string uiString("PLAYER1:\nSCORE: " + std::to_string(playerScore));
	this->m_scoreDisplay.setString(uiString);
}
void GameObjects::UI::update2(int player2Score, int player2Hp, sf::Time remainingTime, const float dt)
{
	std::string uiString("PLAYER2:\nSCORE: " + std::to_string(player2Score));
	this->m_score2Display.setString(uiString);
	time = 180;
	int remainingSeconds = time-static_cast<int>(remainingTime.asSeconds());

	int minutes = remainingSeconds / 60;
	int seconds = remainingSeconds % 60;

	std::string timeString("Remaining Time: " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s");
	m_timeDisplay.setString(timeString);
}

void GameObjects::UI::draw() const
{
	Display::getWindow().draw(this->m_scoreDisplay);
	Display::getWindow().draw(this->m_score2Display);
	Display::getWindow().draw(m_timeDisplay);


}
