#include "Player.h"

Player::Player()
{
}

Player::Player(int x, int y)
{
}

Player::~Player()
{
	for (auto it = playerImg.begin(); it != playerImg.end(); it++)
	{
		for (auto img : *it)
		{
			delete (*img);
		}
	}

	playerImg.clear();
}
