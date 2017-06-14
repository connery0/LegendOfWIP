#include "stdafx.h"
#include "Game.h"

#include "json\json.h"
#include <fstream>
#include "Room.h"


Game::Game(const Window& window)
	:m_Window{ window }
	, m_Hero(new Hero())
	, m_camPos(0,0)
	, m_Cam(10,10)
	, m_SoundEffect_MonsterHit{"Recources/Sounds/Oracle_Enemy_Hit.wav"}
	, m_SoundEffect_LinkHit{ "Recources/Sounds/Oracle_Link_Hurt.wav" }
	, m_SoundEffect_LinkDying{ "Recources/Sounds/Oracle_Link_Dying.wav" }
	, m_music{"Recources/Sounds/Jake Kaufman - Shovel Knight Original Soundtrack - 01 Main Theme.mp3"}
	, m_heroSword{ Point2f(-10,-10),1 }
	, m_CurrentMap{ "Recources/JsonMaps/[C]overworld.json" }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}


void Game::PrintThing() {
	std::cout << "i" << std::endl;
}

void Game::Initialize()
{
	m_Hero->SetPos(336, 248);

	ChangeRoom();

	//m_Cam.SetBoundaries(m_CurrentRoom);
	m_music.Play(true);
	m_music.SetVolume(2);
	m_SoundEffect_MonsterHit.SetVolume(10);
	m_SoundEffect_LinkDying.SetVolume(10);
	m_SoundEffect_LinkHit.SetVolume(10);

}

void Game::Cleanup( )
{
	
}

void Game::Update( float elapsedSec )
{
	if (m_Hero->GetHealth() > 0) {

		UpdateHero(elapsedSec);
		m_heroSword.Update(elapsedSec);
		UpdateMonsters(elapsedSec);
		m_Cam.Update(m_Hero->GetPos(), elapsedSec);

		for (size_t i = 0; i < m_pickups.size(); i++)
		{
			for (size_t j = 0; j < m_CurrentRoom->GetMonsterVector().size(); j++) {
				Rectf monRect = Rectf(m_CurrentRoom->GetMonsterVector()[j]->GetPos().x - 8, m_CurrentRoom->GetMonsterVector()[j]->GetPos().y - 8, 16, 16);
				m_pickups[i]->SetEntity(m_CurrentRoom->GetMonsterVector()[j]);
				if (m_pickups[i]->HitTest(monRect)) {
					m_pickups[i]->Run();
					m_pickups.erase(m_pickups.begin() + i);
					i = m_pickups.size();
					break;
				}
			}
		}
		Rectf heroRect = Rectf(m_Hero->GetPos().x - 8, m_Hero->GetPos().y - 8, 16, 16);
		
		for (size_t i = 0; i < m_pickups.size(); i++)
		{
			m_pickups[i]->SetEntity(m_Hero);
			if (m_pickups[i]->HitTest(heroRect)) {
				m_pickups[i]->Run();
				m_pickups.erase(m_pickups.begin() + i);
				break;
			}
		}

	} else{
		if(m_deathScreenAlpha+ (elapsedSec / 2.0f)<1){
		m_deathScreenAlpha += elapsedSec / 2.0f;
		}
		else { m_deathScreenAlpha = 1; }
	}


	m_globalTime += elapsedSec;
	if (m_globalTime > 1 / m_Fps) {
		m_globalTime =0;
		++m_GlobalFrame;
		if (m_GlobalFrame > m_MaxFrame) {
			m_GlobalFrame = 0;
		}
	}

}

void Game::UpdateHero(const float& elapsedSec) {
	m_Hero->Update(elapsedSec, m_CurrentRoom);

	//When Hero goes out of bounds of a room:
	if (m_CurrentRoom->IsOutOfBounds(m_Hero->GetPos(),m_CurrentMap)) {
		Point2f newPoint = m_Hero->GetPos();
		newPoint.x += 8.0f * m_Hero->GetDirection().x;
		newPoint.y += 8.0f * m_Hero->GetDirection().y;
		
		if (newPoint.x < m_CurrentRoom->GetPos().x) {
			m_Hero->SetPos(m_Hero->GetPos().x - 8.0f, m_Hero->GetPos().y);
		}
		else if (newPoint.y > m_CurrentRoom->GetPos().y) {
			m_Hero->SetPos(m_Hero->GetPos().x , m_Hero->GetPos().y + 8.0f);
		}
		else if (newPoint.x > m_CurrentRoom->GetPos().x + m_CurrentRoom->GetWidth()*16.0f) {
			m_Hero->SetPos(m_Hero->GetPos().x + 8.0f, m_Hero->GetPos().y);
		}
		else if (newPoint.y < m_CurrentRoom->GetPos().y - m_CurrentRoom->GetHeight()*16.0f) {
			m_Hero->SetPos(m_Hero->GetPos().x, m_Hero->GetPos().y - 8.0f);
		}
		ChangeRoom();

	}
}

