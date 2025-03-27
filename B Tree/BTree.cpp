#include "BTree.h"

BTree::BTree(const size_t &maxChildren) : size(0), root(nullptr), capacityElemNode(maxChildren + 1) {}

void BTree::insert(const int &key)
{
	if (root == nullptr)
	{
		root = new BTreeNode{capacityElemNode, true};
		root->insert(key);
	}
	else
	{
		getGroupNode(key)->insert(key);

		while (root->parent != nullptr)
		{
			root = root->parent;
		}
	}
	size++;
}

auto BTree::getGroupNode(const int &key) const -> BTreeNode *
{
	BTreeNode *curr = root;
	while (BTreeNode *child = curr->getChild(key))
	{
		curr = child;
	}

	return curr;
}

void BTree::deleteKey(const int &key)
{
	if (root == nullptr)
	{
		return;
	}

	if (getGroupNode(key)->deleteKey(key))
	{
		size--;
	}

	if (root->isEmpty())
	{
		if (!root->isLeaf)
		{
			root = root->children[0];
			delete root->parent;
			root->parent = nullptr;
		}
		else
		{
			delete root;
			root = nullptr;
		}
	}
}

auto BTree::height() const -> size_t { return root != nullptr ? height(root->elem[0]) + 1 : 0; }

auto BTree::height(const int &key) const -> size_t
{
	BTreeNode *curr = getGroupNode(key);

	if (!curr->keyPresent(key))
	{
		return (size_t)-1;
	}

	size_t depthCounter = 0;
	while ((curr = curr->children[0]) != nullptr)
	{
		depthCounter++;
	}

	return depthCounter;
}

auto BTree::depth(const int &key) const -> size_t
{
	BTreeNode *curr = getGroupNode(key);

	if (!curr->keyPresent(key))
	{
		return (size_t)-1;
	}

	size_t depthCounter = 0;
	while ((curr = curr->parent) != nullptr)
	{
		depthCounter++;
	}

	return depthCounter;
}

auto BTree::search(const int &key) const -> bool
{
	return (root != nullptr) ? getGroupNode(key)->keyPresent(key) : false;
}

auto operator<<(std::ostream &ostream, const BTree *tree) -> std::ostream &
{
	ostream << "Size: " << tree->size << "\n";
	ostream << tree->root << '\n';
	return ostream;
}

BTree::~BTree() { delete root; }
