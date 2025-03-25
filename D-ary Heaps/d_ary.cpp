#include "d_ary.hpp"
#include <print>

DHeap::DHeap(size_t children, std::function<bool(size_t, size_t)> compare) : d(children), compare(std::move(compare)) {}

auto DHeap::insert(size_t key) -> void
{
	heap.push_back(key);
	bubble_up(heap.size() - 1);
}

auto DHeap::size() -> size_t { return heap.size(); }

auto DHeap::is_empty() -> bool { return size() == 0; }

auto DHeap::change_key(size_t index, size_t key) -> void
{
	heap[index] = key;
	heapify(index);
}

auto DHeap::delete_key(size_t index) -> void
{
	heap[index] = heap.back();
	heap.pop_back();
	heapify(index);
}

auto DHeap::print() -> void
{
	for (const size_t &element : heap)
	{
		std::print("{} ", element);
	}
	std::print("\n");
}

auto DHeap::pop() -> size_t
{
	size_t top_element = peek();
	std::swap(heap[0], heap[heap.size() - 1]);
	heap.pop_back();
	bubble_down(0);

	return top_element;
}

auto DHeap::peek() -> size_t { return heap[0]; }

auto DHeap::heapify() -> void
{
	for (size_t i = size() / d; i >= 0; i--)
	{
		bubble_down(i);
	}
}

auto DHeap::invert() -> void
{
	if (compare.target_type() == typeid(std::less<>))
	{
		compare = std::greater<>();
	}
	else
	{
		compare = std::less<>();
	}

	heapify();
}

auto DHeap::bubble_up(size_t index) -> void
{
	size_t parent = (index - 1) / d;

	while (index > 0 && compare(heap[index], heap[parent]))
	{
		std::swap(heap[parent], heap[index]);
		index = parent;
		parent = (index - 1) / d;
	}
}

auto DHeap::bubble_down(size_t index) -> void
{
	size_t smallest = index;
	size_t first_child = (d * index) + 1;
	size_t heap_size = size();

	for (size_t i = 0; i < d; i++, first_child++)
	{
		if (first_child < heap_size && compare(heap[first_child], heap[smallest]))
		{
			smallest = first_child;
		}
	}

	if (smallest != index)
	{
		std::swap(heap[index], heap[smallest]);
		bubble_down(smallest);
	}
}

auto DHeap::heapify(size_t index) -> void
{
	bubble_up(index);
	bubble_down(index);
}
