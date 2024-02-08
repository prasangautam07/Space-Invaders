#include "TextureManager.h"

Utils::TextureManager::TextureManager()
{
	this->addResource(Shared::TextureId::TX_SPLASH_LOGO, "textures/logo1.png");
	this->addResource(Shared::TextureId::TX_PLAYER, "textures/ship.png");
	this->addResource(Shared::TextureId::TX_LASER, "textures/laser.png");
	//this->addResource(Shared::TextureId::TX_ENEMY, "textures/slime.png");
	this->addResource(Shared::TextureId::TX_ENEMY, "textures/asteroid2.png");
}