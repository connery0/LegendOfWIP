#include "stdafx.h"
#include "Hero.h"

Hero::Hero(std::string TexturePath) :Entity(TexturePath)
{
	m_TextureHeight = m_Texture.GetHeight();
	m_CurrentFrame = f_Down_NoShield1;
}

void Hero::Draw()
{
	
	//set textclip on right area before calling the parent draw function
	//m_TextClip.left += 16;
	//m_TextClip.bottom -= m_TextureHeight;
	//m_HMirror = true;
	

	Entity::Draw();
	//utils::SetColor(Color4f(1, 0, 1, 1));
	//utils::DrawPoint(Pos, 5);
}

void Hero::Update(float elapsedSec, Level& currentLevel)
{
	int xOffset = 0;
	if (m_direction.x < 0) { xOffset = -8; }
	if (m_direction.x > 0) { xOffset = 8; }
	int yOffset = 0;
	if (m_direction.y < 0) { yOffset = -8; }
	if (m_direction.y > 0) { yOffset = 8; }
	
	//TODO: simply do +8 and -8 check in IsPassable?
	if (currentLevel.IsPassable(Pos.x +xOffset+elapsedSec * m_direction.x * m_speed, Pos.y-6)
		&&currentLevel.IsPassable(Pos.x + xOffset + elapsedSec * m_direction.x * m_speed, Pos.y+4)
		) {
		Pos.x += elapsedSec * m_direction.x * m_speed;
	}

	if (currentLevel.IsPassable(Pos.x-4, Pos.y+yOffset + elapsedSec*m_direction.y * m_speed)
		&& currentLevel.IsPassable(Pos.x+4, Pos.y + yOffset + elapsedSec*m_direction.y * m_speed)) {
		Pos.y += elapsedSec * m_direction.y * m_speed;
	}

	


	m_secCounter += elapsedSec;
	if (m_secCounter >= 1.0f / FPS) {
		m_secCounter = 0;
		++m_FrameCount;
	}

		//TODO: add other diretions and actions
		if (m_direction.x == 0 && m_direction.y == 0) {
			m_FrameCount = 0;
			m_CurrentFrame = f_Down_NoShield1;
		}
		else if(m_direction.x == 0 && m_direction.y < 0) {
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
/*
		if (m_FrameCount >= 2) { m_FrameCount = 0; }
		if (m_FrameCount == 0)m_CurrentFrame = f_Down_NoShield1;
		if (m_FrameCount == 1)m_CurrentFrame = f_Down_NoShield2;*/

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





