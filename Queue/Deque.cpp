#include <cstdlib>
#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node *next;
};

class LinkedList
{
	int size;
	Node *head;
	Node *tail;

public:
	LinkedList()
	{
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	void add(int data)
	{
		Node *node = new Node{.data=data, .next=nullptr};
		if (head == nullptr)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}
		size++;
	}

	void addLast(int num) { add(num); }

	void addFirst(int num)
	{
		if (head == nullptr)
		{
			add(num);
			return;
		}
		Node *node = new Node{.data = num, .next = head};
		head = node;
		size++;
	}

	auto removeFirst() -> int
	{
		if (size == 0)
		{
			return -1;
		}
		int tempInt = head->data;
		Node *temp = head;
		head = head->next;
		free(temp);
		size--;
		return tempInt;
	}

	auto get(int position) -> int
	{
		if (size == 0)
		{
			return -1;
		}
		Node *curr = head;
		int posCounter = 1;
		while (posCounter != position)
		{
			curr = curr->next;
			posCounter++;
		}
		return curr->data;
	}

	auto removeLast() -> int
	{
		if (size == 0)
		{
			return -1;
		}
		Node *curr = head;
		while (curr->next != tail && curr != tail)
		{
			curr = curr->next;
		}
		int out = tail->data;
		delete tail;
		tail = curr;
		tail->next = nullptr;
		size--;
		return out;
	}

	[[nodiscard]] auto _size() const -> int { return size; }

	void print()
	{
		Node *currentNode = head;
		while (currentNode != nullptr)
		{
			cout << currentNode->data << "->";
			currentNode = currentNode->next;
		}
		cout << '\n';
		free(currentNode);
	}
};

class Deque
{
	LinkedList *list;

public:
	Deque() { list = new LinkedList(); }

	void push_front(int num) { list->addFirst(num); }

	void push_back(int num) { list->addLast(num); }

	auto pop_front() -> int { return list->removeFirst(); }

	auto pop_back() -> int { return list->removeLast(); }

	auto peek_front() -> int { return list->get(1); }

	auto peek_back() -> int { return list->get(size()); }

	auto size() -> int { return list->_size(); }

	auto isEmpty() -> bool { return size() == 0; }

	void print() { list->print(); }
};

auto main() -> int
{
	auto *deque = new Deque();
	char operator_;
	int num;
	while (true)
	{
		cout << "Enter operation: ";
		cin >> operator_;
		switch (operator_)
		{
		case 'e':
			cin >> num;
			deque->push_front(num);
			break;
		case 'E':
			cin >> num;
			deque->push_back(num);
			break;
		case 'p':
			cout << (deque->isEmpty() ? "Queue is empty!\n"
									  : "Front of the queue is " + to_string(deque->peek_front()) + "\n");
			break;
		case 'P':
			cout << (deque->isEmpty() ? "Queue is empty!\n"
									  : "Back of the queue is " + to_string(deque->peek_back()) + "\n");
			break;
		case 'd':
			cout << "Removed number at front: " << deque->pop_front() << '\n';
			break;
		case 'D':
			cout << "Removed number at back: " << deque->pop_back() << '\n';
			break;
		case 'S':
			cout << "Size: " << deque->size() << '\n';
			break;
		case '@':
			deque->print();
			break;
		default:;
		}
		if (operator_ == 'x' || operator_ == 'X')
		{
			cout << "Exiting";
			break;
		}
	}
	return 0;
}
