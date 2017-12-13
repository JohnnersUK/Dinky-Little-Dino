#pragma once
#include <Engine\Renderer.h>
#include <Engine\Sprite.h>

#include <string>

class AnimSprite
{
public:
	AnimSprite() = default;
	~AnimSprite();

	bool init(ASGE::Renderer *renderer, int frames, std::string asset_dir[]);

	void updateFrame();
	void updatePosition(int xPos, int yPos);

	void renderSprite(ASGE::Renderer *renderer);

	void reset();

private:
	ASGE::Sprite** sprite_frames;
	int no_frames;
	int current_frame = 0;
};