#ifndef DATA_STRUCTURES_BTREENODE_H
#define DATA_STRUCTURES_BTREENODE_H

#include <ostream>

class BTreeNode final
{
	size_t size, capacity;

	int *elem;

	BTreeNode **children, *parent;

	bool isLeaf;

	BTreeNode(const size_t &capacity, const bool &isLeaf);

	BTreeNode(const size_t &capacity, BTreeNode *parent, const bool &isLeaf);

	static void printInorder(std::ostream &ostream, const BTreeNode *node, int &&level);

	[[nodiscard]] auto getChild(const int &key) const -> BTreeNode *;

	void insert(const int &key);

	void insertFromChild(const int &key, BTreeNode *newChild);

	void moveHalf(BTreeNode *node);

	void splitNode();

	[[nodiscard]] static auto getSuccessor(BTreeNode *node) -> BTreeNode *;

	[[nodiscard]] static auto getPredecessor(BTreeNode *node) -> BTreeNode *;

	auto deleteKey(const int &key) -> bool;

	[[nodiscard]] auto keyPresent(const int &key) const -> bool;

	/**
	 * this node merges with its sibling
	 * @param sibling
	 */
	void mergeChild(BTreeNode *node);

	void mergeNode(BTreeNode *src, BTreeNode *dest);

	static void mergeContents(const BTreeNode *src, BTreeNode *dest, const size_t &elementIndex);

	/**
	 * @warning Must be used for leaf nodes.
	 */
	void underFlow();

	[[nodiscard]] auto isFull() const -> bool;

	[[nodiscard]] auto isEmpty() const -> bool;

	auto removeElem(const size_t &index) -> int;

	~BTreeNode();

	friend auto operator<<(std::ostream &ostream, BTreeNode *node) -> std::ostream &;

	friend class BTree;
};

auto operator<<(std::ostream &ostream, BTreeNode *node) -> std::ostream &;

#endif // DATA_STRUCTURES_BTREENODE_H
