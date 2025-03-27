#include "BTreeNode.h"
#include <cstddef>
#include <iostream>

BTreeNode::BTreeNode(const size_t &capacity, const bool &isLeaf) :
	size(0), capacity(capacity - 1), elem(new int[capacity - 1]), children(new BTreeNode *[capacity]), parent(nullptr),
	isLeaf(isLeaf)
{
	for (size_t i = 0; i < capacity; ++i)
	{
		children[i] = nullptr;
	}
}

BTreeNode::BTreeNode(const size_t &capacity, BTreeNode *parent, const bool &isLeaf) :
	size(0), capacity(capacity - 1), elem(new int[capacity - 1]), children(new BTreeNode *[capacity]), parent(parent),
	isLeaf(isLeaf)
{
	for (size_t i = 0; i < capacity; ++i)
	{
		children[i] = nullptr;
	}
}

auto BTreeNode::isFull() const -> bool { return size == capacity; }

void BTreeNode::insert(const int &key)
{
	size_t i;
	for (i = size - 1; i >= 0 && elem[i] > key; i--)
	{
		elem[i + 1] = elem[i];
	}

	elem[++i] = key;
	size++;

	if (isFull())
	{
		splitNode();
	}
}

auto BTreeNode::getChild(const int &key) const -> BTreeNode *
{
	size_t i;
	for (i = 0; i < size; i++)
	{
		if (elem[i] > key)
		{
			return children[i];
		}
		if (elem[i] == key)
		{
			return nullptr;
		}
	}
	return children[i];
}

void BTreeNode::splitNode()
{
	auto *newSibling = new BTreeNode(capacity + 1, isLeaf);
	BTreeNode *parentNode;

	if (parent != nullptr)
	{
		parentNode = parent;
	}
	else
	{
		parent = parentNode = new BTreeNode(capacity + 1, false);
		parentNode->children[0] = this;
	}

	newSibling->parent = parentNode;
	parentNode->insertFromChild(removeElem(capacity / 2), newSibling);
	moveHalf(newSibling);

	if (parentNode->isFull())
	{
		parentNode->splitNode();
	}
}

void BTreeNode::insertFromChild(const int &key, BTreeNode *newChild)
{
	size_t i;
	for (i = size - 1; i >= 0 && elem[i] > key; i--)
	{
		elem[i + 1] = elem[i];
		children[i + 2] = children[i + 1];
	}

	elem[++i] = key;
	children[i + 1] = newChild;
	size++;
}

auto BTreeNode::removeElem(const size_t &index) -> int
{
	const int element = elem[index];
	for (size_t i = index + 1; i < size; i++)
	{
		elem[i - 1] = elem[i];
	}
	size--;
	return element;
}

void BTreeNode::mergeContents(const BTreeNode *src, BTreeNode *dest, const size_t &elementIndex)
{

	size_t &destSize = dest->size;
	int *destElem = dest->elem;
	size_t index;
	BTreeNode **srcChildren = src->children;
	BTreeNode **destChildren = dest->children;
	BTreeNode *parent = src->parent;
	const size_t &srcSize = src->size;
	const int *srcElem = src->elem;
	bool isLeaf = dest->isLeaf;

	destElem[destSize++] = parent->removeElem(elementIndex);

	for (index = 0; index < srcSize; index++)
	{
		destElem[destSize] = srcElem[index];
		if (!isLeaf)
		{
			destChildren[destSize++] = srcChildren[index];
			srcChildren[index]->parent = dest;
		}
		else
		{
			destSize++;
		}
	}

	if (!isLeaf)
	{
		destChildren[destSize] = srcChildren[index];
		srcChildren[index]->parent = dest;
	}

	if (dest->isFull())
	{
		dest->splitNode();
	}

	delete src;
}

void BTreeNode::mergeNode(BTreeNode *src, BTreeNode *dest)
{
	const size_t &parentSize = parent->size;
	BTreeNode **parentChildren = parent->children;

	for (size_t i = 0; i <= parentSize; i++)
	{
		if (parentChildren[i] == src)
		{
			const size_t index = i + 1 <= parentSize && parentChildren[i + 1] == dest ? i : i - 1;
			for (++i; i <= parentSize; i++)
			{
				parentChildren[i - 1] = parentChildren[i];
			}
			mergeContents(src, dest, index);
		}
	}
}

