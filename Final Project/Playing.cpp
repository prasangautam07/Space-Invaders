#include "Playing.h"
#include "GameOver.h"
#include "Application.h"
#include "Display.h"

State::Playing::Playing(Application& application) :
	GameState(application),
	maxStars(200),
	maxEnemy(50),
	currentEnemyLimit(6),
	enemySpawnInterval(3.f),
	enemySpawnIntervalMin(1.5f),
	difficultyIncreaseInterval(10.f),
	gameOver(false),
	m_ui(this->getFont(Shared::FontId::F_UI)),
	m_ui2(this->getFont(Shared::FontId::F_UI))

{
	//Create player
	this->m_p_player = new GameObjects::Player(this->getTexture(Shared::TextureId::TX_PLAYER), this->getResourceManager());
	this->m_p_player->SetPosition(sf::Vector2f(0.f, 50.f));

	//Create player2
	this->m_p_player2 = new GameObjects::Player2(this->getTexture(Shared::TextureId::TX_PLAYER), this->getResourceManager());
	this->m_p_player2->SetPosition(sf::Vector2f(0.f, 500.f));

	//Create background
	this->FillBackground();

	this->enemySpawnClock.restart();
	this->difficultyIncreaseClock.restart();

	//Start scene music
	this->m_sceneAudio.setBuffer(this->getAudio(Shared::SoundId::S_GAME_MUSIC));
	this->m_sceneAudio.setVolume(Shared::MUSIC_VOLUME);
	this->m_sceneAudio.setLoop(true);
	this->m_sceneAudio.play();
}

State::Playing::~Playing()
{
	delete this->m_p_player;

	delete this->m_p_player2;
}

void State::Playing::input()
{
	if (!this->gameOver)
		this->m_p_player->HandleInput(Display::getWindow().getSize());

	if (!this->gameOver)
		this->m_p_player2->HandleInput(Display::getWindow().getSize());
}

void State::Playing::update(const float dt)
{
	//Game over condition
	if (this->gameOver && this->m_p_player->isDestoryComplete() && this->m_p_player2->isDestoryComplete()) 
	{

		this->m_p_application->changeState(std::make_unique<GameOver>(*this->m_p_application, this->m_p_player->getScore(), this->m_p_player2->getScore()));
		return;
	}

	////Game over condition for player2
	//if (this->gameOver && this->m_p_player2->isDestoryComplete())
	//{
	//	this->m_p_application->changeState(std::make_unique<GameOver>(*this->m_p_application, this->m_p_player2->getScore()));
	//	return;
	//}

	//Update background objects
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		float x = this->rng.getFloat(0.f, 2.f);
		(*it).move(-1.f * x * dt * 60.f, 0.f);
	}

	//Update player
	if (!this->gameOver)
	{
		//Update ui
		this->m_ui.update(this->m_p_player->getScore(), this->m_p_player->getCurrentHp(), dt);

		//player2
		this->m_ui.update2(this->m_p_player2->getScore(), this->m_p_player2->getCurrentHp(), dt);

		//update player
		this->m_p_player->Update(dt, Display::getWindow().getSize());

		//player2
		this->m_p_player2->Update(dt, Display::getWindow().getSize());


		//Spawn an enemy every enemySpawnSeconds interval.
		if (this->enemySpawnClock.getElapsedTime().asSeconds() >= enemySpawnInterval && this->enemies.size() < this->currentEnemyLimit)
		{
			this->SpawnEnemy();
			this->enemySpawnClock.restart();
		}
	}

	//Enemy update cycle
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		(*it).Update(dt);
	}

	if (!this->gameOver)
	{
		//Handle combat
		this->HandleCombat();

		//Increase difficulty
		this->IncreaseDifficulty();
	}

	//Clear objects
	this->ClearObjects();
}

void State::Playing::draw()
{
	//Draw UI
	this->m_ui.draw();
	this->m_ui2.draw();

	//Draw background objects
	sf::RenderStates renderOptions(sf::BlendAlpha);
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		Display::getWindow().draw((*it), renderOptions);
	}

	this->m_p_player->Draw(Display::getWindow());

	//for player2
	this->m_p_player2->Draw(Display::getWindow());


	//Draw enemies
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		if (!(*it).isDestroyed())
			(*it).Draw(Display::getWindow());
	}
}

void State::Playing::SpawnEnemy()
{
	if (!this->gameOver)
	{
		float minX = static_cast<float>(Display::getWindow().getSize().x);
		float maxX = static_cast<float>(Display::getWindow().getSize().x) * 2.f;
		float maxY = static_cast<float>(Display::getWindow().getSize().y) - 110.f;

		float xPos = this->rng.getFloat(minX, maxX);
		float yPos = this->rng.getFloat(55.f, maxY);
		float speed = this->rng.getFloat(1.f, 5.f);

		this->enemies.emplace_back(
			&this->getTexture(Shared::TextureId::TX_ENEMY),
			&this->getResourceManager(),
			sf::Vector2f(xPos, yPos),
			speed);
	}
}

