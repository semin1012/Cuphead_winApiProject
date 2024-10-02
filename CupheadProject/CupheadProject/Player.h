#pragma once
#include <vector>
#include "framework.h"
using namespace std;
#define PLAYER_IDEL_SIZE 5

enum class EPlayerState
{
	Idle,
	Jump,
	Max
};

class Player
{
private:
	int		x;
	int		y;
	EPlayerState			state;
	vector<vector<CImage>> playerImg;

private:
	void CreateImage();
	void ParsingToImagePath(EPlayerState state, int spriteSize, TCHAR* path, int startNum);

public:
	Player();
	Player(int x, int y);
	~Player();
};

