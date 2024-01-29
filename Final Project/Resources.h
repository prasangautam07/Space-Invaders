#pragma once
#include "TextureManager.h"
#include "FontManager.h"
#include "SoundManager.h"

namespace Utils
{
	struct Resources
	{
		TextureManager textures;
		FontManager fonts;
		SoundManager audio;
	};
}
