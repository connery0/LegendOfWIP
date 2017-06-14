#pragma once
#include <memory>

class Entity;

class Pickup {
public:

	Pickup(Point2f pos, std::shared_ptr<Entity> sharedP);

	virtual void Run() {};
	virtual void Draw() const {};
	virtual bool HitTest(Rectf rect);
	virtual void SetEntity(std::shared_ptr<Entity> E);

protected:
	std::shared_ptr<Entity> m_Entity;
	Point2f m_pos;
};