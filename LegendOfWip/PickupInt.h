#pragma once
#include "Pickup.h"

class Entity;

class PickupInt : public Pickup{
public:

	typedef void(Entity::*function_type)(int);
	PickupInt(Point2f pos, std::shared_ptr<Entity> sharedP, function_type function, int function_param);

	virtual void Run() override;
	virtual void Draw() const override;
	void SetEntity(std::shared_ptr<Entity> E);

protected:
	function_type m_Function;
	int m_param;
};