//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"
#include "World.h"
//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Davids Pong";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine(nullptr)
	, mFontID(-1)
	, mUp(false)
	, mDown(false)
	, mP2Up(false)
	, mP2Down(false)
	, score1(0)
	,score2(0)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;
	//Initialize the Ball and the two paddles on a certain position
	ball = new Ball();
	player1 = new Paddle(0.0f,100.0f,20.0f,200.0f);
	player2 = new Paddle(779.0f,100.0f,799.0f,200.0f);
	mFontID = mEngine->LoadFont( "Old School Adventures.ttf", 80);

	mTextPosition.x = 250.0f;
	mTextPosition.y = 10.0f;
	mTextPositionP2.x = 450.0f;
	mTextPositionP2.y = 10.0f;

	//set inicial scores
	score1 = 0;
	score2 = 0;
	world = new World();
	world->Create(mFontID);

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	mUp = pState[SDL_SCANCODE_W];
	mDown = pState[SDL_SCANCODE_S];
	mP2Up = pState[SDL_SCANCODE_UP];
	mP2Down = pState[SDL_SCANCODE_DOWN];
	
}

//-----------------------------------------------------------------

//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	exVector2 lineP, lineP1;
	exColor c;

	//middle line
	lineP.x = 400.0f;
	lineP.y = 0.0f;
	lineP1.x = 401.0f;
	lineP1.y = 600.0f;
	c.mColor[0] = 255;
	c.mColor[1] = 255;
	c.mColor[2] = 255;
	c.mColor[3] = 255;
	mEngine->DrawBox(lineP, lineP1, c, 0);
	
	//ball movement
	



	world->Update(fDeltaT, mEngine, mP2Up, mP2Down, mUp, mDown);


	//score player1
	std::string score1text = "";
	score1text = std::to_string(score1);
	//mEngine->DrawText( mFontID, mTextPosition,score1text.c_str(), c, 0 );
	//score player2
	std::string score2text = "";
	score2text = std::to_string(score2);
	//mEngine->DrawText(mFontID, mTextPositionP2, score2text.c_str(), c, 0);

}

