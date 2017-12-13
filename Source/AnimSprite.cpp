#include "AnimSprite.h"

AnimSprite::~AnimSprite()
{
	for (int x = 0; x < no_frames + 1; x++)
	{
		delete[] sprite_frames[x];
	}
}

bool AnimSprite::init(ASGE::Renderer *renderer, int frames, std::string asset_dir[])
{
	sprite_frames = new ASGE::Sprite*[frames];
	for (int x = 0; x < frames + 1; x++)
	{
		sprite_frames[x] = renderer->createRawSprite();
		sprite_frames[x]->xPos(0);
		sprite_frames[x]->yPos(550);
		if (!sprite_frames[x]->loadTexture(asset_dir[x].c_str()))
		{

		}
	}
	no_frames = frames;
	return true;
}

void AnimSprite::updateFrame()
{
	current_frame++;
	if (current_frame > no_frames)
	{
		current_frame = 0;
	}
}

void AnimSprite::updatePosition(int xPos, int yPos)
{
	for (int x = 0; x < no_frames + 1; x++)
	{
		sprite_frames[x]->xPos(xPos);
		sprite_frames[x]->yPos(yPos);
	}
}

void AnimSprite::renderSprite(ASGE::Renderer * renderer)
{
	renderer->renderSprite(*sprite_frames[current_frame]);
}
