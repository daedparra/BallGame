// ConsoleApplication10.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>     
#include <algorithm>
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Game/Private/Game.h"
#include "Engine/Public/EngineInterface.h"
//
// here's a very simple framework for a component based game object system
// it's all in one file so it's easier to share with you, but please split into a sensible file structure
//
// ideas on what to add next:
// * check the TODO's I left
// * you'll need add a COG to read in user input to adjust the velocity of the paddle
//

class GameObject;

// COGTransform - where we are in space
class COGTransform : public Component
{
public:

	COGTransform(GameObject* pGO, exVector2 position)
		: Component(pGO)
	{
		mPosition = position;
	}

	virtual ComponentType GetType() const { return ComponentType::Transform; }

	exVector2& GetPosition() { return mPosition; }
	void SetPosition(exVector2 newPosition) { mPosition = newPosition; }

private:
	 
	exVector2 mPosition;

};

// COGShape - our baseclass for shapes
class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

public:

	COGShape(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual void Initialize() override
	{
		AddToComponentVector(mShapeComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mShapeComponents);
	}

	virtual void Render(exEngineInterface* mEngine) = 0;

private:

	// TODO - add a color variable here!

};


// COGBoxShape - box
class COGBoxShape : public COGShape
{
public:

	COGBoxShape(GameObject* pGO, float fWidth, float fHeight, exColor c)
		: COGShape(pGO)
		, mWidth(fWidth)
		, mHeight(fHeight)
	{
		mColor = c;
	}

	virtual ComponentType GetType() const { return ComponentType::BoxShape; }

	virtual void Render(exEngineInterface* mEngine) override
	{
		COGTransform* pTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
		exVector2 myPosition = pTransform->GetPosition();

		exVector2 p1,p2;
		p1.x = myPosition.x + (mWidth * 0.5f);
		p1.y = myPosition.y + (mHeight * 0.5f);
		p2.x = myPosition.x - (mWidth * 0.5f);
		p2.y = myPosition.y - (mHeight * 0.5f);
		
		mEngine->DrawBox(p1, p2, mColor, 0);
	}

	float getWidth() { return mWidth; }
	float getHeight() { return mHeight; }
private:

	float mWidth;
	float mHeight;
	exColor mColor;

};

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape(GameObject* pGO, float fRadius)
		: COGShape(pGO)
		, mRadius(fRadius)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::CircleShape; }

	virtual void Render(exEngineInterface* mEngine) override
	{
		exColor c;
		c.mColor[0] = 255;
		c.mColor[1] = 255;
		c.mColor[2] = 255;
		c.mColor[3] = 255;

		exVector2 myPosition = mGO->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();
		

		mEngine->DrawCircle(myPosition, mRadius, c, 1);
	}
	float getRadius() { return mRadius; }
private:

	float mRadius;

};

// our interface that allows COGPhysics to talk to anyone
class COGPhysics;

class IPhysicsCollisionEvent
{
public:

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) = 0;

};

// COGPhysics - lets move around
class COGPhysics : public Component
{
public:

	static std::vector<COGPhysics*> mPhysicsComponents;

public:

	COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents,exVector2 velocity,exVector2 normal)
		: Component(pGO)
		, mGenerateCollisionEvents(bGenerateCollisionEvents)
	{
		mVelocity = velocity;
		mNormal = normal;
	}

	GameObject* GetGo() { return mGO; }
	exVector2 GetNormal() { return mNormal; }
	exVector2 GetVelocity() { return mVelocity; }
	void setVelocity(exVector2 velocity) 
	{
		mVelocity = velocity;
	}
	virtual ComponentType GetType() const { return ComponentType::Physics; }

	virtual void Initialize() override
	{
		mTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
		mBoxShape = mGO->FindComponent<COGBoxShape>(ComponentType::BoxShape);
		mCircleShape = mGO->FindComponent<COGCircleShape>(ComponentType::CircleShape);

		AddToComponentVector(mPhysicsComponents);
	}

	virtual void Destroy() override
	{
		RemoveFromComponentVector(mPhysicsComponents);
	}

	virtual void Update(float fDeltaT)
	{
		// integrate velocity
		exVector2& myPosition = mTransform->GetPosition();
		
		myPosition.x += mVelocity.x * fDeltaT;
		myPosition.y += mVelocity.y * fDeltaT;

		// check collisions
		if (mGenerateCollisionEvents)
		{
			for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
			{
				// do not collide with self
				if (pPhysicsOther == this)
				{
					continue;
				}

				// TODO - maybe have IsColliding produce a vector/struct that contains the normal and then pass that into OnCollision?
				const bool bResult = IsColliding(pPhysicsOther);

				if (bResult)
				{
					for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
					{
						pCollisionEventListener->OnCollision(this, pPhysicsOther);
					}
				}
			}
		}
	}

	bool IsColliding(COGPhysics* pOther)
	{
		exVector2 Circle = mGO->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();
		exVector2 Rectangle = pOther->GetGo()->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();
		
		float rectWidht = pOther->mBoxShape->getWidth();
		float rectHeight = pOther->mBoxShape->getHeight();
		float DeltaX = Circle.x - std::max(Rectangle.x, std::min(Circle.x, Rectangle.x + rectWidht));
		float Deltay = Circle.y - std::max(Rectangle.y, std::min(Circle.y, Rectangle.y + rectHeight));

		float halfWidth = rectWidht * 0.5f;
		float halfHeight = rectHeight * 0.5f;
		float radius = mCircleShape->getRadius();

		float leftEdgeX = Rectangle.x - halfWidth;
		float rightEdgeX = Rectangle.x + halfWidth;

		if (Circle.x + radius >= leftEdgeX && Circle.x - radius <= rightEdgeX)
		{
			float topEdgeY = Rectangle.y - halfHeight;
			float bottomEdgeY = Rectangle.y + halfHeight;

			if (Circle.y + radius >= topEdgeY && Circle.y - radius <= bottomEdgeY)
			{
				return true;
			}
		}

		return false;
	}

	void AddCollisionEventListener(IPhysicsCollisionEvent* pEvent)
	{
		mCollisionEventListeners.push_back(pEvent);
	}

