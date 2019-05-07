
#include "World.h"
// the world, it contains all of our game objects and defines the order of updates
// create our paddle
GameObject* CreatePaddleLR(bool right)
{
	const float fPaddleWidth = 15.0f;
	const float fPaddleHeight = 100.0f;

	exVector2 velocity;
	exVector2 position;
	exVector2 normal;
	exColor c;
	c.mColor[0] = 255;
	c.mColor[1] = 255;
	c.mColor[2] = 255;
	c.mColor[3] = 255;

	if (!right)
	{
		position.x = 15.0f;
		position.y = kViewportHeight / 2;

		normal.x = 1;
		normal.y = 0;

	}
	else
	{
		position.x = kViewportWidth - 15.0f;
		position.y = kViewportHeight / 2;

		normal.x = -1;
		normal.y = 0;
	}

	GameObject* pPaddle = new GameObject();
	COGTransform* pTransform = new COGTransform(pPaddle,position);
	pPaddle->AddComponent(pTransform);
	COGInputManager* pInputManager = new COGInputManager(pPaddle, right);
	pPaddle->AddComponent(pInputManager);
	COGBoxShape* pBoxShape = new COGBoxShape(pPaddle, fPaddleWidth, fPaddleHeight,c);
	pPaddle->AddComponent(pBoxShape);

	velocity.x = 0;
	velocity.y = 0;
	

	COGPhysics* pPhysics = new COGPhysics(pPaddle, false,velocity,normal);
	pPaddle->AddComponent(pPhysics);

	pPaddle->Initialize();

	return pPaddle;
}

// create ball (notice how it will generate events)
GameObject* CreateBall()
{
	const float fBallRadius = 12.0f;

	GameObject* pBall = new GameObject();
	exVector2 position;
	position.x = 400.0f;
	position.y = 300.0f;
	COGTransform* pTransform = new COGTransform(pBall,position);
	
	pBall->AddComponent(pTransform);

	COGCircleShape* pBoxShape = new COGCircleShape(pBall, fBallRadius);
	pBall->AddComponent(pBoxShape);
	exVector2 velocity;
	velocity.x = 170;
	velocity.y = 170;
	exVector2 normal;
	normal.x = 0;
	normal.y = 0;
	COGPhysics* pPhysics = new COGPhysics(pBall, true, velocity, normal);
	
	pBall->AddComponent(pPhysics);

	COGBounce* pBounce = new COGBounce(pBall);
	pBall->AddComponent(pBounce);

	pBall->Initialize();

	return pBall;
}

GameObject* CreateWallTB(bool top) 
{
	const float wallWidth = kViewportWidth;
	const float wallHeight = 20.0f;
	exVector2 position;
	exVector2 velocity;
	velocity.x = 0;
	velocity.y = 0;
	exVector2 normal;
	exColor c;
	c.mColor[0] = 200;
	c.mColor[1] = 200;
	c.mColor[2] = 255;
	c.mColor[3] = 255;

	if (top) 
	{
		position.x = kViewportWidth / 2;
		position.y = -5;
		normal.x = 0;
		normal.y = 1;
	}
	else 
	{
		position.x = kViewportWidth / 2;
		position.y = kViewportHeight+5;
		normal.x = 0;
		normal.y = -1;
	}

	GameObject* pWall = new GameObject();
	COGTransform* pTransform = new COGTransform(pWall, position);
	pWall->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pWall, wallWidth, wallHeight,c);
	pWall->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pWall, false, velocity,normal);
	pWall->AddComponent(pPhysics);

	pWall->Initialize();

	return pWall;
}

GameObject* CreateWallLR(bool right,int thisFont)
{
	const float wallWidth = 20;
	const float wallHeight = kViewportHeight;
	exVector2 position;
	exVector2 velocity;
	velocity.x = 0;
	velocity.y = 0;
	exVector2 normal;
	exColor c;
	c.mColor[0] = 200;
	c.mColor[1] = 200;
	c.mColor[2] = 255;
	c.mColor[3] = 255;
	exVector2 ScorePosition;
	int score = 0;

	if (right)
	{
		position.x = kViewportWidth+10;
		position.y = kViewportHeight / 2;
		normal.x = -1;
		normal.y = 0;
		ScorePosition.x = (kViewportWidth / 4);
		ScorePosition.y = 25;
	}
	else
	{
		position.x = -11;
		position.y = kViewportHeight / 2;
		normal.x = 1;
		normal.y = 0;
		ScorePosition.x = (kViewportWidth * .65);
		ScorePosition.y = 25;
	}

	GameObject* pWall = new GameObject();
	COGTransform* pTransform = new COGTransform(pWall, position);
	pWall->AddComponent(pTransform);
	
	COGBoxShape* pBoxShape = new COGBoxShape(pWall, wallWidth, wallHeight,c);
	pWall->AddComponent(pBoxShape);

	c.mColor[0] = 255;
	c.mColor[1] = 255;
	c.mColor[2] = 255;
	c.mColor[3] = 255;
	COGScore* pScore = new COGScore(pWall, ScorePosition, thisFont, score, c, right);
	pWall->AddComponent(pScore);
	COGPhysics* pPhysics = new COGPhysics(pWall, false, velocity,normal);
	pWall->AddComponent(pPhysics);

	pWall->Initialize();

	return pWall;
}


	void World::Create(int thisFont)
	{
		mGameObjects.push_back(CreatePaddleLR(true));
		mGameObjects.push_back(CreatePaddleLR(false));
		mGameObjects.push_back(CreateWallTB(true));
		mGameObjects.push_back(CreateWallTB(false));
		mGameObjects.push_back(CreateWallLR(true,thisFont));
		mGameObjects.push_back(CreateWallLR(false,thisFont));
		mGameObjects.push_back(CreateBall());
		
	}

	void World::Destroy()
	{
		for (GameObject* pGameObject : mGameObjects)
		{
			delete pGameObject;
		}

		mGameObjects.clear();
	}

	void World::Update(float fDeltaT, exEngineInterface* mEngine, bool mUp, bool mDown, bool mW, bool mS)
	{
		// run simulation first
		for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
		{
			pPhysics->Update(fDeltaT);
		}

		for (COGInputManager* pInput : COGInputManager::mInputs)
		{
			pInput->MovementEventListener(mUp, mDown, mW, mS, fDeltaT);

		}

		// then render everything
		for (COGShape* pShape : COGShape::mShapeComponents)
		{
			pShape->Render(mEngine);
		}
	}
