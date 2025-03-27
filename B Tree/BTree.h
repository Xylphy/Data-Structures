#ifndef DATA_STRUCTURES_BTREE_H
#define DATA_STRUCTURES_BTREE_H

#include <cstddef>
#include <ostream>
#include "BTreeNode.h"

class BTree
{
	size_t size;

	BTreeNode *root;

	size_t capacityElemNode;

public:
	explicit BTree(const size_t &maxChildren);

	void insert(const int &key);

	void deleteKey(const int &key);

	[[nodiscard]] auto height() const -> size_t;

	[[nodiscard]] auto height(const int &key) const -> size_t;

	[[nodiscard]] auto depth(const int &key) const -> size_t;

	[[nodiscard]] auto getGroupNode(const int &key) const -> BTreeNode *;

	~BTree();

	[[nodiscard]] auto search(const int &key) const -> bool;

	friend auto operator<<(std::ostream &ostream, const BTree *tree) -> std::ostream &;
};

auto operator<<(std::ostream &ostream, const BTree *tree) -> std::ostream &;

#endif // DATA_STRUCTURES_BTREE_H
