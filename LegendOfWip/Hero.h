#pragma once
#include "Entity.h"
#include "HeroFrames.h"
#include "Room.h"
class Hero :
	public Entity
{
public:
	enum direction{ left,right,up,down };
	enum State{standing, walking, pushing, attacking};

	Hero();
	virtual void Draw(const Color4f&  overlayColor = Color4f(1,1,1, 1)) const override;
	void Update(const float & elapsedSec,const std::unique_ptr<Room> &currentLevel) override;

	void Animate(const float & elapsedSec);

	void SetXSpeed(float xSpeed);
	void SetYSpeed(float ySpeed);
	void SetSpeed(float xSpeed, float ySpeed);
	int MaxHealth();

	Point2f GetDirection();

	//float m_speed{ 64 };
};

