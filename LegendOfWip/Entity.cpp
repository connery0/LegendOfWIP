#include "stdafx.h"
#include "Entity.h"

Entity::Entity() :m_Texture{ "Recources/Diamond.png" }, m_TextClip{ Rectf{0,0,48,48} }
{
}

Entity::Entity(std::string TexturePath) : m_Texture{ TexturePath }, m_TextClip{ Rectf(0,0,16,16)}
{
}

Entity::Entity(std::string TexturePath,Rectf textClip) : m_Texture{ TexturePath }, m_TextClip{ textClip }
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
	//m_Texture.Draw(Rectf(Pos.x,Pos.y,m_TextClip.width,m_TextClip.height),m_TextClip);
	Rectf m_Shape = Rectf(-8, -8, 16, 16);
	glPushMatrix();

	glTranslatef(Pos.x, Pos.y, 0.0f);
	
	if (m_CurrentFrame.m_HMirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}
	if (m_CurrentFrame.m_VMirror) {
		glScalef(1.0f, -1.0f, 1.0f);
	}
	//glTranslatef(-m_Shape.left - m_ClipWidth / 2, 0.0f, 0.0f);
	
	m_Texture.Draw(m_Shape, Rectf(m_CurrentFrame.m_pos.x, m_CurrentFrame.m_pos.y,16,16));
	glPopMatrix();
}
