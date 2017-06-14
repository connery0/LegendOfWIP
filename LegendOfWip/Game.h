#pragma once
#include "Entity.h"
#include "Hero.h"
#include "Room.h"
#include "Camera.h"

#include "SoundEffect.h"
#include "SoundStream.h"
#include "Projectile.h"

#include "Pickup.h"
#include "PickupInt.h"



class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	~Game();

	void Update( float elapsedSec );
	void  const Draw( );

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

	std::unique_ptr<Room> FindRoom(float x, float y,std::string& CFile);

private:

	SoundEffect m_SoundEffect_MonsterHit;
	SoundEffect m_SoundEffect_LinkHit;
	SoundEffect m_SoundEffect_LinkDying;
	SoundStream m_music;
	
	void UpdateHero(const float & elapsedSec);
	void ChangeRoom();
	void UpdateMonsters(const float & elapsedSec);



	// DATA MEMBERS
	Window m_Window;
	std::shared_ptr<Hero> m_Hero;
	std::unique_ptr<Room> m_CurrentRoom;
	std::unique_ptr<Room> m_PreviousRoom;
	std::vector <std::shared_ptr<Pickup>> m_pickups;
	float m_scale{ 2.5f };

	float m_globalTime{ 0 };
	int m_GlobalFrame{ 0 };
	const int m_MaxFrame{ 8 };
	const float m_Fps{4 };
	float m_deathScreenAlpha{ 0 };
	std::string m_CurrentMap;

	Projectile m_heroSword;

	Point2f m_camPos;
	Camera m_Cam;

	

	void PrintThing();

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( );
};