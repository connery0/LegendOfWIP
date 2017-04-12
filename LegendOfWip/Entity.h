#pragma once
#include "stdafx.h"
#include "Texture.h"
#include "Frame.h"

class Entity
{
public:
	Entity(std::string TexturePath);
	~Entity();
	virtual void Update(float elapsedSec);
	virtual void Draw();
	Point2f GetPos();
	void SetPos(int x, int y);

protected:
	Point2f Pos{ 0,0 };
	Texture m_Texture;
	bool m_VMirror{ false };
	bool m_HMirror{ false };
	Frame m_CurrentFrame{ Point2f(0,0) };
	int m_FrameCount{ 0 };
	//Default sprite size
	Rectf m_Shape{ -8,-8,16,16 };
};

