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
			Node(Node* parent) : m_parent(parent) {}
			~Node();

			Node* m_parent = nullptr;
			Node* m_childLeft = nullptr;
			Node* m_childRight = nullptr;

			int m_startCol = 0;
			int m_startRow = 0;
			int m_width = 0;
			int m_height = 0;

			void SplitVertically();
			void SplitHorizontally();

			bool IsRoot() { return m_parent == nullptr; }
		};

		BSPTree(int tilemapWidth, int tilemapHeight);
		~BSPTree();

		Node* GetRoot() { return m_root; }

	private:
		Node* m_root = nullptr;
	};
}

#endif
