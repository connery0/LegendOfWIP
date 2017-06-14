#pragma once
#include "Moblin_Red.h"
class Moblin_Blue : public Enemy
{
public:
	Moblin_Blue();
	Moblin_Blue(float x, float y);
	Moblin_Blue(const Moblin_Blue& other);
	//virtual void Update(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel)override;
protected:
	void Initialize();

	virtual void Movement(const float &elapsedSec, const std::unique_ptr<Room> &currentLevel) override;
	virtual void Animate(const float &elapsedSec) override;

	float MoveChangeTimer{ 0 };
};

