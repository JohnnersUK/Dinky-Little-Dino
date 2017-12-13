#include "PlayerDino.h"
#include "Actions.h"
#include <string>

PlayerDino::~PlayerDino()
{
	if (actions[0])
	{
		delete actions[0];
	}
}

bool PlayerDino::init(ASGE::Renderer *renderer)
{
	yPos = 550;
	std::string dir[6];
	dir[0] = ("..\\..\\Resources\\Textures\\Running1.png");
	dir[1] = ("..\\..\\Resources\\Textures\\Running2.png");
	dir[2] = ("..\\..\\Resources\\Textures\\Running3.png");
	dir[3] = ("..\\..\\Resources\\Textures\\Running4.png");
	dir[4] = ("..\\..\\Resources\\Textures\\Running5.png");
	dir[5] = ("..\\..\\Resources\\Textures\\Running6.png");
	running.init(renderer, 5, dir);

	actions[0] = renderer->createRawSprite();
	actions[0]->yPos(550);
	if (!actions[0]->loadTexture("..\\..\\Resources\\Textures\\Idle.png"))
	{

	}

	return true;
}

bool PlayerDino::update(Platforms platform)
{
	if (yPos < 550)
	{
		yVel += 5;
	}

	yPos += yVel;
	xPos += xVel;

	if (yPos > 550)
	{
		yPos = 550;
		yVel = 0;
		jumped = false;
	}
	if (collisionCheck(platform))
	{
		return true;
	}

	running.updatePosition(xPos, yPos);
	running.updateFrame();

	return false;
}

void PlayerDino::render(ASGE::Renderer * renderer)
{
	if (game_action == GameAction::DEFAULT)
	{
		renderer->renderSprite(*actions[0]);
	}
	else if (game_action != GameAction::DEFAULT)
	{
		running.renderSprite(renderer);
	}
}

void PlayerDino::move()
{
	if (game_action == GameAction::JUMP)
	{
		if (!jumped)
		{
			yVel -= 40;
			jumped = true;
		}
		game_action = GameAction::NONE;
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

bool PlayerDino::collisionCheck(Platforms platform)
{
	for (int x = 0; x != platform.getSize(); x++)
	{
		if ((xPos + 16) < (platform.getBlockX(x) + 96) && (xPos + 80) > platform.getBlockX(x))
		{
			if (yPos > platform.getBlockY(x))
			{
				return true;
			}
			if (yPos + 75 > platform.getBlockY(x))
			{
				yPos = platform.getBlockY(x) - 75;
				yVel = 0;
				jumped = false;
			}
		}
	}

	return false;
}

int PlayerDino::getPlayerX()
{
	return xPos;
}

int PlayerDino::getPlayerY()
{
	return yPos;
}

void PlayerDino::setPlayerY(int new_yPos)
{
	yPos = new_yPos;
}

void PlayerDino::setPlayerYVel(int new_yVel)
{
	yVel = new_yVel;
}

void PlayerDino::reset()
{
	yPos = 550;
	xPos = 0;
	running.reset();
}

