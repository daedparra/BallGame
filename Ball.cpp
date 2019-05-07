#include "Game/Private/Ball.h"
#include "Engine/Public/EngineTypes.h"
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <string>
//Ball constructor 
Ball::Ball() {
	pBall.x = 400.0f;
	pBall.y = 300.0f;
	pOriginal.x = pBall.x;
	pOriginal.y = pBall.y;
	direction = STOP;
}

Ball::~Ball() {

}
//get ball as a vector
exVector2 Ball::getBall() {
	return pBall;
}
//get x pos in ball
float Ball::getpBallX() {
	return pBall.x;
}
//get y pos in ball
float Ball::getpBallY() {
	return pBall.y;
}
//get direction 
eDir Ball::getDirection() {
	return direction;
}
//get reset for the ball if a player hit a wall left or right
void Ball::Reset()
{
	pBall.x = pOriginal.x;
	pBall.y = pOriginal.y;

	direction = STOP;
}
//change new direction for ball
void Ball::randomDirection() {
	direction = (eDir)((rand() % 6) + 1);
}
//Set new direction 
void Ball::changeDirection(eDir d) {
	direction = d;
}
//Move ball depending on the new direction is set
void Ball::Move(float fDeltaT) {
	int speed = 2;
	//speed *= 4;
	switch (direction)
	{
	case STOP:
		break;
	case LEFT:
		pBall.x -= 200.0f *fDeltaT * speed;
		break;
	case RIGHT:
		pBall.x += 200.0f *fDeltaT * speed;
		break;
	case UPLEFT:
		pBall.x -= 200.0f *fDeltaT * speed;
		pBall.y -= 200.0f *fDeltaT * speed;
		break;
	case DOWNLEFT:
		pBall.x -= 200.0f *fDeltaT * speed;
		pBall.y += 200.0f *fDeltaT * speed;
		break;
	case UPRIGHT:
		pBall.x += 200.0f *fDeltaT * speed;
		pBall.y -= 200.0f *fDeltaT * speed;
		break;
	case DOWNRIGHT:
		pBall.x += 200.0f *fDeltaT * speed;
		pBall.y += 200.0f *fDeltaT * speed;
		break;
	default:
		break;
	}
}