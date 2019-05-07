#pragma once
#include "Engine/Public/EngineTypes.h"

class Paddle
{
public:

	Paddle(float x, float y, float x1, float y1);
	virtual						~Paddle();
	virtual void				setpFirstPaddleX(float x);
	virtual void				setpSecondPaddleX(float x);
	virtual void				setpFirstPaddleY(float y);
	virtual void				setpSecondPaddleY(float y);
	virtual float				getpFirstPaddleX();
	virtual float				getpSecondPaddleX();
	virtual float				getpFirstPaddleY();
	virtual float				getpSecondPaddleY();
	virtual exVector2			getPaddleP1();
	virtual exVector2			getPaddleP2();

private:
	exVector2					p1, p2;
};
