#pragma once
#include "Texture.h"

struct Tile
{
	Tile(Point2f OriginPoint, bool passable = true) :
		m_pos{ OriginPoint },
		m_passable{ passable }
	{}

	Point2f m_pos;
	bool m_passable{ true };
};



class Level
{
public:
	Level(Point2f pos,int width, int height, std::string tileString);


	void DrawBackground();

private:
	std::vector<Tile> m_background;
	//real world coords
	Point2f m_pos;
	// In number of tiles.
	int m_height;
	int m_width;

	Tile ParseTile(std::string tileInfo);
	void ParseTileString(std::string tileString);
	Texture m_TileSheet;

};

