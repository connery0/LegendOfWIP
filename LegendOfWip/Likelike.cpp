#include "stdafx.h"
#include "Likelike.h"
#include "MonsterFrames_Likelike.h"
#include "Room.h"

Likelike::Likelike() :Enemy()
{
	Initialize();
}

Likelike::Likelike(float x, float y) : Enemy(x,y)
{
	Initialize();
}

void Likelike::Initialize() {
	m_FrameCount = rand() % 2;
	FPS = 2;
	m_speed = 16;
}

Likelike::Likelike(const Likelike & other) : Enemy(other)
{
}

void Likelike::Movement(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel) {
	if (m_direction.x == 0 && m_direction.y == 0) {
		m_direction.x = float(rand() % 3 - 1);
		m_direction.y = float(rand() % 3 - 1);
	}
	
	int xOffset = 0;
	if (m_direction.x < 0) { xOffset = -8; }
	if (m_direction.x > 0) { xOffset = 8; }
	int yOffset = 0;
	if (m_direction.y < 0) { yOffset = -8; }
	if (m_direction.y > 0) { yOffset = 8; }


	if (currentLevel->IsOutOfBounds(Pos)) {
		m_direction.x = -m_direction.x;
		m_direction.y = -m_direction.y;
		Pos.x += elapsedSec * m_direction.x * m_speed;
		Pos.y += elapsedSec * m_direction.y * m_speed;
	}
	else {
		if (currentLevel->IsPassable(Pos.x + xOffset + elapsedSec * m_direction.x * m_speed, Pos.y - 6)
			&& currentLevel->IsPassable(Pos.x + xOffset + elapsedSec * m_direction.x * m_speed, Pos.y + 4)
			) {
			Pos.x += elapsedSec * m_direction.x * m_speed;
		}
		else {
			m_direction.x = -m_direction.x;
			m_direction.y = float(rand() % 3 - 1);
		}

		if (currentLevel->IsPassable(Pos.x - 4, Pos.y + yOffset + elapsedSec*m_direction.y * m_speed)
			&& currentLevel->IsPassable(Pos.x + 4, Pos.y + yOffset + elapsedSec*m_direction.y * m_speed)) {
			Pos.y += elapsedSec * m_direction.y * m_speed;
		}
		else {
			m_direction.y = -m_direction.y;
			m_direction.x = float(rand() % 3 - 1);
		}
	}
}

void Likelike::Animate(const float & elapsedSec)
{

	m_secCounter += elapsedSec;
	if (m_secCounter >= 1.0f / FPS) {
		m_secCounter = 0;
		++m_FrameCount;
	}

	//TODO: add other diretions and actions
	if (m_FrameCount >= 2) { m_FrameCount = 0; }
	if (m_FrameCount == 0)m_CurrentFrame = f_Default_1;
	if (m_FrameCount == 1)m_CurrentFrame = f_Default_2;
}