//Set map and player position before calling!
void Game::ChangeRoom() {
	if (!m_CurrentRoom) {
		m_CurrentRoom = FindRoom(m_Hero->GetPos().x, m_Hero->GetPos().y, m_CurrentMap);
		m_PreviousRoom = FindRoom(m_Hero->GetPos().x, m_Hero->GetPos().y, m_CurrentMap);
	}
	else {
		if (m_CurrentRoom->IsOutOfBounds(m_Hero->GetPos(), m_CurrentMap)) {
			if (!m_PreviousRoom->IsOutOfBounds(m_Hero->GetPos(), m_CurrentMap)) {
				std::unique_ptr<Room> tempRoom = std::move(m_CurrentRoom);
				m_CurrentRoom = std::move(m_PreviousRoom);
				m_PreviousRoom = std::move(tempRoom);
			}
			else {
				std::unique_ptr<Room> tempRoom = FindRoom(m_Hero->GetPos().x, m_Hero->GetPos().y, m_CurrentMap);
				if (tempRoom) {
					m_PreviousRoom = std::move(m_CurrentRoom);
					m_CurrentRoom = std::move(tempRoom);
				}
			}
		}
	}
	m_Cam.SetBoundaries(m_CurrentRoom);
}
void Game::UpdateMonsters(const float & elapsedSec)
{
	Rectf heroRect = Rectf(m_Hero->GetPos().x - 8, m_Hero->GetPos().y - 8, 16, 16);
	for (size_t i = 0; i < m_CurrentRoom->GetMonsterVector().size(); i++)
	{
		m_CurrentRoom->GetMonsterVector()[i]->Update(elapsedSec, m_CurrentRoom);

		if (m_heroSword.isAttacking() && m_CurrentRoom->GetMonsterVector()[i]->HitTest(m_heroSword.GetHitRect()))
		{
			m_CurrentRoom->GetMonsterVector()[i]->ChangeHealth(-m_heroSword.GetDamage());
		}

		if (m_CurrentRoom->GetMonsterVector()[i]->HitTest(heroRect)) {
			int damage = m_CurrentRoom->GetMonsterVector()[i]->DealContactDamage();

			if (damage > 0) {
				m_Hero->ChangeHealth(-damage);
				m_SoundEffect_LinkHit.Play(0);
				if (m_Hero->GetHealth() <= 0) {
					m_SoundEffect_LinkDying.Play(0);
					SoundStream::Stop();
				}
			}
		};
	}
	//TODO: clean up this palceholder code
	//TODO: add living, dying, death states to enemies/link
	for (size_t i = 0; i < m_CurrentRoom->GetMonsterVector().size(); i++)
	{
		if (m_CurrentRoom->GetMonsterVector()[i]->GetHealth() <= 0) {
			m_CurrentRoom->GetMonsterVector().erase(m_CurrentRoom->GetMonsterVector().begin() + i);
			break;
		}
	}
}


