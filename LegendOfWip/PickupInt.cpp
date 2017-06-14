#include "stdafx.h"
#include "PickupInt.h"
#include "Entity.h"


PickupInt::PickupInt(Point2f pos, std::shared_ptr<Entity> sharedP, function_type function, int function_param):
	Pickup(pos,sharedP)
	,m_Function(function)
	,m_param(function_param)
{
}

void PickupInt::Run() {
		(m_Entity.get()->*m_Function)(m_param);
	}

void PickupInt::Draw() const
{
	if (m_param < 0) {
		utils::SetColor(Color4f(0, 0, 0, 1));
	}
	else {
		utils::SetColor(Color4f(1, 0, 0, 1));
	}

	utils::DrawPoint(m_pos, 16);
}

void PickupInt::SetEntity(std::shared_ptr<Entity> E)
{
	m_Entity = E;
}

