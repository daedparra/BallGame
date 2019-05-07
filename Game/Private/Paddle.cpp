#include "Paddle.h"

Paddle::Paddle(float x, float y, float x1, float y1)
{
	p1.x = x;
	p1.y = y;
	p2.x = x1;
	p2.y = y1;
}

Paddle::~Paddle()
{
}

void Paddle::setpFirstPaddleX(float x)
{
	p1.x = x;
}

void Paddle::setpSecondPaddleX(float x)
{
	p2.x = x;
}

void Paddle::setpFirstPaddleY(float y)
{
	p1.y = y;
}

void Paddle::setpSecondPaddleY(float y)
{
	p2.y = y;
}

float Paddle::getpFirstPaddleX()
{
	return p1.x;
}

float Paddle::getpSecondPaddleX()
{
	return p2.x;
}

float Paddle::getpFirstPaddleY()
{
	return p1.y;
}

float Paddle::getpSecondPaddleY()
{
	return p2.y;
}

exVector2 Paddle::getPaddleP1()
{
	return p1;
}
exVector2 Paddle::getPaddleP2()
{
	return p2;
}
