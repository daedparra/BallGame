#pragma once
#include "Engine/Public/EngineTypes.h"


class Ball
{
public:

	Ball();
	virtual						~Ball();
	virtual void				Reset();
	virtual void				changeDirection(eDir d);
	virtual void				randomDirection();
	virtual void				Move(float fDeltaT);
	virtual float				getpBallX();
	virtual float				getpBallY();
	virtual eDir				getDirection();
	virtual exVector2			getBall();

private:
	eDir						direction;
	exVector2					pBall, pOriginal;
};