void  const Game::Draw( )
{
	ClearBackground( );

	glPushMatrix();
	//glTranslatef(m_camPos.x*m_scale, m_camPos.y*m_scale, 0);
	glTranslatef(-m_Cam.Pos().x*m_scale, -m_Cam.Pos().y*m_scale, 0);
	glScalef(m_scale, m_scale, 1.0f);

	m_CurrentRoom->DrawBackground(m_GlobalFrame);
	//m_PreviousRoom->DrawBackground(m_GlobalFrame);



	for (std::shared_ptr<Pickup> P : m_pickups)
	{
		P->Draw();
	}


	if (m_heroSword.isAttacking()) {
		m_heroSword.Draw();
	}
	m_Hero->Draw();

	glPopMatrix();


	int heroHealth = m_Hero->GetHealth();
	for (int i = 0; i < m_Hero->MaxHealth(); i++)
	{
		if(i<heroHealth){
			//Healthy color
			utils::SetColor(Color4f(1, 0, 0, 0.9f));
		}
		else {
			//Empty color
			utils::SetColor(Color4f(0.5, 0.5, 0.5, 0.9f));
		}

		utils::FillEllipse(10 + i * 25.0f, m_Window.height - 20.0f, 10.0f, 10.0f);
		utils::SetColor(Color4f(0, 0, 0, 0.9f));
		utils::DrawEllipse(10 + i * 25.0f, m_Window.height - 20.0f, 10.0f, 10.0f, 2.0f);
	}

	if (m_Hero->GetHealth() <= 0) {

		utils::SetColor(Color4f(0, 0, 0, m_deathScreenAlpha));
		utils::FillRect(0, 0, m_Window.width, m_Window.height);
	}
}


void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;	
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		m_Hero->SetXSpeed(-1);
		break;
	case SDLK_RIGHT:
		m_Hero->SetXSpeed(1);
		break;
	case SDLK_UP:
		m_Hero->SetYSpeed(1);
		break;
	case SDLK_DOWN:
		m_Hero->SetYSpeed(-1);
		break;
		
/*	case 1073741916:
		//4	
		break;
	case 1073741918:
		//6		
		--m_camPos.x;
		--m_camPos.x;
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
		*/

	case SDLK_KP_PLUS:
		//++m_scale;

		if (!m_CurrentMap.compare("Recources/JsonMaps/[C]overworld.json")) {
			m_CurrentMap = "Recources/JsonMaps/[C]dungeon.json";
			m_Hero->SetPos(90, 40);
			ChangeRoom();
		}
		else if (!m_CurrentMap.compare("Recources/JsonMaps/[C]dungeon.json")) {
			m_CurrentMap = "Recources/JsonMaps/[C]overworld.json";
			m_Hero->SetPos(90, 200);
			ChangeRoom();
		}



		break;
	case SDLK_KP_MINUS:
		//if (m_scale > 1) {
		//	--m_scale;
		//}
		m_CurrentMap = "Recources/JsonMaps/[C]overworld.json";
		m_Hero->SetPos(336, 248);
		ChangeRoom();
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_LEFT:
		m_Hero->SetXSpeed(0);
		break;
	case SDLK_RIGHT:
		m_Hero->SetXSpeed(0);
		break;
	case SDLK_UP:
		m_Hero->SetYSpeed(0);
		break;
	case SDLK_DOWN:
		m_Hero->SetYSpeed(0);
		break;
	}
}


std::unique_ptr<Room> Game::FindRoom(float x, float y,std::string& CFile) {

	Json::Value root;
	Json::Reader reader;
	reader.parse(std::ifstream(CFile), root, false);

	int mapsize = root["rooms"].size();
	for (int i = 0; i < mapsize; i++)
	{
		if (x >= root["rooms"][i]["x"].asInt()
			&& y <= root["rooms"][i]["y"].asInt()
			&& x <= root["rooms"][i]["x"].asInt() + 16 * root["rooms"][i]["w"].asInt()
			&& y >= root["rooms"][i]["y"].asInt() - 16 * root["rooms"][i]["h"].asInt()
			){



			std::cout << root["rooms"][i]["file"].asString() << std::endl;
			return Room::jsonRoom(root["rooms"][i]["file"].asString(), m_CurrentMap,m_Hero);
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
		if (!m_heroSword.isAttacking()) {
			m_heroSword.SetPos(m_Hero->GetPos());
			m_heroSword.SetStatic();
		}
		
		break;
	case SDL_BUTTON_RIGHT:
		//std::cout << " right button " << std::endl;

		m_pickups.push_back(std::make_shared<Pickup>( PickupInt(Point2f(e.x/m_scale+m_Cam.Pos().x, (m_Window.height-e.y)/m_scale + m_Cam.Pos().y), m_Hero, &Entity::ChangeHealth, 1)));
		break;
	case SDL_BUTTON_MIDDLE:
		m_pickups.push_back(std::make_shared<Pickup>(PickupInt(Point2f(e.x / m_scale + m_Cam.Pos().x, (m_Window.height - e.y) / m_scale + m_Cam.Pos().y), m_Hero, &Entity::ChangeHealth, -3)));
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
