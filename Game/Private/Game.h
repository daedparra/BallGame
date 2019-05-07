//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//
#pragma once
#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Ball.h"
#include "Paddle.h"
class World;
//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

private:

	

	exEngineInterface*			mEngine;

	int							mFontID;
	int							score1, score2;

	bool						mUp;
	bool						mDown;
	bool						mP2Up;
	bool						mP2Down;

	exVector2					mTextPosition, mTextPositionP2;
	//Pointers from paddle class
	Paddle*						player1;
	Paddle*						player2;
	//Pointer from ball class
	Ball*						ball;
	int							ai;
	//world
	World*						world;
};
