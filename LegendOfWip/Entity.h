#pragma once
#include "stdafx.h"
#include "Texture.h"
#include "Frame.h"
#include <memory>

class Room;

class Entity
{
public:
	Entity(std::string TexturePath);
	Entity(const Entity & other);
	void Update(float elapsedSec, const std::unique_ptr<Room>& currentLevel){};
	virtual void Update(const float& elapsedSec);
	virtual void Update(const float& elapsedSec, const std::unique_ptr<Room>& currentLevel);
	virtual void Draw(const Color4f& overlayColor = Color4f(1,1,1,1))const;
	Point2f GetPos();
	void SetPos(float x, float y);
	int GetHealth();
	virtual void ChangeHealth(int healthChange);
	void SetHealth(int newHealth);

protected:

	virtual void Movement(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel);


	Point2f Pos{ 0,0 };
	Point2f m_direction{ 0.0f,0.0f };
	std::shared_ptr<Texture> m_Texture;
	bool m_VMirror{ false };
	bool m_HMirror{ false };
	Frame m_CurrentFrame{ Point2f(0,0) };
	int m_FrameCount{ 0 };
	//Default sprite size
	Rectf m_Shape{ -8,-8,16,16 };
	float m_speed{ 32 };
	float m_secCounter{ 0 };
	float FPS = 4;
	int m_health{ 5 };

	int m_MaxHealth{ 10 };

};

