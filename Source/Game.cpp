#include <Engine\GameTime.h>
#include <Engine\InputEvents.h>

#include "Game.h"
#include "GameFont.h"

#include "Actions.h"

EndlessGame::~EndlessGame()
{
	this->inputs->unregisterCallback(key_handler_id);

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}

	if (backdrop1)
	{
		delete backdrop1;
		backdrop1 = nullptr;
	}

	if (backdrop2)
	{
		delete backdrop2;
		backdrop2 = nullptr;
	}

}

bool EndlessGame::init()
{
	game_width = 1280;
	game_height = 720;

	if (!initAPI(ASGE::Renderer::WindowMode::WINDOWED))
	{
		return false;
	}

	renderer->setWindowTitle("Endless Runner");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
	toggleFPS();

	this->inputs->use_threads = false;
	this->inputs->addCallbackFnc(
		ASGE::EventType::E_KEY, &EndlessGame::keyHandler, this);

	backdrop1 = renderer->createRawSprite();
	backdrop1->xPos(0);
	backdrop1->yPos(0);

	if (!backdrop1->loadTexture("..\\..\\Resources\\Textures\\BG_Game.png"))
	{
		return false;
	}

	backdrop2 = renderer->createRawSprite();
	backdrop2->xPos(1280);
	backdrop2->yPos(0);

	if (!backdrop2->loadTexture("..\\..\\Resources\\Textures\\BG_Game.png"))
	{
		return false;
	}

	player.init(renderer.get());

	return true;
}

void EndlessGame::update(const ASGE::GameTime& us)
{
	player_count += us.delta_time.count() * 00.1;
	other_count += us.delta_time.count() * 00.1;
	if (player_count > 5)
	{
		player.update();
		player_count = 0;
	}
	if (other_count > 1)
	{
		updateBackdrop();
		other_count = 0;
	}
	processActions();
}

void EndlessGame::render(const ASGE::GameTime& us)
{
	renderer->renderSprite(*backdrop1);
	renderer->renderSprite(*backdrop2);
	player.render(renderer.get());
}

void EndlessGame::keyHandler(const ASGE::SharedEventData data)
{
	const ASGE::KeyEvent* key_event = 
		static_cast<const ASGE::KeyEvent*>(data.get());
	
	auto key = key_event->key;
	auto action = key_event->action;

	if (key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}

	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		if (key == ASGE::KEYS::KEY_UP)
		{
			game_action = GameAction::JUMP;
		}
		if (key == ASGE::KEYS::KEY_LEFT)
		{
			game_action = GameAction::LEFT;
		}
		if (key == ASGE::KEYS::KEY_RIGHT)
		{
			game_action = GameAction::RIGHT;
		}
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			game_action = GameAction::KICK;
		}
	}

	if (action == ASGE::KEYS::KEY_RELEASED)
	{
		if (key == ASGE::KEYS::KEY_LEFT || key == ASGE::KEYS::KEY_RIGHT)
		{
			game_action = GameAction::STOP;
		}
	}
}

void EndlessGame::processActions()
{
	player.move();
	game_action = GameAction::NONE;
}

void EndlessGame::updateBackdrop()
{
	backdrop1->xPos(backdrop1->xPos() - 1);
	backdrop2->xPos(backdrop2->xPos() - 1);

	if (backdrop1->xPos() == -1280)
	{
		backdrop1->xPos(1280);
	}
	if (backdrop2->xPos() == -1280)
	{
		backdrop2->xPos(1280);
	}
}

