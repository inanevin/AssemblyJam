#include "World/Tilemap.hpp"
#include "Common/Utils.hpp"
#include "Common/BSPTree.hpp"

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

		// todo clear rooms

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
			opts.textureHandle = 0;
			opts.thickness = 1;

			// todo(nicolas): cleanup when necessary
			switch (tile->type)
			{
				case TILE_WALL:  { opts.color = LinaVG::Vec4(0.1,0.1,0.1,1); } break;
				case TILE_FLOOR: { opts.color = LinaVG::Vec4(0.9,0.9,0.9,1); } break;
				default:         { opts.color = LinaVG::Vec4(0,0,0,0); } break;
			}

			if (tile->DEBUG_color.w > 0.0f)
				opts.color = tile->DEBUG_color; // :bspdebug

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
		if (col >= m_cols) return; // TODO assert
		if (row >= m_rows) return; // TODO assert

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

	void Tilemap::SetTiles(int fromCol, int fromRow, int width, int height, TileType type)
	{
		for (int row=fromRow; row < fromRow+height; row++)
		for (int col=fromCol; col < fromCol+width; col++)
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

		Generate();
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
		m_tilemap.SetTiles(0,0, m_tilemap.GetWidth(),m_tilemap.GetHeight(), TILE_WALL);

		BSPTree* tree = new BSPTree(m_tilemap.GetWidth(), m_tilemap.GetHeight());

		/*

			LOL

			todo(nicolas): copypaste the working implementation from the old project loollzzz

		*/

		// PLACE ROOMS
		struct
		{
			void operator()(TilemapWorld* world, Tilemap* tilemap, BSPTree::Node* node, LinaVG::Vec4 debugColor, int depth)
			{
				const int MAX_DEPTH = 4;

				// :bspdebug
				//for (int row=node->m_startRow; row < node->m_startRow + node->m_height; row++)
				//for (int col=node->m_startCol; col < node->m_startCol + node->m_width; col++)
				//	tilemap->GetTile(col,row)->DEBUG_color = debugColor;

				if (depth < MAX_DEPTH)
				{
					if (GetRandomBool())
						node->SplitVertically();
					else
						node->SplitHorizontally();
				} else {
					auto PlaceRoom = [&]()
					{
						Room* room = new Room;

						int padding = 1;
						room->startCol = node->m_startCol + padding;
						room->startRow = node->m_startRow + padding;
						room->width    = GetRandom(3, node->m_width - padding) - 1;
						room->height   = GetRandom(3, node->m_height - padding) - 1;

						//LOG("ROOM at (%d,%d) size (%d,%d)", room->startCol, room->startRow, room->width, room->height);

						tilemap->SetTiles(room->startCol, room->startRow, room->width, room->height, TILE_FLOOR);
						//for (int row=room->startRow; row < room->startRow + room->height; row++)
						//for (int col=room->startCol; col < room->startCol + room->width; col++)
						//	tilemap->GetTile(col,row)->DEBUG_color = { 1.0f, 0.0f, 0.0f, 1.0f };

						world->m_rooms.push_back(room);
					};

					PlaceRoom();
				}

				if (node->m_childLeft)  (*this)(world, tilemap, node->m_childLeft,  { debugColor.x + 0.3f, debugColor.y, debugColor.z, 1.0f }, depth + 1);
				if (node->m_childRight) (*this)(world, tilemap, node->m_childRight, { debugColor.x, debugColor.y, debugColor.z + 0.3f, 1.0f }, depth + 1);
			}
		} recurseBSPTree;
		recurseBSPTree(this, &m_tilemap, tree->GetRoot(), { 0,0,0,1 }, 0);

		// PLACE CORRIDORS
		// todo(nicolas): connect bsp leafs

		delete tree;
		tree = nullptr;
	}
}
