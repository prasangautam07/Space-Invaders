#pragma once

namespace Shared
{
	//Resource identifiers
	enum class TextureId { TX_SPLASH_LOGO = 1, TX_PLAYER, TX_PLAYER2, TX_ENEMY, TX_LASER,TX_LASERBLUE };
	enum class FontId { F_UI = 1 };
	enum class SoundId { S_LASER = 1, S_PLAYER_DEATH, S_ENEMY_DEATH, S_GAME_MUSIC };

	constexpr float MASTER_VOLUME = 100.f;
	constexpr float MUSIC_VOLUME = (40.f * MASTER_VOLUME) / 100.f;
	constexpr float EFFECT_VOLUME = (60.f * MASTER_VOLUME) / 100.f;
}