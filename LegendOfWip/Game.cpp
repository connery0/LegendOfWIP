#include "stdafx.h"
#include "Game.h"

const std::string testLvlString =
"|16,0|17,0|05,1|16,0|18,0|15,0|14,0|15,0|14,0|15,0"
"|16,0|16,0|05,1|16,0|22,0|23,0|22,0|14,0|15,0|14,0"
"|07,1|16,0|05,1|17,1|16,1|16,1|02,1|22,0|14,0|15,0"
"|05,1|16,0|05,1|03,0|03,0|03,0|20,1|20,1|22,0|14,0"
"|08,1|04,1|11,1|03,0|01,0|03,0|20,1|20,1|20,1|22,0"
"|05,1|03,0|03,0|03,0|00,1|03,0|20,1|20,1|09,1|00,1"
"|05,1|00,1|02,1|00,1|00,1|03,0|08,1|26,1|24,1|07,1"
"|10,1|07,1|03,0|03,0|03,0|03,0|08,1|25,1|26,1|09,1"
"|00,1|05,1|03,0|06,1|13,1|13,1|26,1|24,1|25,1|09,1"
"|00,1|05,1|03,1|08,1|25,1|12,1|12,1|12,1|12,1|11,1";

const std::string testLvlString2 =
"|22,1|23,1|18,1|19,1|22,1|23,1|23,1|23,1|23,1|23,1" 
"|06,1|07,1|22,1|23,1|03,1|03,1|03,1|03,1|03,1|03,1" 
"|10,1|12,1|04,1|07,1|02,1|03,1|03,1|03,1|03,1|03,1" 
"|16,1|16,1|16,1|05,1|03,1|03,1|03,1|03,1|03,1|03,1" 
"|20,1|17,1|16,1|05,1|00,1|00,1|00,1|00,1|00,1|00,1";




Game::Game(const Window& window)
	:m_Window{ window }
	//,m_Hero("Recources/Images/LinkCleaned.png",Rectf(0,-638,16,16))
	, m_Hero("Recources/Images/LinkCleaned.png")
	, m_level(Point2f(0,0), 10, 10, testLvlString)
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize()
{
	m_Hero.Pos.x = 16;
	m_Hero.Pos.y = 16;
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_Hero.Update(elapsedSec,m_level);
}

void Game::Draw( )
{
	ClearBackground( );

	glPushMatrix();

	glScalef(m_scale, m_scale, 1.0f);

	m_level.DrawBackground();
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
	case SDLK_KP_PLUS:
		//std::cout << "`Right arrow key released\n";
		++m_scale;
		++m_scale;
		std::cout << "!!!!!!!!!!!!!!!!!!!!!!! "<< std::endl;
		break;
	case SDLK_KP_MINUS:
		//std::cout << "`Right arrow key released\n";
		if (m_scale > 2) {
			--m_scale;
			--m_scale;
		}
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
		m_Hero.Pos = Point2f(e.x/m_scale, (m_Window.height - e.y)/m_scale);
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
