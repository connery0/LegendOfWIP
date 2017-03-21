#pragma once
#include "utils.h"
#include "Texture.h"

class Entity
{
public:
	Entity();
	Entity(std::string TexturePath, Rectf textClip);
	~Entity();
	void Update(float elapsedSec);
	void Draw();
	Point2f Pos{ 0,0 };

protected:
	Texture m_Texture;
	Rectf m_TextClip;
};