void BTreeNode::mergeChild(BTreeNode *node)
{
	BTreeNode *parentNode = parent;

	// removing of variable node
	if (node->elem[0] < elem[0])
	{
		mergeNode(this, node);
	}

	// removing of this node
	else
	{
		mergeNode(node, this);
	}

	if (parentNode->isEmpty())
	{

		parentNode->underFlow();
	}
}

void BTreeNode::underFlow()
{
	if (parent == nullptr)
	{
		return;
	}

	const size_t parentSize = parent->size;
	BTreeNode **parentChildren = parent->children;

	for (size_t i = 0; i <= parentSize; i++)
	{
		if (parentChildren[i] == this)
		{
			BTreeNode *sibling;
			bool isLeft;

			if (i + 1 <= parentSize)
			{
				isLeft = false;
				sibling = parentChildren[i + 1];
			}
			else
			{
				isLeft = true;
				sibling = parentChildren[i - 1];
			}

			if (sibling->size < capacity / 2 && i - 1 >= 0 && !isLeft)
			{
				sibling = parentChildren[i - 1];
				isLeft = true;
			}

			if (sibling->size < capacity / 2 || !isLeaf)
			{
				mergeChild(sibling);
			}
			else if (isLeft)
			{
				int &parentElement = parent->elem[i - 1];
				insert(parentElement);
				parentElement = sibling->removeElem(sibling->size - 1);
			}
			else
			{
				int &parentElement = parent->elem[i];
				insert(parentElement);
				parentElement = sibling->removeElem(0);
			}

			return;
		}
	}
}

auto BTreeNode::deleteKey(const int &key) -> bool
{
	for (size_t i = 0; i < size; i++)
	{
		if (elem[i] == key)
		{
			if (isLeaf)
			{
				for (++i; i < size; i++)
				{
					elem[i - 1] = elem[i];
				}

				size--;
				if (isEmpty())
				{
					underFlow();
				}
			}
			else
			{
				BTreeNode *substitute = getPredecessor(children[i]);
				elem[i] = substitute->removeElem(substitute->size - 1);
			}

			return true;
		}
	}
	return false;
}

auto BTreeNode::getSuccessor(BTreeNode *node) -> BTreeNode *
{
	while (!node->isLeaf)
	{
		node = node->children[0];
	}

	return node;
}

auto BTreeNode::getPredecessor(BTreeNode *node) -> BTreeNode *
{
	while (!node->isLeaf)
	{
		node = node->children[node->size];
	}

	return node;
}

void BTreeNode::printInorder(std::ostream &ostream, const BTreeNode *node, int &&level)
{
	if (node != nullptr)
	{
		size_t index;
		const size_t &nodeSize = node->size;
		for (index = 0; index < nodeSize; index++)
		{
			printInorder(ostream, node->children[index], level + 1);
			ostream << " " << level << "| " << node->elem[index] << " ";
		}

		printInorder(ostream, node->children[index], level + 1);
		ostream << '\n';
	}
}

auto BTreeNode::keyPresent(const int &key) const -> bool
{
	for (size_t i = 0; i < size; i++)
	{
		if (elem[i] == key)
		{
			return true;
		}
	}

	return false;
}

auto BTreeNode::isEmpty() const -> bool { return size == 0; }

void BTreeNode::moveHalf(BTreeNode *node)
{
	size_t index;
	size_t childIndex;
	int *nodeElem = node->elem;
	BTreeNode **nodeChildren = node->children;

	for (index = capacity / 2, childIndex = 0; index < size; index++, childIndex++)
	{
		nodeElem[childIndex] = elem[index];
		if (!isLeaf)
		{
			nodeChildren[childIndex] = children[index + 1];
			nodeChildren[childIndex]->parent = node;
		}
	}

	if (!isLeaf)
	{
		nodeChildren[childIndex] = children[index + 1];
		nodeChildren[childIndex]->parent = node;
	}

	node->size = capacity - (size = capacity / 2) - 1;
}

BTreeNode::~BTreeNode()
{
	delete[] elem;
	delete[] children;
}

auto operator<<(std::ostream &ostream, BTreeNode *node) -> std::ostream &
{
	BTreeNode::printInorder(ostream, node, 1);
	return ostream;
}
