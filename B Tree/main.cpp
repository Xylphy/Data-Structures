#include <cstddef>
#include <iostream>
#include "BTree.h"

using namespace std;

auto main() -> int
{
	size_t maxChildCount = 4;
	cout << "Max Element Per Node: ";
	cin >> maxChildCount;
	auto *tree = new BTree(maxChildCount);
	int operation;
	int input;
	size_t result;

	do
	{
		cout << "Enter operation: ";
		cin >> operation;
		switch (operation)
		{
		case 1:
			cout << "Enter element to add: ";
			cin >> input;
			tree->insert(input);
			break;
		case 2:
			cout << "Enter element to search: ";
			cin >> input;
			cout << '\n';
			if (tree->search(input))
			{
				cout << input << " exists" << '\n';
			}
			else
			{
				cout << input << " does not exists" << '\n';
			}
			break;
		case 3:
			cout << "Enter element to delete: ";
			cin >> input;
			tree->deleteKey(input);
			break;
		case 4:
			cout << "Max height of the tree is: " << tree->height() << '\n';
			break;
		case 5:
			cout << "Enter element: ";
			cin >> input;
			result = tree->height(input);
			if (result == (size_t)-1)
			{
				cout << input << " does not exist\n";
			}
			else
			{
				cout << "The height of " << input << " is " << result << '\n';
			}
			break;
		case 6:
			cout << "Enter element: ";
			cin >> input;
			result = tree->depth(input);
			if (result >= 0)
			{
				cout << "The depth of the node with the element " << input << " is " << result << '\n';
			}
			else
			{
				cout << "Element not found" << '\n';
			}
			break;
		case 7:
			cout << tree;
			break;
		default:
			cout << "Invalid Operation";
			break;
		}
		cout << '\n';
	}
	while (operation != 0);
	return 0;
}
