#pragma once

#include "Common/DataStructures.hpp"
#include "linavg/LinaVG.hpp"

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

		LinaVG::Vec4 DEBUG_color = { 0,0,0,0 };
	};

	struct TilemapRenderOptions
	{
		int tileWidthPx = 8;
		int tileHeightPx = 8;
	};

	class Tilemap
	{
	public:
		void Init();
		void Uninit();
		void Render();

		void Randomize();

		void SetTile(int col, int row, TileType type);
		void SetTiles(int fromCol, int fromRow, int width, int height, TileType type);

		Tile* GetTile(int col, int row);
		int   GetIndex(int col, int row);

		int GetWidth() { return m_cols; }
		int GetHeight() { return m_rows; }

	private:
		TilemapRenderOptions m_renderOpts;

		Tile* m_tiles = nullptr;
		int m_cols = 64;
		int m_rows = 64;
	};

	class TilemapWorld
	{
	public:
		struct Room {
			int startCol = 0;
			int startRow = 0;
			int width = 0;
			int height = 0;
		};

		void Start();
		void Tick();
		void Render();
		void Unload();

		void Generate();

		Tilemap& GetTilemap();

	private:
		Tilemap m_tilemap;

		vector<Room*> m_rooms;
	};
}

#endif
