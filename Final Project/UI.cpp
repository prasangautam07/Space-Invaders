#include "UI.h"
#include "Display.h"

GameObjects::UI::UI(sf::Font const& uiFont) :
	m_uiFont(uiFont)
{
	this->m_scoreDisplay.setFont(this->m_uiFont);
	this->m_scoreDisplay.setFillColor(sf::Color::Red);
	this->m_scoreDisplay.setCharacterSize(25);
	this->m_scoreDisplay.setPosition(5.f, 5.f);

	this->m_score2Display.setFont(this->m_uiFont);
	this->m_score2Display.setFillColor(sf::Color::Blue);
	this->m_score2Display.setCharacterSize(25);
	this->m_score2Display.setPosition(1700.f, 5.f);
}

GameObjects::UI::~UI()
{
}

void GameObjects::UI::update(int playerScore, int playerHp, const float dt)
{
	std::string uiString("PLAYER1:\nHP: " + std::to_string(playerHp) + "    SCORE: " + std::to_string(playerScore));
	this->m_scoreDisplay.setString(uiString);
}
void GameObjects::UI::update2(int player2Score, int player2Hp, const float dt)
{
	std::string uiString("PLAYER2:\nHP: " + std::to_string(player2Hp) + "    SCORE: " + std::to_string(player2Score));
	this->m_score2Display.setString(uiString);
}

void GameObjects::UI::draw() const
{
	Display::getWindow().draw(this->m_scoreDisplay);
	Display::getWindow().draw(this->m_score2Display);

}
//void GameObjects::UI::draw2() const
//{
//	Display::getWindow().draw(this->m_score2Display);
//
//}
