#pragma once
#include "Entity.h"
#include "Hero.h"
#include "Room.h"

class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( );

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

	std::unique_ptr<Room> FindRoom(int x, int y);

private:
	// DATA MEMBERS
	Window m_Window;
	Hero m_Hero;
	std::unique_ptr<Room> m_CurrentRoom;
	std::unique_ptr<Room> m_PreviousRoom;
	float m_scale{ 2.5f };

	Rectf testRect{ 0,0,16,16 };

	Point2f m_camPos;


	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( );
};