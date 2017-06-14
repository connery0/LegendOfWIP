#include "stdafx.h"
#include "Projectile.h"
#include "SwordFrames.h"

//TODO: expand into all projectiles, Is only the heroes sword(subclass) right now
Projectile::Projectile(Point2f position, int damage) :
	m_Pos{ position }
	, m_HitRect{ position.x,position.y,16,16 }
	, m_Damage{ damage }
	, m_attackTime{0}
	, m_Sprites("Recources/Images/LinkCleaned.png")
{
	m_CurrentFrame = f_sword_V_Up;
}

void Projectile::Update(const float & elapsedSec)
{
	if (m_IsAttacking&& m_Frame<int(animationFrames.size())) {

		m_attackTime += elapsedSec;

		if (m_attackTime >= (1.0f / m_fps)) {
			m_attackTime = 0;
			++m_Frame;
		}

	}
	if (m_Frame>=int(animationFrames.size())) {
		m_IsAttacking = false;
		
	}
	else {
		m_CurrentFrame = animationFrames[m_Frame];
	}
}

void  const Projectile::Draw()
{
	if (m_IsAttacking) {
		glPushMatrix();

		glTranslatef(m_Pos.x, m_Pos.y, 0.0f);

		if (m_CurrentFrame.m_HMirror) {
			glScalef(-1.0f, 1.0f, 1.0f);
		}
		if (m_CurrentFrame.m_VMirror) {
			glScalef(1.0f, -1.0f, 1.0f);
		}

		m_Sprites.Draw(m_Shape, Rectf(m_CurrentFrame.m_pos.x, m_CurrentFrame.m_pos.y, 16, 16));
		glPopMatrix();
	}
}

Rectf Projectile::GetHitRect()
{
	return m_HitRect;
}

int Projectile::GetDamage()
{
	if(m_IsAttacking){
	return m_Damage;
	}
	return 0;
}

bool Projectile::isAttacking()
{
	return m_IsAttacking;
}

void Projectile::SetPos(Point2f pos)
{
	m_Pos = pos;
	m_HitRect.left = pos.x;
	m_HitRect.bottom = pos.y;
}

void Projectile::SlashRight()
{
	m_IsAttacking = true;
	m_attackTime = 0;
	m_Frame = 0;
	animationFrames.clear();
	animationFrames.push_back(f_sword_V_Up);
	animationFrames.push_back(f_sword_D_UpToRight);
	animationFrames.push_back(f_sword_H_Right);
	m_HitRect = Rectf(m_Pos.x, m_Pos.y, 16, 16);

}

void Projectile::SetStatic()
{
	m_IsAttacking = true;
	m_attackTime = 0;
	m_Frame = 0;
	animationFrames.clear();
	animationFrames.push_back(f_static_1);
	animationFrames.push_back(f_static_2);
	animationFrames.push_back(f_static_3);
	animationFrames.push_back(f_static_1);
	animationFrames.back().m_VMirror = true;
	animationFrames.push_back(f_static_2);
	animationFrames.back().m_VMirror = true;
	animationFrames.push_back(f_static_3);
	animationFrames.back().m_VMirror = true;

	animationFrames.push_back(f_static_1);
	animationFrames.push_back(f_static_2);
	animationFrames.push_back(f_static_3);
	animationFrames.push_back(f_static_1);
	animationFrames.back().m_VMirror = true;
	animationFrames.push_back(f_static_2);
	animationFrames.back().m_VMirror = true;
	animationFrames.push_back(f_static_3);
	animationFrames.back().m_VMirror = true;

	m_HitRect = Rectf(m_Pos.x, m_Pos.y, 16, 16);
}

void Projectile::SlashDown()
{
	m_IsAttacking = true;
	m_attackTime = 0;
	m_Frame = 0;
	animationFrames.clear();
	animationFrames.push_back(f_sword_H_Right);
	animationFrames.push_back(f_sword_D_RightToDown);
	animationFrames.push_back(f_sword_V_Down);
	m_HitRect = Rectf(m_Pos.x, m_Pos.y-16, 16, 16);
}

void Projectile::SlashLeft()
{
	m_IsAttacking = true;
	m_attackTime = 0;
	m_Frame = 0;
	animationFrames.clear();
	animationFrames.push_back(f_sword_V_Down);
	animationFrames.push_back(f_sword_D_DownToLeft);
	animationFrames.push_back(f_sword_H_Left);
	m_HitRect = Rectf(m_Pos.x-16, m_Pos.y-16, 16, 16);
}

void Projectile::SlashUp()
{
	m_IsAttacking = true;
	m_attackTime = 0;
	m_Frame = 0;
	animationFrames.clear();
	animationFrames.push_back(f_sword_H_Left);
	animationFrames.push_back(f_sword_D_LeftToUp);
	animationFrames.push_back(f_sword_V_Up);
	m_Pos.x -= 8;
	m_Pos.y += 8;
	m_HitRect = Rectf(m_Pos.x-16, m_Pos.y, 16, 16);
}
