#pragma once
#include "Entity.h"
#include "HeroFrames.h"
#include "Level.h"
class Hero :
	public Entity
{
public:
	enum direction{ left,right,up,down };
	enum State{standing, walking, pushing, attacking};

	Hero(std::string TexturePath);
	virtual void Draw() override;
	virtual	void Update(float elapsedSec,Level& currentLevel);

	void SetXSpeed(float xSpeed);
	void SetYSpeed(float ySpeed);
	void SetSpeed(float xSpeed, float ySpeed);

protected:
	Point2f m_direction{ 0.0f,0.0f };
	float m_TextureHeight;
	float m_secCounter{ 0 };
	float FPS = 4;

	//float m_speed{ 64 };
	float m_speed{ 32 };
};

