#include "stdafx.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	//,m_Hero("Recources/Images/LinkCleaned.png",Rectf(0,-638,16,16))
	,m_Hero("Recources/Images/LinkCleaned.png")
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_Hero.Update(elapsedSec);
}

void Game::Draw( )
{
	ClearBackground( );

	glPushMatrix();

	glScalef(4.0f, 4.0f, 1.0f);


	m_Hero.Draw();
	glPopMatrix();


}


void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;	
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		m_Hero.SetXSpeed(-1);
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		m_Hero.SetXSpeed(1);
		break;
	case SDLK_UP:
		//std::cout << "Left arrow key released\n";
		m_Hero.SetYSpeed(1);
		break;
	case SDLK_DOWN:
		//std::cout << "`Right arrow key released\n";
		m_Hero.SetYSpeed(-1);
		break;
		//case SDLK_1:
		//case SDLK_KP_1:
		//	//std::cout << "Key 1 released\n";
		//	break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		m_Hero.SetXSpeed(0);
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		m_Hero.SetXSpeed(0);
		break;
	case SDLK_UP:
		//std::cout << "Left arrow key released\n";
		m_Hero.SetYSpeed(0);
		break;
	case SDLK_DOWN:
		//std::cout << "`Right arrow key released\n";
		m_Hero.SetYSpeed(0);
		break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		std::cout << " left button " << std::endl;
		m_Hero.Pos = Point2f(e.x, m_Window.height - e.y);
		break;
	case SDL_BUTTON_RIGHT:
		std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( )
{
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
