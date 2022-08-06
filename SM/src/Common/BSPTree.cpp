#include "Common/BSPTree.hpp"
#include "Common/Utils.hpp"

namespace SM
{
	BSPTree::BSPTree(int tilemapWidth, int tilemapHeight)
	{
		m_root = new Node(nullptr);
		m_root->m_startCol = 1;
		m_root->m_startRow = 1;
		m_root->m_width = tilemapWidth - 2;
		m_root->m_height = tilemapHeight - 2;
	}

	BSPTree::~BSPTree()
	{
		if (m_root) {
			delete m_root;
			m_root = nullptr;
		}
	}
}

namespace SM
{
	BSPTree::Node::~Node() {
		if (m_childLeft) {
			delete m_childLeft;
			m_childLeft = nullptr;
		}
		if (m_childRight) {
			delete m_childRight;
			m_childRight = nullptr;
		}
	}

	void BSPTree::Node::SplitVertically()
	{
		m_childLeft = new Node(this);
		m_childRight = new Node(this);

		m_childLeft->m_startCol    = m_startCol;
		m_childLeft->m_width       = m_width / GetRandom(2, 3);
		m_childRight->m_startCol   = m_startCol + m_childLeft->m_width + 1;
		m_childRight->m_width      = m_width - m_childLeft->m_width - 1;

		m_childLeft->m_startRow    = m_startRow;
		m_childLeft->m_height      = m_height;
		m_childRight->m_startRow   = m_startRow;
		m_childRight->m_height     = m_height;

		//LOG("V SPLIT left [at (%d,%d), size(%d,%d)] / right [at (%d,%d), size(%d,%d)]", m_childLeft->m_startCol, m_childLeft->m_startRow, m_childLeft->m_width, m_childLeft->m_height, m_childRight->m_startCol, m_childRight->m_startRow, m_childRight->m_width, m_childRight->m_height);
	}

	void BSPTree::Node::SplitHorizontally()
	{
		m_childLeft = new Node(this);
		m_childRight = new Node(this);

		m_childLeft->m_startRow   = m_startRow;
		m_childLeft->m_height     = m_height / GetRandom(2, 3);
		m_childRight->m_startRow  = m_startRow + m_childLeft->m_height + 1;
		m_childRight->m_height    = m_height - m_childLeft->m_height - 1;

		m_childLeft->m_startCol   = m_startCol;
		m_childLeft->m_width      = m_width;
		m_childRight->m_startCol  = m_startCol;
		m_childRight->m_width     = m_width;

		//LOG("H SPLIT left [at (%d,%d), size(%d,%d)] / right [at (%d,%d), size(%d,%d)]", m_childLeft->m_startCol, m_childLeft->m_startRow, m_childLeft->m_width, m_childLeft->m_height, m_childRight->m_startCol, m_childRight->m_startRow, m_childRight->m_width, m_childRight->m_height);
	}
}
