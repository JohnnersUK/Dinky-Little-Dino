#include <Engine\GameTime.h>
#include <Engine\InputEvents.h>

#include "Game.h"
#include "GameFont.h"

EndlessGame::~EndlessGame()
{
	this->inputs->unregisterCallback(key_handler_id);

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
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

	return true;
}

void EndlessGame::update(const ASGE::GameTime& us)
{

}

void EndlessGame::render(const ASGE::GameTime& us)
{

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
}

