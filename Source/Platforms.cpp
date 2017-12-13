#include "Platforms.h"
#include <ctime>

Platforms::Platforms()
{
	std::srand(std::time(nullptr));
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
		case 1:
		{
			if (current_height > 3.5)
			{
				current_height--;
			}
			break;
		}
		case 2:
		{
			if (current_height < 6.5)
			{
				current_height++;
			}
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
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

void Platforms::reset()
{
	for (int x = 0; x < size; x++)
	{
		delete blocks[x];
	}
	blocks.clear();
	size = 0;
	current_height = 6.5;
	blocks.resize(size);
	std::srand(std::time(nullptr));
}
