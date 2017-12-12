#include "AnimSprite.h"

AnimSprite::AnimSprite()
{
}

AnimSprite::~AnimSprite()
{
}

bool AnimSprite::init(ASGE::Renderer *renderer, int frames, std::string asset_dir[])
{
	sprite_frames = new ASGE::Sprite*[frames];
	for (int x = 0; x < frames + 1; x++)
	{
		sprite_frames[x] = renderer->createRawSprite();
		if (!sprite_frames[x]->loadTexture(asset_dir[x].c_str()))
		{
			return false;
		}
	}
	return true;
}

void AnimSprite::update()
{
}
