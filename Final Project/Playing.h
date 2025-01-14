#pragma once

#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "GameState.h"
#include<SFML/System/Clock.hpp>
#include"SFML/System/Time.hpp"

namespace State
{
	class Playing : public GameState
	{
	public:
		 Playing(Application& application);
		~Playing();

		void input() override;
		void update(const float dt) override;

		virtual int getremhp() { return remhp2; }


		void draw() override;

	private:
		unsigned maxStars;
		unsigned maxEnemy;
		unsigned currentEnemyLimit;
		float enemySpawnInterval;
		float enemySpawnIntervalMin;
		float difficultyIncreaseInterval;
		bool gameOver;

		sf::Clock gameTimeClock;
		sf::Time totalElapsedTime;
		sf::Time timeLimit;
		sf::Font m_uiFont;
		//sf::Time remainingTime;

		Utils::RandomNumberGenerator rng;

		sf::Clock enemySpawnClock;
		sf::Clock difficultyIncreaseClock;

		GameObjects::UI m_ui;
		GameObjects::Player* m_p_player;

		GameObjects::UI m_ui2;
		GameObjects::Player2* m_p_player2;
		int remhp2;

		std::vector<GameObjects::Enemy> enemies;
		std::vector<GameObjects::Enemy> enemyGCList;

		std::vector<sf::CircleShape> stars;

		void SpawnEnemy();
		void IncreaseDifficulty();
		void FillBackground();
		void HandleCombat();
		void ClearObjects();

		void displayTimeRemaining();
	};


}
