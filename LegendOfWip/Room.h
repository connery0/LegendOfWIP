#pragma once
#include "Texture.h"
#include <memory>
#include "Tile.h"
#include <string>
#include "json\json.h"
#include <fstream>

#include "EnemyConstructor.h"
class Hero;

class Room
{
public:
	static std::unique_ptr<Room> jsonRoom(std::string FileName,std::string& Cname, const std::shared_ptr<Hero>& Hero);
	
	Room(std::string tileSheet, std::string Cname);

	Point2f GetPos();
	void SetX(float x);
	void SetY(float y);
	void SetWidth(int width);
	int GetWidth();
	void SetHeight(int height);
	int GetHeight();
	bool IsOutOfBounds(float x, float y)const;
	bool IsOutOfBounds(Point2f checkPos) const;
	bool IsOutOfBounds(Point2f checkPos, std::string& CFile) const;
	bool IsPassable(float x, float y);
	void DrawBackground(int globalTimer) const;
	void PushBackground(Tile tile);

	void PushEnemy(std::shared_ptr<Enemy> enemy);
	std::vector<std::shared_ptr<Enemy>> GetEnemyList();

	void PushBackground(std::vector<Tile> background);

	std::vector<std::shared_ptr<Enemy>>& GetMonsterVector();
	std::shared_ptr<Hero> GetHero() const;

private:
	std::vector<Tile> m_Background;
	std::vector<std::shared_ptr<Enemy>> m_Monsters;
	std::string m_MapName;
	// world coords
	Point2f m_pos;
	// In number of tiles.
	int m_height;
	int m_width;
	Texture m_TileSheet;
	std::shared_ptr<Hero> m_HeroRef;
};

