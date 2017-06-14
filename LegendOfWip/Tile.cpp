#include "stdafx.h"
#include "Tile.h"

Tile::Tile(bool passable):m_Passable(passable),m_FrameCount(0)
{
}

void Tile::AddPos(Point2f originalPoint)
{
	m_FrameCount++;
	m_Points.push_back(originalPoint);
}

int  Tile::GetFrameCount() const
{
	return m_FrameCount;
}

bool  Tile::IsPassable()const
{
	return m_Passable;
}

Point2f  Tile::GetPoint(int index)const
{
	return m_Points[index];
}
