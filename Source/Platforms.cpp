#include "Platforms.h"
#include <ctime>

Platforms::Platforms()
{
	std::srand(std::time(nullptr));
	blocks.resize(0);
}

Platforms::~Platforms()
{

}

void Platforms::getNextBlock(ASGE::Renderer *renderer)
{
	size ++;
	blocks.resize(size-1);
	switch (int random_int = std::rand() % 2 + 1)
	{
		case 0:
		{

			break;
		}
		case 1:
		{
			current_height--;
			break;
		}
		case 2:
		{
			current_height++;
			break;
		}
	}

	blocks.push_back(createBlock(renderer));
	return;
}


ASGE::Sprite * Platforms::createBlock(ASGE::Renderer *renderer)
{
	ASGE::Sprite* temp;
	temp = renderer->createRawSprite();
	temp->xPos(1280);
	temp->yPos(current_height*96);

	if (!temp->loadTexture("..\\..\\Resources\\Textures\\Block.png"))
	{
		return nullptr;
	}
	return temp;
}

void Platforms::renderBlocks(ASGE::Renderer * renderer)
{
	for (int x = 0; x != size; x++)
	{
		if (!(blocks[x]->xPos() < -96))
		{
			renderer->renderSprite(*blocks[x]);
		}
	}
}

void Platforms::updateBlocks()
{
	for (int x = 0; x != size; x++)
	{
		blocks[x]->xPos(blocks[x]->xPos() - 1);
	}
}

int Platforms::getSize()
{
	return size;
}

int Platforms::getBlockX(int size)
{
	return blocks[size]->xPos();
}

int Platforms::getBlockY(int size)
{
	return blocks[size]->yPos();
}
