#pragma once

#include "Common/DataStructures.hpp"

#ifndef Tilemap_HPP
#define Tilemap_HPP

namespace SM
{
	enum TileType : uint32_t
	{
		TILE_NONE = 0,
		TILE_WALL,
		TILE_FLOOR,
	};

	struct Tile
	{
		TileType type = TILE_NONE;
		bool isSolid = false;
	};

	class Tilemap
	{
	public:
		void Start();
		void Tick();
		void Render();
		void Unload();

	};
}

#endif
