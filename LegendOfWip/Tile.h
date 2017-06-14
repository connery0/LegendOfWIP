#pragma once
class Tile
{

public:
	Tile(bool passable = true);
	void AddPos(Point2f originalPoint);
	int  GetFrameCount()const;
	bool  IsPassable()const;
	Point2f  GetPoint(int index)const;

private:
	int m_FrameCount;
	bool m_Passable;
	std::vector<Point2f> m_Points;
};

