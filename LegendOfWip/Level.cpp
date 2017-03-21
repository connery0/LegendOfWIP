#include "stdafx.h"
#include "Level.h"


Level::Level():m_BackgrondTexture("Recources/Maps/WorldMap.png")
{
}

void Level::DrawBackground()
{
	m_BackgrondTexture.Draw();
}

