#pragma once
#include "animSprite.h"
#include "Platforms.h"

class PlayerDino
{
public:
	PlayerDino() = default;
	~PlayerDino();

	bool init(ASGE::Renderer *renderer);

	bool update(Platforms platform);
	void render(ASGE::Renderer *renderer);

	void move();

	int getPlayerX();
	int getPlayerY();

	void setPlayerY(int new_yPos);
	void setPlayerYVel(int new_yVel);

	void reset();


private:
	bool collisionCheck(Platforms platform);

	AnimSprite running;
	ASGE::Sprite* actions[2];

	int xPos = 0;
	int yPos = 550;

	int xVel = 0;
	int yVel = 0;
	
	bool jumped = false;
};
