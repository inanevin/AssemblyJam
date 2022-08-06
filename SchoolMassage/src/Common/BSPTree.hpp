#pragma once

#include "Common/DataStructures.hpp"

#ifndef BSPTree_HPP
#define BSPTree_HPP

namespace SM
{
	// quick, dirty and buggy shaiba

	class BSPTree
	{
	public:
		class Node
		{
		public:
			~Node();

			Node* m_parent = nullptr;
			Node* m_childLeft = nullptr;
			Node* m_childRight = nullptr;

			int m_startCol = 0;
			int m_startRow = 0;
			int m_widthCols = 0;
			int m_heightRows = 0;
		};

		BSPTree();
		~BSPTree();

	private:
		Node* m_root = nullptr;
	};
}

#endif
