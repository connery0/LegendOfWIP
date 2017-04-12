#include "stdafx.h"
#include "Room.h"
#include <string>
#include "json\json.h"
#include <fstream>


Room::Room(std::string tileSheet) :
	m_TileSheet(tileSheet)
{
}

std::unique_ptr<Room> Room::jsonRoom(std::string FileName)
{
	try {
		Json::Value root;
		Json::Reader reader;
		reader.parse(std::ifstream(FileName), root, false);

		std::unique_ptr<Room> ReturnRoom(new Room(root["tilesets"][0]["image"].asString()));
		ReturnRoom->SetX(root["properties"]["pos_x"].asInt());
		ReturnRoom->SetY(root["properties"]["pos_y"].asInt());
		ReturnRoom->SetHeight(root["layers"][0]["height"].asInt());
		ReturnRoom->SetWidth(root["layers"][0]["width"].asInt());

		int mapSize = root["layers"][0]["data"].size();
		for (size_t tileNumber = 0; tileNumber < mapSize; tileNumber++)
		{
			int tileId = root["layers"][0]["data"][tileNumber].asInt();
			Point2f tilePos;
			tilePos.x = 16 * ((tileId - 1) % root["tilesets"][0]["columns"].asInt());
			tilePos.y = 16 + 16 * ((tileId - 1) / root["tilesets"][0]["columns"].asInt());

			ReturnRoom->PushBackground(
				Tile{
				tilePos,
				root["tilesets"][0]["tileproperties"][std::to_string(tileId - 1)]["Passable"].asBool() });
		}

		return ReturnRoom;
	}
	catch (std::exception e) {
		std::cout << e.what();
		return nullptr;
	}
}

void Room::SetX(int x)
{
	m_pos.x = x;
}
void Room::SetY(int y)
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

bool Room::IsOutOfBounds(float x, float y) {
	bool one = x < m_pos.x;
	bool two = y > m_pos.y;
	int test3 = m_pos.x + (m_width * 16);
	bool three = x > m_pos.x + (m_width * 16);
	int test4 = m_pos.y - (m_height * 16);
	bool four = y < m_pos.y - (m_height * 16);

	return (x< m_pos.x || y>m_pos.y || x > m_pos.x + (m_width * 16) || y < m_pos.y - (m_height * 16));
}
bool Room::IsOutOfBounds(Point2f checkPos) {
	return IsOutOfBounds(checkPos.x, checkPos.y);
}

bool Room::IsPassable(float x,float y) {
	//Assume hero can't get to the border if it's blocked on the next screen
	if (IsOutOfBounds(x, y)) return true;

	int xTile = floor(( x-m_pos.x) / 16.0f);
	int yTile = floor((y-m_pos.y) / -16.0f);
	
	int tileNumber = m_width*yTile + xTile;
	if (tileNumber >= 0 && tileNumber < m_background.size() && x<m_pos.x + m_width*16) {
		return m_background[tileNumber].m_passable;
	}
	return false;
}

void Room::DrawBackground(int globalTimer)
{
	for (size_t h = 0; h < m_height; ++h)
	{
		for (size_t w = 0; w < m_width; ++w)
		{
			int TileNum = h*m_width + w;

			//draw order
			Rectf m_Shape = Rectf(
									m_pos.x + (16 * w),
									m_pos.y - (16 * (h+1)),
									16, 16
								);

			m_TileSheet.Draw(
								m_Shape, 
								Rectf(
									m_background[TileNum].m_pos.x,
									m_background[TileNum].m_pos.y,
									16, 16)
							);
		}
	}
}

void Room::PushBackground(Tile tile)
{
	m_background.push_back(tile);
}


//Room::Room(Point2f pos,int width, int height, std::string tileString):
//	m_pos(pos.x, pos.y + (height-1)*16)
//	,m_width(width)
//	,m_height(height)
//	,m_TileSheet("Recources/Images/basicTiles.png")
//{
//	ParseTileString(tileString);
//}
//Tile Room::ParseTile(std::string tileInfo)
//{
//	int spritesPerRow = m_TileSheet.GetWidth() / 16;
//	
//	int first = tileInfo.find_first_of(",", 0);
//
//	int tileNumber = std::stoi(tileInfo.substr(0, first));
//
//	bool passable = false;
//
//	if (tileInfo.substr(first+1) == "1") {
//		passable = true;
//	}
//	return Tile(
//		Point2f(
//			16 * (tileNumber%spritesPerRow),
//			16 + 16 * (tileNumber / spritesPerRow)
//			)
//		,passable);
//
//}
//
//void Room::ParseTileString(std::string tileString)
//{
//	int LastDivider = 0;
//	char divider = '|';
//	int NextDivider = 0;
//	while (NextDivider >-1) {
//		NextDivider = tileString.find_first_of(divider, LastDivider + 1);
//
//		m_background.push_back( ParseTile(tileString.substr(LastDivider + 1, NextDivider - LastDivider - 1)));
//
//		LastDivider = NextDivider;
//	}
//}
//
