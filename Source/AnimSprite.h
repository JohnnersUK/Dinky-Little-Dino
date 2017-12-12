#pragma once
#include <Engine\Renderer.h>
#include <Engine\Sprite.h>

#include <string>

class AnimSprite
{
public:
	AnimSprite();
	~AnimSprite();

	bool init(ASGE::Renderer *renderer, int frames, std::string asset_dir[]);
	void update();

private:
	ASGE::Sprite** sprite_frames;
	int no_frames;
	int current_frame;


};