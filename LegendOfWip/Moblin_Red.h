#pragma once
#include "Enemy.h"
class Moblin_Red :
	public Enemy
{
public:
	Moblin_Red();
	Moblin_Red(float x, float y);
	Moblin_Red(const Moblin_Red& other);
	//virtual void Update(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel)override;

protected:
	void Initialize();
	virtual void Movement(const float &elapsedSec, const std::unique_ptr<Room> &currentLevel) override;
	virtual void Animate(const float &elapsedSec) override;

	float MoveChangeTimer{ 0 };
};

