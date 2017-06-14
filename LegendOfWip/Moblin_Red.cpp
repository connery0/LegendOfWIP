#include "stdafx.h"
#include "Moblin_Red.h"
#include "MonsterFrames_Moblin_red.h"
#include "Room.h"


Moblin_Red::Moblin_Red():
	Enemy()
{
	Initialize();
}

Moblin_Red::Moblin_Red(float x, float y):Enemy(x,y)
{
	Initialize();
}

void Moblin_Red::Initialize() {

	m_CurrentFrame = f_Down_1;
	m_speed = 24;
}

Moblin_Red::Moblin_Red(const Moblin_Red & other):
	Enemy(other)
{
}


void Moblin_Red::Movement(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel) {
	MoveChangeTimer -= elapsedSec;
	if (MoveChangeTimer <= 0) {
		if (m_direction.x == 0) {
			if (rand() % 2) {
				m_direction = Point2f(-1, 0);
			}
			else {
				m_direction = Point2f(1, 0);
			}
		}
		else {

			if (rand() % 2) {
				m_direction = Point2f(0, -1);
			}
			else {
				m_direction = Point2f(0, 1);
			}
		}
		MoveChangeTimer = float(rand() % 3);
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
		Pos.x += elapsedSec * m_direction.x *2* m_speed;
		Pos.y += elapsedSec * m_direction.y * 2*m_speed;
		MoveChangeTimer = float(rand() % 3);
	}
	else {
		if (currentLevel->IsPassable(Pos.x + xOffset + elapsedSec * m_direction.x * m_speed, Pos.y - 6)
			&& currentLevel->IsPassable(Pos.x + xOffset + elapsedSec * m_direction.x * m_speed, Pos.y + 4)
			) {
			Pos.x += elapsedSec * m_direction.x * m_speed;
		}
		else {
			m_direction.x = -m_direction.x;
			MoveChangeTimer = 0.0f;
		}

		if (currentLevel->IsPassable(Pos.x - 4, Pos.y + yOffset + elapsedSec*m_direction.y * m_speed)
			&& currentLevel->IsPassable(Pos.x + 4, Pos.y + yOffset + elapsedSec*m_direction.y * m_speed)) {
			Pos.y += elapsedSec * m_direction.y * m_speed;
		}
		else {
			m_direction.y = -m_direction.y;
			MoveChangeTimer = 0.0f;
		}
	}
}


void Moblin_Red::Animate(const float & elapsedSec)
{
}
