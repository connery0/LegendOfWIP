#include "stdafx.h"
#include "Level.h"
#include <string>



Level::Level(Point2f pos,int width, int height, std::string tileString):
	m_pos(pos.x, pos.y + (height-1)*16)
	,m_width(width)
	,m_height(height)
	,m_TileSheet("Recources/Images/basicTiles.png")
{
	ParseTileString(tileString);
}

bool Level::IsPassable(float x,float y) {
	
	int xTile = floor(( x-m_pos.x) / 16.0f);
	int yTile = floor((y-m_pos.y) / -16.0f)+1;
	
	int tileNumber = m_width*yTile + xTile;
	if (tileNumber >= 0 && tileNumber < m_background.size() && x<m_pos.x + m_width*16) {
		return m_background[tileNumber].m_passable;
	}
	return false;
}

void Level::DrawBackground()
{

	for (size_t h = 0; h < m_height; ++h)
	{
		for (size_t w = 0; w < m_width; ++w)
		{
			int TileNum = h*m_width + w;

			//draw order
			Rectf m_Shape = Rectf(m_pos.x + (16 * w), m_pos.y - (16 * h), 16, 16);
			//Rectf m_Shape = Rectf(m_pos.x + (16 * w) - 8, m_pos.y + (16 * h) - 8, 16, 16);

			//if(m_background[TileNum].m_pos.x==m_drawTile.m_pos.x && m_background[TileNum].m_pos.y == m_drawTile.m_pos.y){
			m_TileSheet.Draw(m_Shape, Rectf(m_background[TileNum].m_pos.x, m_background[TileNum].m_pos.y, 16, 16));
			//}
			//Rectf dest{m_background[h*w + w].m_pos.x,}
			//m_TileSheet.Draw()			
		}
	}
}

Tile Level::ParseTile(std::string tileInfo)
{
	int spritesPerRow = m_TileSheet.GetWidth() / 16;
	
	int first = tileInfo.find_first_of(",", 0);

	int tileNumber = std::stoi(tileInfo.substr(0, first));

	bool passable = false;

	if (tileInfo.substr(first+1) == "1") {
		passable = true;
	}
	return Tile(
		Point2f(
			16 * (tileNumber%spritesPerRow),
			16 + 16 * (tileNumber / spritesPerRow)
			)
		,passable);

}

void Level::ParseTileString(std::string tileString)
{
	int LastDivider = 0;
	char divider = '|';
	int NextDivider = 0;
	while (NextDivider >-1) {
		NextDivider = tileString.find_first_of(divider, LastDivider + 1);

		m_background.push_back( ParseTile(tileString.substr(LastDivider + 1, NextDivider - LastDivider - 1)));

		LastDivider = NextDivider;
	}
}

