#include "stdafx.h"
#include "Entity.h"

Entity::Entity() :m_Texture{ "Recources/Diamond.png" }, m_TextClip{ Rectf{0,0,48,48} }
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
	m_Texture.Draw(Rectf(Pos.x,Pos.y,m_TextClip.width,m_TextClip.height),m_TextClip);
}
