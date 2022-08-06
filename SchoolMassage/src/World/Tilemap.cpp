#include "World/Tilemap.hpp"
#include "Common/Utils.hpp"
#include "Common/BSPTree.hpp"
#include "linavg/LinaVG.hpp"

namespace SM
{
	void Tilemap::Init()
	{
		m_tiles = new Tile[m_cols * m_rows];

		Randomize();
	}
	void Tilemap::Uninit()
	{
		if (m_tiles) {
			delete[] m_tiles;
		}
		m_tiles = nullptr;

		LOG("Tilemap unloaded!");
	}

	void Tilemap::Render()
	{
		for (int row=0; row < m_rows; row++)
		for (int col=0; col < m_cols; col++)
		{
			Tile* tile = GetTile(col, row);

			LinaVG::StyleOptions opts;
			opts.isFilled = true;
			opts.textureHandle = false;

			// todo(nicolas): cleanup when necessary
			switch (tile->type)
			{
				case TILE_WALL:  { opts.color = LinaVG::Vec4(0.1,0.1,0.1,1); } break;
				case TILE_FLOOR: { opts.color = LinaVG::Vec4(0.9,0.9,0.9,1); } break;
				default:         { opts.color = LinaVG::Vec4(0,0,0,0); } break;
			}

			int screenX = m_renderOpts.tileWidthPx * col;
			int screenY = m_renderOpts.tileHeightPx * row;
			LinaVG::DrawRect(LinaVG::Vec2(screenX, screenY), LinaVG::Vec2(screenX + m_renderOpts.tileWidthPx, screenY + m_renderOpts.tileHeightPx), opts);
		}
	}

	void Tilemap::Randomize()
	{
		for (int row=0; row < m_rows; row++)
		for (int col=0; col < m_cols; col++)
			SetTile(col, row, TileType(GetRandom(TILE_NONE + 1, TILE_TYPE_COUNT - 1)));
	}

	void Tilemap::SetTile(int col, int row, TileType type)
	{
		Tile* tile = GetTile(col, row);

		// todo(nicolas): cleanup when necessary
		tile->type = type;
		switch (tile->type)
		{
			case TILE_WALL:  { tile->isSolid = true; } break;
			case TILE_FLOOR: { tile->isSolid = false; } break;
			default:         { tile->isSolid = false; } break;
		}
	}

	void Tilemap::SetTiles(int fromCol, int fromRow, int widthCols, int heightRows, TileType type)
	{
		for (int row=fromRow; row < fromRow+heightRows; row++)
		for (int col=fromCol; col < fromCol+widthCols; col++)
			SetTile(col, row, type);
	}

	Tile* Tilemap::GetTile(int col, int row)
	{
		return &m_tiles[GetIndex(col, row)];
	}

	int Tilemap::GetIndex(int col, int row)
	{
		return (row * m_cols) + col;
	}
}

namespace SM
{
	void TilemapWorld::Start()
	{
		m_tilemap.Init();
	}

	void TilemapWorld::Tick()
	{
	}

	void TilemapWorld::Render()
	{
		m_tilemap.Render();
	}

	void TilemapWorld::Unload()
	{
		m_tilemap.Uninit();
	}

	void TilemapWorld::Generate()
	{
		m_tilemap.SetTiles(0,0, m_tilemap.GetWidth()-1,m_tilemap.GetHeight(), TILE_WALL);

		BSPTree* tree = new BSPTree;
		delete tree;
		tree = nullptr;
	}
}