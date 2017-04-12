#pragma once
#include "Texture.h"
#include <memory>

struct Tile
{
	Tile(Point2f OriginPoint, bool passable = true) :
		m_pos{ OriginPoint },
		m_passable{ passable }
	{}

	Point2f m_pos;
	bool m_passable{ true };
};



class Room
{
public:
	static std::unique_ptr<Room> jsonRoom(std::string FileName);

	Room(std::string tileSheet);

	void SetX(int x);
	void SetY(int y);
	void SetWidth(int width);
	void SetHeight(int height);
	bool IsOutOfBounds(float x, float y);
	bool IsOutOfBounds(Point2f checkPos);
	bool IsPassable(float x, float y);
	void DrawBackground(int globalTimer);
	void PushBackground(Tile tile);

private:
	std::vector<Tile> m_background;
	//real world coords
	Point2f m_pos;
	// In number of tiles.
	int m_height;
	int m_width;
	Texture m_TileSheet;
};

