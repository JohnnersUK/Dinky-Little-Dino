#pragma once
#include "animSprite.h"

class PlayerDino
{
public:
	PlayerDino() = default;
	~PlayerDino();

	bool init(ASGE::Renderer *renderer);

	void update();
	void render(ASGE::Renderer *renderer);

	void move();

private:
	AnimSprite running;
	ASGE::Sprite* actions[2];

	int xPos = 0;
	int yPos = 550;

	int xVel = 0;
	int yVel = 0;
};
