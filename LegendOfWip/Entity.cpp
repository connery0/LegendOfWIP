#include "stdafx.h"
#include "Entity.h"
#include "Room.h"

Entity::Entity(std::string TexturePath):m_Texture(std::shared_ptr<Texture>(new Texture(TexturePath)))
{
}

Entity::Entity(const Entity & other):
	m_Texture{other.m_Texture}
	, Pos{ other.Pos }
	, m_VMirror{ other.m_VMirror }
	,m_HMirror{other.m_HMirror}
	, m_CurrentFrame{ other.m_CurrentFrame }
	,m_FrameCount{other.m_FrameCount}
	, m_Shape{ other.m_Shape }
{
}

void Entity::Update(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel)
{
	Update(elapsedSec);
}

void Entity::Update(const float& elapsedSec) {
	m_secCounter += elapsedSec;
	if (m_secCounter >= 1.0f / FPS) {
		m_secCounter = 0;
		++m_FrameCount;
	}
}

void Entity::Draw(const Color4f&  overlayColor) const
{
	
	glPushMatrix();

	glTranslatef(Pos.x, Pos.y, 0.0f);
	
	if (m_CurrentFrame.m_HMirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}
	if (m_CurrentFrame.m_VMirror) {
		glScalef(1.0f, -1.0f, 1.0f);
	}
	
	m_Texture->Draw(m_Shape, Rectf(m_CurrentFrame.m_pos.x, m_CurrentFrame.m_pos.y,16,16), overlayColor);
	glPopMatrix();
}

Point2f Entity::GetPos()
{
	return Pos;
}

void Entity::SetPos(float x, float y)
{
	Pos.x = x;
	Pos.y = y;
}

int Entity::GetHealth()
{
	return m_health;
}

void Entity::ChangeHealth(int healthChange)
{
	m_health += healthChange;
	if (m_health > m_MaxHealth) {
		m_health = m_MaxHealth;
	}
}

void Entity::SetHealth(int newHealth)
{
	m_health = newHealth;
}

void Entity::Movement(const float & elapsedSec, const std::unique_ptr<Room> &currentLevel) {
	int xOffset = 0;
	if (m_direction.x < 0) { xOffset = -8; }
	if (m_direction.x > 0) { xOffset = 8; }
	int yOffset = 0;
	if (m_direction.y < 0) { yOffset = -8; }
	if (m_direction.y > 0) { yOffset = 8; }


	if (currentLevel->IsPassable(Pos.x + xOffset + elapsedSec * m_direction.x * m_speed, Pos.y - 6)
		&& currentLevel->IsPassable(Pos.x + xOffset + elapsedSec * m_direction.x * m_speed, Pos.y + 4)
		) {
		Pos.x += elapsedSec * m_direction.x * m_speed;
	}

	if (currentLevel->IsPassable(Pos.x - 4, Pos.y + yOffset + elapsedSec*m_direction.y * m_speed)
		&& currentLevel->IsPassable(Pos.x + 4, Pos.y + yOffset + elapsedSec*m_direction.y * m_speed)) {
		Pos.y += elapsedSec * m_direction.y * m_speed;
	}
}

