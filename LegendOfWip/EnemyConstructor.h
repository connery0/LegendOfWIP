#pragma once
#include "stdafx.h"

#include "Enemy.h"
#include "Moblin_Blue.h"
#include "Moblin_Red.h"
#include "Likelike.h"
#include <memory>

class EnemyConstructor {
public:
	static std::shared_ptr<Enemy> GetEnemyByName(std::string name)
	{
		if (name == "moblin_blue") {
			return std::shared_ptr<Enemy>(new Moblin_Blue());
		}
		else if (name == "moblin_red") {
			return std::shared_ptr<Enemy>(new Moblin_Red());
		}
		else if (name == "likelike") {
			return std::shared_ptr<Enemy>(new Likelike());
		}
		return std::shared_ptr<Enemy>();
	}

	static std::shared_ptr<Enemy> GetEnemyByName(std::string name,float x,float y)
	{
		if (name == "moblin_blue") {
			return std::shared_ptr<Enemy>(new Moblin_Blue(x,y));
		}
		else if (name == "moblin_red") {
			return std::shared_ptr<Enemy>(new Moblin_Red(x,y));
		}
		else if (name == "likelike") {
			return std::shared_ptr<Enemy>(new Likelike(x,y));
		}
		return std::shared_ptr<Enemy>();
	}
};