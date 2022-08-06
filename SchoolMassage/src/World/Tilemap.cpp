#include "World/Tilemap.hpp"
#include "Common/Utils.hpp"
#include "linavg/LinaVG.hpp"

namespace SM
{
	void Tilemap::Start()
	{
		m_tiles = new Tile[m_cols * m_rows];

		Generate();
	}

	void Tilemap::Tick()
	{
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

			switch (tile->type)
			{
				case TILE_NONE:  { opts.color = LinaVG::Vec4(0,0,0,0); } break;
				case TILE_WALL:  { opts.color = LinaVG::Vec4(0.1,0.1,0.1,1); } break;
				case TILE_FLOOR: { opts.color = LinaVG::Vec4(0.9,0.9,0.9,1); } break;
			}

			int screenX = m_renderOpts.tileWidthPx * col;
			int screenY = m_renderOpts.tileHeightPx * row;
			LinaVG::DrawRect(LinaVG::Vec2(screenX, screenY), LinaVG::Vec2(screenX + m_renderOpts.tileWidthPx, screenY + m_renderOpts.tileHeightPx), opts);
		}
	}

	void Tilemap::Unload()
	{
		LOG("Tilemap unloaded!");

		if (m_tiles) {
			delete[] m_tiles;
		}
		m_tiles = nullptr;
	}

	void Tilemap::Generate()
	{
		for (int row=0; row < m_rows; row++)
		for (int col=0; col < m_cols; col++)
		{
			Tile* tile = GetTile(col, row);

			int r = GetRandom(0, 1);
			switch (r) {
				case 0: {
					tile->type = TILE_FLOOR;
					tile->isSolid = false;
					break;
				}
				default: {
					tile->type = TILE_WALL;
					tile->isSolid = true;
					break;
				}
			}
		}
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
