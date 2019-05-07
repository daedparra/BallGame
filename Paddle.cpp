#include "Paddle.h"

#include "Engine/Public/EngineInterface.h"

Paddle::Paddle(exVector2 leftPlayer, exVector2 rightPlayer, exColor paddleColor, int playerId, exEngineInterface* pEngine)
{

	// Constructing both paddles for player one and two;
	this->p1 = leftPlayer;
	this->p2 = rightPlayer;
	this->c = paddleColor;
	this->playerId = playerId;
	this->pEngine = pEngine;

}

Paddle::~Paddle()
{

}

// Handle the movement of the Paddle
void Paddle::movePaddle(bool up, bool down, float time)
{

	if (up && getmPaddleLeftVecY() > 5 || up && getmPaddleLeftVecY() > 5)
	{
		p1.y -= paddleSpeed * time;
		p2.y -= paddleSpeed * time;
	}
	else if (down && getmPaddleRightVecY() < (kViewportHeight - 5) || down && getmPaddleRightVecY() < (kViewportHeight - 5))
	{
		p1.y += paddleSpeed * time;
		p2.y += paddleSpeed * time;
	}


}

void Paddle::renderPaddle(exEngineInterface* pEngine)
{
	pEngine->DrawBox(p1, p2, c, 0);
}

float Paddle::getmPaddleLeftVecY()
{
	return p1.y;
}

float Paddle::getmPaddleRightVecY()
{
	return p1.y;
}

float Paddle::getmPaddleLeftVecX()
{
	return p1.x;
}

float Paddle::getmPaddleRightVecX()
{
	return p2.y;
}


// Getters
exVector2 Paddle::getP1() {
	return p1;
}

exVector2 Paddle::getP2() {
	return p2;
}

// Setters
void Paddle::setP1(exVector2 p1) {
	this->p1 = p1;
}

void Paddle::setP2(exVector2 p2) {
	this->p2 = p2;
}