#include "stdafx.h"
#include "Game.h"

#include "json\json.h"
#include <fstream>


Game::Game(const Window& window)
	:m_Window{ window }
	//,m_Hero("Recources/Images/LinkCleaned.png",Rectf(0,-638,16,16))
	, m_Hero("Recources/Images/LinkCleaned.png")
	, m_camPos(0,0)
{
	m_CurrentRoom = Room::jsonRoom("Recources/JsonMaps/FrontTempleGate10x10.json");
	m_PreviousRoom = Room::jsonRoom("Recources/JsonMaps/PathTemple10x10.json");
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize()
{
	m_Hero.SetPos(16, 16);
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_Hero.Update(elapsedSec, m_CurrentRoom);
	if (m_CurrentRoom->IsOutOfBounds(m_Hero.GetPos())) {
		if (!m_PreviousRoom->IsOutOfBounds(m_Hero.GetPos())) {
			std::unique_ptr<Room> tempRoom = std::move(m_CurrentRoom);
			m_CurrentRoom = std::move(m_PreviousRoom);
			m_PreviousRoom = std::move(tempRoom);
		}
		else {
			m_PreviousRoom = std::move(m_CurrentRoom);
			std::cout << "bzzzzzzzzzzzzzzzzzz";
			m_CurrentRoom = FindRoom(m_Hero.GetPos().x, m_Hero.GetPos().y);
		}
	}
}

void Game::Draw( )
{
	ClearBackground( );

	glPushMatrix();
	glTranslatef(m_camPos.x*m_scale, m_camPos.y*m_scale, 0);
	glScalef(m_scale, m_scale, 1.0f);

	m_CurrentRoom->DrawBackground(0);
	m_PreviousRoom->DrawBackground(0);
/*
	utils::SetColor(Color4f(1, 0, 0, 0.5f));
	utils::FillRect(testRect);*/

	m_Hero.Draw();
	glPopMatrix();
}


void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;	
	switch (e.keysym.sym)
	{

	case SDLK_LEFT:
		m_Hero.SetXSpeed(-1);
		break;
	case SDLK_RIGHT:
		m_Hero.SetXSpeed(1);
		break;
	case SDLK_UP:
		m_Hero.SetYSpeed(1);
		break;
	case SDLK_DOWN:
		m_Hero.SetYSpeed(-1);
		break;

	case 1073741916:
		//4		
		--m_camPos.x;
		--m_camPos.x;
		break;
	case 1073741918:
		//6		
		++m_camPos.x;
		++m_camPos.x;
		break;
	case 1073741920:
		//8	
		++m_camPos.y;
		++m_camPos.y;
		break;
	case 1073741914:
		//2	
		--m_camPos.y;
		--m_camPos.y;
		break;


	case SDLK_KP_PLUS:
		++m_scale;
		break;
	case SDLK_KP_MINUS:
		if (m_scale > 1) {
			--m_scale;
		}
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		m_Hero.SetXSpeed(0);
		break;
	case SDLK_RIGHT:
		m_Hero.SetXSpeed(0);
		break;
	case SDLK_UP:
		m_Hero.SetYSpeed(0);
		break;
	case SDLK_DOWN:
		m_Hero.SetYSpeed(0);
		break;
	}
}


std::unique_ptr<Room> Game::FindRoom(int x, int y) {

	Json::Value root;
	Json::Reader reader;
	reader.parse(std::ifstream("Recources/JsonMaps/[C]overworld.json"), root, false);

	int mapsize = root["rooms"].size();
	for (size_t i = 0; i < mapsize; i++)
	{
		if (x >= root["rooms"][i]["x"].asInt()
			&& y <= root["rooms"][i]["y"].asInt()
			&& x <= root["rooms"][i]["x"].asInt() + 16 * root["rooms"][i]["w"].asInt()
			&& y >= root["rooms"][i]["y"].asInt() - 16 * root["rooms"][i]["h"].asInt()
			){
			testRect.left = root["rooms"][i]["x"].asInt();
			testRect.bottom = root["rooms"][i]["y"].asInt();
			testRect.width = root["rooms"][i]["w"].asInt() *16;
			testRect.height = -root["rooms"][i]["h"].asInt() *16;

			std::cout << root["rooms"][i]["file"].asString() << std::endl;
			return Room::jsonRoom(root["rooms"][i]["file"].asString());
		}
	}
	return nullptr;
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
		//std::cout << " left button " << std::endl;
		m_Hero.SetPos(e.x/m_scale -m_camPos.x, (m_Window.height - e.y)/m_scale - m_camPos.y);
		FindRoom(e.x / m_scale - m_camPos.x, (m_Window.height - e.y) / m_scale - m_camPos.y);
		break;
	case SDL_BUTTON_RIGHT:
		//std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:	
		//std::cout << " middle button " << std::endl;
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
