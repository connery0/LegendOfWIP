#include "stdafx.h"
#include "Pickup.h"

#include "Entity.h"


Pickup::Pickup(Point2f pos, std::shared_ptr<Entity> sharedP):
	m_Entity(sharedP),
	m_pos(pos)
{
}

bool Pickup::HitTest(Rectf rect)
{
	if (utils::IsPointInRect(m_pos, rect)) {
		return true;
	}
	return false;
}

void Pickup::SetEntity(std::shared_ptr<Entity> E)
{
	m_Entity = E;
}

