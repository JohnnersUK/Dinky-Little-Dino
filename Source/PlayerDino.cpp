#include "PlayerDino.h"
#include "Actions.h"
#include <string>

PlayerDino::~PlayerDino()
{

}

bool PlayerDino::init(ASGE::Renderer *renderer)
{
	std::string dir[6];
	dir[0] = ("..\\..\\Resources\\Textures\\Running1.png");
	dir[1] = ("..\\..\\Resources\\Textures\\Running2.png");
	dir[2] = ("..\\..\\Resources\\Textures\\Running3.png");
	dir[3] = ("..\\..\\Resources\\Textures\\Running4.png");
	dir[4] = ("..\\..\\Resources\\Textures\\Running5.png");
	dir[5] = ("..\\..\\Resources\\Textures\\Running6.png");
	running.init(renderer, 5, dir);

	return true;
}

void PlayerDino::update()
{
	if (yPos < 551)
	{
		yVel += 5;
	}

	yPos += yVel;
	xPos += xVel;

	if (yPos > 550)
	{
		yPos = 550;
		yVel = 0;
	}


	running.updatePosition(xPos, yPos);
	running.updateFrame();
}

void PlayerDino::render(ASGE::Renderer * renderer)
{
	running.renderSprite(renderer);
}

void PlayerDino::move()
{
	if (game_action == GameAction::JUMP)
	{
		yVel -= 40;
	}
	if (game_action == GameAction::LEFT)
	{
		if (xVel > -5)
		{
			xVel -= 5;
		}
	}
	if (game_action == GameAction::RIGHT)
	{
		if (xVel < 5)
		{
			xVel += 5;
		}
	}
	if (game_action == GameAction::STOP)
	{
		xVel = 0;
	}
}
