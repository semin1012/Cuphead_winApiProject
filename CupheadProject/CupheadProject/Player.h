#pragma once
#include <vector>
#include "framework.h"
using namespace std;

enum class EPlayerState
{
	Idle,
	Jump,
	Max
};

class Player
{
	int		x;
	int		y;
	EPlayerState			state;
	vector<vector<CImage*>> playerImg;

public:
	Player();
	Player(int x, int y);
	~Player();
};

