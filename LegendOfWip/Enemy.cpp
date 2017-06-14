#include "stdafx.h"
#include "Enemy.h"
#include "Room.h"


static const std::string EnemySpriteSheet{ "Recources/Images/Enemies_cleaned.png" };

Enemy::Enemy() :
	Entity(EnemySpriteSheet)
{
	m_health = 3;
}

Enemy::Enemy(float x, float y) :
	Entity(EnemySpriteSheet)
{
	Pos = Point2f(x, y);
	m_health = 3;
}


Enemy::Enemy(const Enemy & other):Entity(other)
{
}



void Enemy::Update(const float & elapsedSec, const std::unique_ptr<Room>& currentLevel)
{
	UpdateInvulnerability(elapsedSec);
	//Entity::Update(elapsedSec,currentLevel);
	Animate(elapsedSec);

	if (!m_Invulnerable) {
		Movement(elapsedSec, currentLevel);
	}
}

void Enemy::UpdateInvulnerability(const float & elapsedSec) {

	if (m_Invulnerable) {
		//std::cout << "can't touch this" << std::endl;
		m_InvulnerabilityTimer -= elapsedSec;
		if (m_InvulnerabilityTimer <= 0) {
			m_Invulnerable = false;
		}
	}
}

void Enemy::ChangeHealth(int healthChange)
{
	if (!m_Invulnerable) {
		Entity::ChangeHealth(healthChange);
		DealContactDamage();
	}
}
void Enemy::Draw(const Color4f&  overlayColor) const
{
	if (m_health > 0)
		Entity::Draw();
	if (m_Invulnerable) {
		Color4f invulColor = Color4f(1.0f, 0.1f, 0.1f, m_InvulnerabilityTimer / m_InvulnerabilitySetTime);

		//Color4f invulColor =Color4f(m_InvulnerabilityTimer / m_InvulnerabilitySetTime, m_InvulnerabilityTimer / (3*m_InvulnerabilitySetTime), m_InvulnerabilityTimer / (3 * m_InvulnerabilitySetTime), 1);
		//utils::FillRect(Pos.x - 8, Pos.y - 8, 16, 16);
		Entity::Draw(invulColor);
	}
}

void Enemy::Animate(const float & elapsedSec)
{
}

bool Enemy::HitTest(const Point2f & point) {
	if (m_health <= 0) {
		return false;
	}
	Rectf hitRect = Rectf(Pos.x-8, Pos.y-8, 16, 16);
	return utils::IsPointInRect(point, hitRect);
}

bool Enemy::HitTest(const Rectf & hitTestRect) {
	if (   HitTest(Point2f(hitTestRect.left, hitTestRect.bottom))
		|| HitTest(Point2f(hitTestRect.left+hitTestRect.width, hitTestRect.bottom))
		|| HitTest(Point2f(hitTestRect.left, hitTestRect.bottom+hitTestRect.height))
		|| HitTest(Point2f(hitTestRect.left + hitTestRect.width, hitTestRect.bottom + hitTestRect.height))
		) {
		return true;
	}
	return false;
}

int Enemy::DealContactDamage()
{
	if (m_Invulnerable) {
		return 0;
	}
	else {
		m_Invulnerable = true;
		m_InvulnerabilityTimer = m_InvulnerabilitySetTime;
		return m_ContactDamage;
	}
}
