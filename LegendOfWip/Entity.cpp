#include "stdafx.h"
#include "Entity.h"

Entity::Entity(std::string TexturePath) : m_Texture{ TexturePath }
{
}

Entity::~Entity()
{
}

void Entity::Update(float elapsedSec)
{
}

void Entity::Draw()
{
	glPushMatrix();

	glTranslatef(Pos.x, Pos.y, 0.0f);
	
	if (m_CurrentFrame.m_HMirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}
	if (m_CurrentFrame.m_VMirror) {
		glScalef(1.0f, -1.0f, 1.0f);
	}
	
	m_Texture.Draw(m_Shape, Rectf(m_CurrentFrame.m_pos.x, m_CurrentFrame.m_pos.y,16,16));
	glPopMatrix();
}


Point2f Entity::GetPos()
{
	return Pos;
}

void Entity::SetPos(int x, int y)
{
	Pos.x = x;
	Pos.y = y;
}

