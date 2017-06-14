#include "stdafx.h"
#include "Room.h"
#include "Hero.h"

Room::Room(std::string tileSheet, std::string Cname) :
	m_TileSheet(tileSheet),m_MapName{Cname}
{}

std::unique_ptr<Room> Room::jsonRoom(std::string FileName, std::string& Cname, const std::shared_ptr<Hero>& Hero)
{
	Json::Value root;
	Json::Reader reader;
	reader.parse(std::ifstream(FileName), root, false);
	std::vector<std::string> monsterList;

	std::unique_ptr<Room> ReturnRoom(new Room(root["tilesets"][0]["image"].asString(), Cname));
	ReturnRoom->SetX(root["properties"]["pos_x"].asFloat());
	ReturnRoom->SetY(root["properties"]["pos_y"].asFloat());
	ReturnRoom->SetHeight(root["layers"][0]["height"].asInt());
	ReturnRoom->SetWidth(root["layers"][0]["width"].asInt());

	//int mapSize = root["layers"][0]["data"].size();

	int mapWidth = root["layers"][0]["width"].asInt();
	int mapHeight = root["layers"][0]["height"].asInt();

	for (int tileNumber = 0; tileNumber < mapWidth*mapHeight; tileNumber++)
	{
		int tileId;
		Point2f tilePos;
		Tile tileCreation;

		for (size_t layer = 0; layer < root["layers"].size(); layer++)
		{
			tileId = root["layers"][layer]["data"][tileNumber].asInt()-1;

			//Check to see if we are on a monster layer
			if (root["layers"][layer]["name"].asString() == "Enemies") {
				if (tileId != -1) {
					//room coördinates
					tileId = tileId - (root["tilesets"][1]["firstgid"].asInt() -1);
					std::shared_ptr<Enemy> monster = EnemyConstructor::GetEnemyByName(
						root["tilesets"][1]["tileproperties"][std::to_string(tileId)]["Name"].asString(),
						(tileNumber%mapWidth) * 16.0f + 8,
						float(tileNumber / mapWidth) * 16.0f + 8.0f);

					ReturnRoom->PushEnemy(monster);
				}
			}
			//Otherwise it'll be one of the possibly many tile layers
			else {
				if (layer == 0) {
					tileCreation = Tile(root["tilesets"][0]["tileproperties"][std::to_string(tileId)]["Passable"].asBool());
				}
				if (tileId != -1) {
					//spritesheet location
					tilePos.x = 16.0f * ((tileId) % root["tilesets"][0]["columns"].asInt());
					tilePos.y = 16 + 16.0f * ((tileId) / root["tilesets"][0]["columns"].asInt());

					tileCreation.AddPos(tilePos);
				}
			}
		}

		ReturnRoom->PushBackground(tileCreation);
	}

	return ReturnRoom;
}

Point2f Room::GetPos()
{
	return m_pos;
}

void Room::SetX(float x)
{
	m_pos.x = x;
}
void Room::SetY(float y)
{
	m_pos.y = y;
}

void Room::SetWidth(int width)
{
	m_width = width;
}

void Room::SetHeight(int height)
{
	m_height = height;
}

int Room::GetHeight()
{
	return m_height;
}

int Room::GetWidth()
{
	return m_width;
}
bool Room::IsOutOfBounds(float x, float y) const{
	return (x< m_pos.x || y>m_pos.y || x > m_pos.x + (m_width * 16) || y < m_pos.y - (m_height * 16));
}
bool  Room::IsOutOfBounds(Point2f checkPos)const {
	return IsOutOfBounds(checkPos.x, checkPos.y);
}
bool  Room::IsOutOfBounds(Point2f checkPos,std::string& CFile)const {
	//compare returns 0 if they are equal, which would mean it's still in bounds
	return (m_MapName.compare(CFile) || IsOutOfBounds(checkPos.x, checkPos.y));
}

bool Room::IsPassable(float x,float y) {
	//Assume hero can't get to the border if it's blocked on the next screen
	if (IsOutOfBounds(x, y)) return true;

	int xTile = int(floor(( x-m_pos.x) / 16.0f));
	int yTile = int(floor((y-m_pos.y) / -16.0f));
	
	int tileNumber = m_width*yTile + xTile;
	if (tileNumber >= 0 && tileNumber < int(m_Background.size()) && x<float(m_pos.x + m_width*16)) {
		return m_Background[tileNumber].IsPassable();
	}
	return false;
}

void Room::DrawBackground(int globalFrame)const
{
	for (int h = 0; h < m_height; ++h)
	{
		for (int w = 0; w < m_width; ++w)
		{
			int tileNum = h*m_width + w;
			int frame = globalFrame % m_Background[tileNum].GetFrameCount();

			//draw order
			Rectf m_Shape = Rectf(
									m_pos.x + (16 * w),
									m_pos.y - (16 * (h+1)),
									16, 16
								);
			m_TileSheet.Draw(
								m_Shape, 
								Rectf(
									m_Background[tileNum].GetPoint(frame).x,
									m_Background[tileNum].GetPoint(frame).y,
									16, 16)
							);
		}
	}
	
	for (auto monster: m_Monsters)
	{
		monster->Draw();
	}
	
}

void Room::PushBackground(Tile tile)
{
	m_Background.push_back(tile);
}

void Room::PushEnemy(std::shared_ptr<Enemy> enemy)
{
	Point2f pos = enemy->GetPos();
	pos.x += m_pos.x;
	pos.y = m_pos.y - pos.y;
	enemy->SetPos(pos.x, pos.y);
	m_Monsters.push_back(enemy);
}

std::vector<std::shared_ptr<Enemy>> Room::GetEnemyList()
{
	return m_Monsters;
}

void Room::PushBackground(std::vector<Tile> background)
{
	m_Background = background;
}

std::vector<std::shared_ptr<Enemy>>& Room::GetMonsterVector()
{
	return m_Monsters;
}

std::shared_ptr<Hero> Room::GetHero() const
{
	return m_HeroRef;
}
