#pragma once

#include "Engine/Public/EngineTypes.h"
#include "Engine/Public/EngineInterface.h"

class Paddle
{
public:
	Paddle(exVector2 leftPlayer, exVector2 rightPlayer, exColor paddleColor, int playerId, exEngineInterface* pEngine);
	~Paddle();

	// Moving the Paddle
	void movePaddle(bool up, bool down, float time);
	void renderPaddle(exEngineInterface* pEngine);
	
	float getmPaddleLeftVecY();
	float getmPaddleRightVecY();

	float getmPaddleLeftVecX();
	float getmPaddleRightVecX();

	// Getters
	exVector2 getP1();
	exVector2 getP2();
	
	// Setters
	void setP1(exVector2 p1);
	void setP2(exVector2 p2);
private:
	// Hold the default values for the paddle
	exEngineInterface* pEngine;
	exVector2  p1;
	exVector2  p2;
	exColor c;

	int playerId;
	
	float paddleSpeed = 400;
};