void State::Playing::IncreaseDifficulty()
{
	if (this->difficultyIncreaseClock.getElapsedTime().asSeconds() > this->difficultyIncreaseInterval)
	{
		if (this->currentEnemyLimit < this->maxEnemy)
			this->currentEnemyLimit++;

		if (this->enemySpawnInterval > this->enemySpawnIntervalMin)
			this->enemySpawnInterval -= 0.5f;

		this->difficultyIncreaseClock.restart();
	}
}


void State::Playing::FillBackground()
{
	float maxX = static_cast<float>(Display::getWindow().getSize().x);
	float maxY = static_cast<float>(Display::getWindow().getSize().y);

	for (unsigned i = this->stars.size(); i < this->maxStars; i++)
	{
		sf::CircleShape star(this->rng.getFloat(0.3f, 1.5f));
		star.setFillColor(sf::Color::White);

		star.setPosition(this->rng.getFloat(0.f, maxX), this->rng.getFloat(0.f, maxY));
		this->stars.push_back(star);
	}
}

void State::Playing::HandleCombat()
{
	if (this->m_p_player->getCurrentHp() <= 0)
	{
		this->m_p_player->Destroy();
		this->gameOver = true;
	}

	//for player2
	if (this->m_p_player2->getCurrentHp() <= 0)
	{
		this->m_p_player2->Destroy();
		this->gameOver = true;
	}

	//Player & enemy collision check
	auto playerBox = this->m_p_player->getBoundingBox();
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		auto enemyBox = (*it).getBoundingBox();
		if (enemyBox.intersects(playerBox) && (!(*it).isDestroying() || (*it).isDestroyed()))
		{
			this->m_p_player->TakeDamage((*it).getCurrentHp());
			(*it).TakeDamage((*it).getCurrentHp());
			break;
		}
	}

	//for player2
	auto playerBox2 = this->m_p_player2->getBoundingBox();
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		auto enemyBox = (*it).getBoundingBox();
		if (enemyBox.intersects(playerBox2) && (!(*it).isDestroying() || (*it).isDestroyed()))
		{
			this->m_p_player2->TakeDamage((*it).getCurrentHp());
			(*it).TakeDamage((*it).getCurrentHp());
			break;
		}
	}

	//Bullet & enemy collision check
	for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); ++enemy)
	{
		if (!(*enemy).isDestroying())
		{
			if (!this->m_p_player->getBullets().empty())
			{
				for (auto bullet = this->m_p_player->getBullets().begin(); bullet != this->m_p_player->getBullets().end(); ++bullet)
				{
					if ((*bullet).getBoundingBox().intersects(enemy->getBoundingBox()))
					{
						enemy->TakeDamage(this->m_p_player->getDamage());
						this->m_p_player->getBullets().erase(bullet);

						if (enemy->isDestroying() || enemy->isDestroyed())
							this->m_p_player->AddScore(5);

						break;
					}
				}
			}
		}
	}

	//for player2
	//Bullet & enemy collision check
	for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); ++enemy)
	{
		if (!(*enemy).isDestroying())
		{
			if (!this->m_p_player2->getBullets().empty())
			{
				for (auto bullet = this->m_p_player2->getBullets().begin(); bullet != this->m_p_player2->getBullets().end(); ++bullet)
				{
					if ((*bullet).getBoundingBox().intersects(enemy->getBoundingBox()))
					{
						enemy->TakeDamage(this->m_p_player2->getDamage());
						this->m_p_player2->getBullets().erase(bullet);

						if (enemy->isDestroying() || enemy->isDestroyed())
							this->m_p_player2->AddScore(5);

						break;
					}
				}
			}
		}
	}
}


void State::Playing::ClearObjects()
{
	//Player bullet GC
	if (!this->m_p_player->getBullets().empty())
	{
		for (auto bullet = this->m_p_player->getBullets().begin(); bullet != this->m_p_player->getBullets().end(); ++bullet)
		{
			if ((bullet->getPosition().x < 0 ||
				bullet->getPosition().y < 0 ||
				bullet->getPosition().x > Display::getWindow().getSize().x ||
				bullet->getPosition().y > Display::getWindow().getSize().y) || this->gameOver)
			{
				this->m_p_player->getBullets().erase(bullet);
				break;
			}
		}
	}

	//Player2 bullet GC
	if (!this->m_p_player2->getBullets().empty())
	{
		for (auto bullet = this->m_p_player2->getBullets().begin(); bullet != this->m_p_player2->getBullets().end(); ++bullet)
		{
			if ((bullet->getPosition().x < 0 ||
				bullet->getPosition().y < 0 ||
				bullet->getPosition().x > Display::getWindow().getSize().x ||
				bullet->getPosition().y > Display::getWindow().getSize().y) || this->gameOver)
			{
				this->m_p_player2->getBullets().erase(bullet);
				break;
			}
		}
	}

	//Enemy GC
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		if (it->getPosition().x < -100)
		{
			if (!it->isDestroyed())
			{
				//If player missed the enemy takes 1 damage
				this->m_p_player->TakeDamage(1);
				this->m_p_player2->TakeDamage(1);
			}

			std::swap(*it, this->enemies.back());
			this->enemies.pop_back();
			break;
		}
	}

	//Background objects GC
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		if ((*it).getPosition().x < -10.f)
		{
			this->stars.erase(it);
			this->FillBackground();
			break;
		}
	}
}
