#pragma once
#include "utils.h"
#include "Texture.h"
#include "Frame.h"

class Entity
{
public:
	Entity();
	Entity(std::string TexturePath);
	Entity(std::string TexturePath, Rectf textClip);
	~Entity();
	virtual void Update(float elapsedSec);
	virtual void Draw();
	Point2f Pos{ 0,0 };

protected:
	Texture m_Texture;
	Rectf m_TextClip;
	bool m_VMirror{ false };
	bool m_HMirror{ false };
	Frame m_CurrentFrame{ Point2f(0,0) };
	int m_FrameCount{ 0 };
};

