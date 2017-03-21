#pragma once
#include "utils.h"
#include <list>


struct Frame
{
	Frame(Point2f OriginPoint, bool HorizontalMirror = false, bool VerticalMirror = false) :
		m_pos{ OriginPoint },
		m_HMirror{ HorizontalMirror },
		m_VMirror{ VerticalMirror }
	{}

	Point2f m_pos;
	bool m_VMirror{ false };
	bool m_HMirror{ false };
};

//
//struct Animation {
//	Animation(std::list<Frame> frame_list) :
//		frames{ frame_list },
//		AnimationLength{ int(frame_list.size()) } 
//	{};
//	std::list<Frame> frames;
//	int AnimationLength;
//};
