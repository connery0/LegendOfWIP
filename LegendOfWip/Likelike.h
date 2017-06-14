#pragma once
#include "Enemy.h"
class Likelike :
	public Enemy
{
public:
	Likelike();
	Likelike(float x, float y);
	Likelike(const Likelike& other);

protected:
	void Initialize();
	void Movement(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel) override;
	virtual void Animate(const float &elapsedSec)override;
	
};

