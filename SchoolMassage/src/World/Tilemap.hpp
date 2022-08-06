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

	struct TilemapRenderOptions
	{
		int tileWidthPx = 64;
		int tileHeightPx = 64;
	};

	class Tilemap
	{
	public:
		void Start();
		void Tick();
		void Render();
		void Unload();

		void Generate();

		Tile* GetTile(int col, int row);
		int   GetIndex(int col, int row);

	private:
		TilemapRenderOptions m_renderOpts;

		Tile* m_tiles = nullptr;
		int m_cols = 8;
		int m_rows = 8;
	};
}

#endif
