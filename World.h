#include "GameObject.h"
#include "Engine/Public/EngineInterface.h"
#include "GameObjectComponents.h"
// the world, it contains all of our game objects and defines the order of updates
class World
{
public:

	virtual void Create(int thisFont);

	virtual void Destroy();

	virtual void Update(float fDeltaT, exEngineInterface* mEngine, bool mUp, bool mDown, bool mW, bool mS);

private:

	std::vector<GameObject*> mGameObjects;
	

};