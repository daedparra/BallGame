#pragma once
#include "Engine/Public/EngineTypes.h"
#include "Paddle.h"

class Ball
{
public:
	Ball(exVector2 mPosition, exColor mColor, float mSpeed, Paddle* mPlayer1, Paddle* mPlayer2, exEngineInterface* mEngine);
	~Ball();

	// Getters
	float getRadius();
	exVector2 getCenter();

	int getPlayer1Score();
	int getPlayer2Score();
	void renderBall(float time, Paddle* Player1, Paddle* Player2);

	void resetBall();
	void render();


	// Setters
	void setRadius(float r);
	void setP1(exVector2 p1);
	
private:
	float radius = 10;

	float mSpeedX;
	float mSpeedY;

	exVector2			mBallCenter;
	exColor				mBallColor;
	exEngineInterface*	mEngine;

	Paddle*				mPlayer1;
	Paddle*				mPlayer2;

	int					mPlayer1Score;
	int					mPlayer2Score;
};

