#pragma once
#include "stdafx.h"
#include "Room.h"
#include "Entity.h"
class Camera
{
public:
	Camera(int widthInTiles, int heightInTiles);
	void SetBoundaries(const std::unique_ptr<Room>& currentRoom);
	void Update(const Point2f pos,float elapsedSec);
	Point2f Pos();

private:
	float m_Width;
	float m_Height;
	Rectf m_Boundaries;
	Point2f m_Position;

	Point2f m_FreePosition;
	Rectf m_FreeRoam;

	Point2f Track(const std::unique_ptr<Entity>& toTrack);
	Point2f Bounds(Point2f bottomLeftPos);
};
