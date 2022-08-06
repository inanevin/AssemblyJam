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
		TILE_TYPE_COUNT
	};

	struct Tile
	{
		TileType type = TILE_NONE;
		bool isSolid = false;
	};

	struct TilemapRenderOptions
	{
		int tileWidthPx = 8;
		int tileHeightPx = 8;
	};

	class Tilemap
	{
	public:
		void Start();
		void Tick();
		void Render();
		void Unload();

		void Generate();
		void Randomize(); // fill with random tiles

		void SetTile(int col, int row, TileType type);
		void SetTiles(int fromCol, int fromRow, int widthCols, int heightRows, TileType type);

		Tile* GetTile(int col, int row);
		int   GetIndex(int col, int row);

	private:
		TilemapRenderOptions m_renderOpts;

		Tile* m_tiles = nullptr;
		int m_cols = 64;
		int m_rows = 64;
	};
}

#endif
