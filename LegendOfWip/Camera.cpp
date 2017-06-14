#include "stdafx.h"
#include "Camera.h"

Camera::Camera(int widthInTiles, int heightInTiles):
	m_Width(16.0f*widthInTiles)
	,m_Height(16.0f*heightInTiles)
	//,m_FreeRoam((10 * 16 * 1 / 4), (10 * 16 * 1 / 4), (10 * 16 * 2 / 4), (10 * 16 * 2 / 4))
{
}

void Camera::SetBoundaries(const std::unique_ptr<Room>& currentRoom)
{
	m_Boundaries.left = currentRoom->GetPos().x;
	m_Boundaries.bottom = currentRoom->GetPos().y;
	m_Boundaries.width= 16.0f* currentRoom->GetWidth();
	m_Boundaries.height=16.0f* currentRoom->GetHeight();

	m_Position = Point2f(0, 0);
}

void Camera::Update(const Point2f pos, float elapsedSec)
{
	m_Position.x= pos.x-m_Width/2;
	m_Position.y = pos.y - m_Height/ 2;
}

Point2f Camera::Pos()
{
	return Bounds(m_Position);
}


Point2f Camera::Track(const std::unique_ptr<Entity>& toTrack)
{
	return Point2f();
}

Point2f Camera::Bounds(Point2f bottomLeftPos)
{
	if (bottomLeftPos.x <= m_Boundaries.left) {bottomLeftPos.x = m_Boundaries.left;}
	else if (bottomLeftPos.x >= m_Boundaries.left + m_Boundaries.width-m_Width) { bottomLeftPos.x = m_Boundaries.left + m_Boundaries.width - m_Width; }
	
	if (bottomLeftPos.y <= m_Boundaries.bottom - m_Boundaries.height) { bottomLeftPos.y = m_Boundaries.bottom - m_Boundaries.height; }
	else if (bottomLeftPos.y +m_Height>= m_Boundaries.bottom) { bottomLeftPos.y = m_Boundaries.bottom - m_Height; }
	
	return bottomLeftPos;
}
