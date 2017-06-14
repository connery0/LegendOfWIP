#pragma once
#include "Entity.h"

class Enemy :
	public Entity
{
public:
	Enemy();
	Enemy(float x, float y);
	Enemy(const Enemy& other);


	void Update(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel) override;

	void UpdateInvulnerability(const float & elapsedSec);

	void ChangeHealth(int healthChange) override; 

	virtual void Draw(const Color4f&  overlayColor=Color4f(1,1,1,1)) const override;

	bool HitTest(const Point2f & point);
	bool HitTest(const Rectf & testRect);
	int DealContactDamage();

protected:
	virtual void Animate(const float &elapsedSec);

	bool m_Invulnerable{ false };
	float m_InvulnerabilityTimer{ 0 };
	const float m_InvulnerabilitySetTime{ 3 };

	int m_ContactDamage{ 1 };
};