private:

	COGTransform* mTransform;
	COGBoxShape* mBoxShape;
	COGCircleShape* mCircleShape;

	exVector2 mVelocity;
	exVector2 mNormal;
	bool mGenerateCollisionEvents;
	std::vector<IPhysicsCollisionEvent*> mCollisionEventListeners;

};


class COGScore : public COGShape {
public:
	COGScore(GameObject * pGO, exVector2 position, int font, int score, exColor color, bool flag) : COGShape(pGO)
	{
		mGo = pGO;
		mPosition = position;
		mFontID = font;
		mColor = color;
		mScore = score;
		mFlag = flag;
	}

	ComponentType GetType() const
	{
		return ComponentType::Score;
	}
	int GetScore() { return mScore; }
	void SetScore(int score) { mScore = score; }
	void Render(exEngineInterface* pEngine)
	{
		std::string score = std::to_string(mScore);

		if (!mFlag)
		{
			//score to the left
			pEngine->DrawText(mFontID, mPosition, score.c_str(), mColor, 0);
		}
		else
		{
			//Score to the right
			pEngine->DrawText(mFontID, mPosition, score.c_str(), mColor, 0);
		}
	}
private:
	int mFontID;
	bool mFlag;
	int mScore;
	GameObject* mGo;
	exVector2 mPosition;
	exColor mColor;
};


// COGBounce - where we make the ball bounce
class COGBounce : public Component, public IPhysicsCollisionEvent
{
public:

	COGBounce(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Bounce; }

	virtual void Initialize() override
	{
		COGPhysics* pPhysics = mGO->FindComponent<COGPhysics>(ComponentType::Physics);

		// add myself to the list of objects that are interested in collisions
		// COGPhysics is able to interface with us because we inherit from IPhysicsCollisionEvent
		pPhysics->AddCollisionEventListener(this);
	}


	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override
	{
		exVector2 position;
		position.x = 400.0f;
		position.y = 300.0f;
		exVector2 Square = pOther->GetNormal();
		exVector2 BallPosition = pMe->GetGo()->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();

		//if ball hits left wall
		if (Square.x == 1 && Square.y == 0 && BallPosition.x < 30.0f) {
			
			int score = pOther->GetGo()->FindComponent<COGScore>(ComponentType::Score)->GetScore();
			score++;
			pOther->GetGo()->FindComponent<COGScore>(ComponentType::Score)->SetScore(score);
			pMe->GetGo()->FindComponent<COGTransform>(ComponentType::Transform)->SetPosition(position);
		}
		//if ball hits right wall
		if (Square.x == -1 && Square.y == 0 && BallPosition.x > 770.0f) {
			int score = pOther->GetGo()->FindComponent<COGScore>(ComponentType::Score)->GetScore();
			score++;
			pOther->GetGo()->FindComponent<COGScore>(ComponentType::Score)->SetScore(score);
			pMe->GetGo()->FindComponent<COGTransform>(ComponentType::Transform)->SetPosition(position);
		}
		float dotproduct = Square.x * pMe->GetVelocity().x + Square.y * pMe->GetVelocity().y;
		Square.x *= 2;
		Square.x *= dotproduct;
		Square.y *= 2;
		Square.y *= dotproduct;
  		Square.x =  pMe->GetVelocity().x - Square.x;
		Square.y =  pMe->GetVelocity().y - Square.y ;
		Square.x += 5;
		Square.y += 5;
		pMe->setVelocity(Square);
	}
	
};

class COGInputManager : public Component {
public:
	static std::vector<COGInputManager*> mInputs;
	COGInputManager(GameObject * mPointer, bool flag) : Component(mPointer)
	{
		mObject = mPointer;
		thisFlag = flag;
	}

	ComponentType GetType() const
	{
		return ComponentType::InputManager;
	}

	void Initialize()
	{
		AddToComponentVector(mInputs);
	}

	void MovementEventListener(bool mUp, bool mDown, bool mP2Up, bool mP2Down, float time)
	{
		exVector2& position = mObject->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();
		COGPhysics* pMe = mObject->FindComponent<COGPhysics>(ComponentType::Physics);

		if (!thisFlag)
		{
			if (mP2Up && position.x != 0)
			{
				if (position.y <= 60) {
					position.y = 60;
				}
				position.y -= 10.0f;
			}
			else if (mP2Down)
			{
				if (position.y >= kViewportHeight - 60) {
					position.y = kViewportHeight - 60;
				}
				position.y += 10.0f;
			}
		}
		else
		{
			if (mUp)
			{
				if (position.y <= 60) {
					position.y = 60;
				}
				position.y -= 10.0f;
			}
			else if (mDown)
			{
				if (position.y >= kViewportHeight - 60) {
					position.y = kViewportHeight - 60;
				}
				position.y += 10.0f;
			}
		}
	}
private:

	GameObject* mObject;
	bool thisFlag;
};


