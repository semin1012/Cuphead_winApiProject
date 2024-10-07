#include "FadeEffect.h"

FadeEffect::FadeEffect()
{
	image.Load(L"../Resource/Image/Background/Loading.png");
	lastTime = clock();
	alpha = 0;
	isOut = true;
	bEnd = false;
}

FadeEffect::~FadeEffect()
{
}

void FadeEffect::Draw(HDC& hdc)
{
	if (bEnd == true)
		return;

	if (isOut)
	{
		alpha += 10;
		if (alpha >= 255)
		{
			alpha = 255;
			isOut = false;
		}
	}
	else
	{
		alpha -= 10;
		if (alpha <= 0)
		{
			alpha = 0;
			bEnd = true;
		}
	}

	image.AlphaBlend(hdc, 0, 0, alpha);
}

bool FadeEffect::GetIsFadeIn()
{
	return !isOut;
}

bool FadeEffect::GetIsEnd()
{
	return bEnd;
}
