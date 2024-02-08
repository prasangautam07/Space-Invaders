#include "Enemy.h"

GameObjects::Enemy::Enemy(sf::Texture const* texture, Utils::Resources const* resourceManager, sf::Vector2f position, float speed) :
	hp(50),
	maxHp(50),
	dmgMin(1),
	dmgMax(2),
	speed(speed),
	exploding(false),
	direction(sf::Vector2f(-1.f, 0.f)),
	m_p_Texture(texture),
	m_resourceManager(resourceManager)
{
	this->m_sprite.setTexture(*this->m_p_Texture);
	this->m_sprite.setScale(0.4f, 0.4f);
	this->m_sprite.setPosition(position);

	this->m_healthBar.setSize(sf::Vector2f(50.f * 1.5f, 2.f));
	this->m_healthBar.setFillColor(sf::Color::Red);

	this->m_enemyDestorySound.setBuffer(this->m_resourceManager->audio.getResource(Shared::SoundId::S_ENEMY_DEATH));
	this->m_enemyDestorySound.setVolume(Shared::EFFECT_VOLUME);
	this->m_enemyDestorySound.setLoop(false);

	this->initAnimationFrames();
}

GameObjects::Enemy::~Enemy()
{
}

void GameObjects::Enemy::Update(float const& dt)
{
	auto animationFrame = this->exploding ?
		this->m_deathAnimation.getFrame() :
		this->m_moveAnimation.getFrame();

	this->m_sprite.setTextureRect(animationFrame);

	sf::Vector2f pos(this->direction.x * this->speed * dt * 60.f, this->direction.y * this->speed * dt * 60.f);
	this->m_sprite.move(pos);

	this->m_healthBar.setPosition(this->m_sprite.getPosition().x, this->m_sprite.getPosition().y + 15.f);
}

void GameObjects::Enemy::Draw(sf::RenderTarget& target) const
{
	target.draw(this->m_healthBar);
	target.draw(this->m_sprite);
}

void GameObjects::Enemy::TakeDamage(int amount)
{
	if (this->exploding) return;

	this->hp -= amount;

	if (this->hp < 0)
		this->hp = 0;

	float hpPercent = std::max<float>(0.f, (static_cast<float>(this->hp) / static_cast<float>(this->maxHp)) * this->m_sprite.getGlobalBounds().width);
	this->m_healthBar.setSize(sf::Vector2f(hpPercent, 2.f));

	if (this->hp == 0)
		this->Explode();
}

void GameObjects::Enemy::Explode()
{
	this->m_enemyDestorySound.play();
	this->exploding = true;
}

void GameObjects::Enemy::initAnimationFrames()
{
	
	// Move animation forward
	this->m_moveAnimation.addFrame(sf::IntRect(0, 0, 577, 433), 0.f); // Frame 1
	this->m_moveAnimation.addFrame(sf::IntRect(577, 0, 577, 433), 0.f); // Frame 2
	this->m_moveAnimation.addFrame(sf::IntRect(1154, 0, 577, 433), 0.f); // Frame 3
	this->m_moveAnimation.addFrame(sf::IntRect(1731, 0, 577, 433), 0.f); // Frame 4
	this->m_moveAnimation.addFrame(sf::IntRect(2308, 0, 577, 433), 0.f); // Frame 5

	// Move animation backward
	this->m_moveAnimation.addFrame(sf::IntRect(1731, 0, 577, 433), 0.f); // Frame 6
	this->m_moveAnimation.addFrame(sf::IntRect(1154, 0, 577, 433), 0.f); // Frame 7
	this->m_moveAnimation.addFrame(sf::IntRect(577, 0, 577, 433), 0.f); // Frame 8

	// Death animation
	this->m_deathAnimation.addFrame(sf::IntRect(0, 0, 0, 0), 0.f); // Frame 9
}


