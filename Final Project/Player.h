#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <queue>
#include "Shared.h"
#include "Random.h"
#include "Resources.h"
#include "Bullet.h"

namespace GameObjects
{
	class Player
	{
	public:
		explicit Player(sf::Texture const& texture, Utils::Resources const& resourceManager);
		~Player();

		void HandleInput(sf::Vector2u const& windowBounds);
		void Update(float const& dt, sf::Vector2u const& windowBounds);
		void Draw(sf::RenderTarget& target);
		void TakeDamage(int amount);
		void Destroy();



		//Accessors
		std::deque<Bullet>& getBullets() { return this->m_bullets; }
		sf::Vector2f const& getPosition() const { return this->m_sprite.getPosition(); }
		sf::FloatRect getBoundingBox() const { return this->m_sprite.getGlobalBounds(); }
		std::string getHpAsString() const { return std::to_string(this->hp); }
		int getScore() const { return this->score; }
		int getCurrentHp() const { return this->hp; }
		int getTotalHp() const { return this->hpMax; }
		int getDamage() { return this->rng.getInt(this->damageMin, this->damageMax); }

		//Returns true if player explosion sound is NOT playing.
		bool isDestoryComplete() const { return this->m_playerDeathSound.getStatus() == sf::Sound::Stopped; }

		//Modifiers
		void SetPosition(sf::Vector2f const& position) { this->m_sprite.setPosition(position); }
		void AddScore(int modifier) { this->score += modifier; }

	private:

		int hp;
		int hpMax;

		int level;


		int damageMin;
		int damageMax;

		double exp;
		double expNext;

		int score;
		float shootTimerMax, shootTimer;

		float scaleX, scaleY;
		float dt;

		sf::Vector2f currentVelocity;
		sf::Vector2f direction;
		float maxVelocity;
		float acceleration;
		float stabilizerForce;

		Utils::RandomNumberGenerator rng;
		Utils::Resources const& m_resources;

		sf::Sprite m_sprite;
		sf::RectangleShape m_healthBar;
		sf::Texture const& m_texture;
		sf::Sound m_playerDeathSound;

		std::deque<Bullet> m_bullets;
		std::queue<sf::Sound> m_bulletSounds;

		void SpawnBullet();
	};




	// Second Player Class
	class Player2
	{
	public:
		explicit Player2(sf::Texture const& texture, Utils::Resources const& resourceManager);
		~Player2();

		void HandleInput(sf::Vector2u const& windowBounds);
		void Update(float const& dt, sf::Vector2u const& windowBounds);
		void Draw(sf::RenderTarget& target);
		void TakeDamage(int amount);
		void Destroy();

		//Accessors
		std::deque<Bullet>& getBullets() { return this->m_bullets; }
		sf::Vector2f const& getPosition() const { return this->m_sprite2.getPosition(); }
		sf::FloatRect getBoundingBox() const { return this->m_sprite2.getGlobalBounds(); }
		std::string getHpAsString() const { return std::to_string(this->hp2); }
		int getScore() const { return this->score2; }
		int getCurrentHp() const { return this->hp2; }
		int getTotalHp() const { return this->hpMax2; }
		int getDamage() { return this->rng.getInt(this->damageMin2, this->damageMax2); }

		//Returns true if player explosion sound is NOT playing.
		bool isDestoryComplete() const { return this->m_player2DeathSound.getStatus() == sf::Sound::Stopped; }

		//Modifiers
		void SetPosition(sf::Vector2f const& position) { this->m_sprite2.setPosition(position); }
		void AddScore(int modifier) { this->score2 += modifier; }

	private:
		int hp2;
		int hpMax2;

		int level2;

		int damageMin2;
		int damageMax2;

		double exp2;
		double expNext2;

		int score2;
		float shootTimerMax2, shootTimer2;

		float scaleX2, scaleY2;
		float dt;

		sf::Vector2f currentVelocity2;
		sf::Vector2f direction2;
		float maxVelocity2;
		float acceleration2;
		float stabilizerForce2;

		Utils::RandomNumberGenerator rng;
		Utils::Resources const& m_resources2;

		sf::Sprite m_sprite2;
		sf::RectangleShape m_healthBar2;
		sf::Texture const& m_texture2;
		sf::Sound m_player2DeathSound;

		std::deque<Bullet> m_bullets;
		std::queue<sf::Sound> m_bulletSounds;

		void SpawnBullet();
	};
}

