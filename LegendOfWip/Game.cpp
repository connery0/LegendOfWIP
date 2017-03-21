#include "stdafx.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	for (size_t i = 0; i < 5; i++)
	{
		Entity* E = new Entity("Recources/PowerUp.png", Rectf(0, 70, 70, 70));
		E->Pos = { i * 50.0f,i * 50.0f };
		m_EntityList.push_back(E);
	}	
	for (size_t i = 0; i < 5; i++)
	{
		Entity* E = new Entity("Recources/PowerUp.png",Rectf(0,0,70,70));
		E->Pos = { m_Window.width - (i+1) * 50.0f,i * 50.0f };
		m_EntityList.push_back(E);
	}
	for (size_t i = 0; i < 5; i++)
	{
		Entity* E = new Entity();
		E->Pos = { m_Window.width - (i+1) * 50.0f,m_Window.height - (i+1) * 50.0f };
		m_EntityList.push_back(E);
	}
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
}

void Game::Draw( )
{
	ClearBackground( );
	for (size_t i = 0; i < m_EntityList.size(); i++)
	{
		m_EntityList[i]->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
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
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
