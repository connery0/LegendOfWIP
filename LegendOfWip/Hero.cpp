#include "stdafx.h"
#include "Hero.h"

static const std::string HeroSpriteSheet{ "Recources/Images/LinkCleaned.png" };


Hero::Hero() :Entity(HeroSpriteSheet)
{
	m_CurrentFrame = f_Down_NoShield1;

}

void  Hero::Draw(const Color4f&  overlayColor)const
{
	Entity::Draw();
}

void Hero::Update(const float & elapsedSec,const std::unique_ptr<Room> &currentLevel)
{
	Entity::Update(elapsedSec);
	Entity::Movement(elapsedSec, currentLevel);
	Animate(elapsedSec);
}


void Hero::Animate(const float & elapsedSec) {
	//TODO: add other diretions and actions
	if (m_direction.x == 0 && m_direction.y == 0) {
		m_FrameCount = 0;
		m_CurrentFrame = f_Down_NoShield1;
	}
	else if (m_direction.x == 0 && m_direction.y < 0) {
		if (m_FrameCount >= 2) { m_FrameCount = 0; }
		if (m_FrameCount == 0)m_CurrentFrame = f_Down_NoShield1;
		if (m_FrameCount == 1)m_CurrentFrame = f_Down_NoShield2;
	}
	else if (m_direction.x == 0 && m_direction.y > 0) {
		if (m_FrameCount >= 2) { m_FrameCount = 0; }
		if (m_FrameCount == 0)m_CurrentFrame = f_Up_NoShield1;
		if (m_FrameCount == 1)m_CurrentFrame = f_Up_NoShield2;
	}
	else if (m_direction.x < 0) {
		if (m_FrameCount >= 2) { m_FrameCount = 0; }
		if (m_FrameCount == 0)m_CurrentFrame = f_Left_NoShield1;
		if (m_FrameCount == 1)m_CurrentFrame = f_Left_NoShield2;
	}
	else if (m_direction.x > 0) {
		if (m_FrameCount >= 2) { m_FrameCount = 0; }
		if (m_FrameCount == 0)m_CurrentFrame = f_Right_NoShield1;
		if (m_FrameCount == 1)m_CurrentFrame = f_Right_NoShield2;
	}
}


void Hero::SetXSpeed(float xSpeed)
{
	m_direction.x = xSpeed;
}

void Hero::SetYSpeed(float ySpeed)
{
	m_direction.y = ySpeed;
}

void Hero::SetSpeed(float xSpeed, float ySpeed)
{
	m_direction= Point2f(xSpeed,ySpeed);
}

int Hero::MaxHealth()
{
	return m_MaxHealth;
}


Point2f Hero::GetDirection()
{
	return m_direction;
}




