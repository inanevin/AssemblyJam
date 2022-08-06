#include "Common/BSPTree.hpp"

namespace SM
{
	BSPTree::BSPTree()
	{
		m_root = new Node;
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
}
