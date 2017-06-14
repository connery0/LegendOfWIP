#pragma once
#include "stdafx.h"
#include "Texture.h"
#include "Frame.h"
class Projectile
{
public:
	enum damageType {hero,enemy,all};

	Projectile( Point2f position,int damage);
	void Update(const float & elapsedSec);
	void const  Draw();
	Rectf GetHitRect();
	int GetDamage();
	bool isAttacking();
	
	void SetPos(Point2f pos);

	void SlashRight();
	void SetStatic();
	void SlashDown();
	void SlashLeft();
	void SlashUp();

private:
	int m_Damage;
	bool m_IsAttacking{ false };
	Point2f m_Pos;
	Rectf m_HitRect;
	
	const int m_fps{ 4 }; 
	float m_attackTime;

	const Rectf m_Shape{ -8,-8,16,16 };
	Frame m_CurrentFrame{ Point2f(0,0) };
	int m_Frame{ 0 };
	std::vector<Frame> animationFrames;
	Texture m_Sprites;
};

