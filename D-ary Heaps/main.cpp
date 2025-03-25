#include <memory>
#include "d_ary.hpp"

auto main() -> int
{
	std::unique_ptr<DHeap> heap = std::make_unique<DHeap>(2, std::less<>());
	heap->insert(3);
	heap->insert(2);
	heap->insert(15);
	heap->insert(5);
	heap->insert(4);
	heap->insert(45);
	heap->print();
	return 0;
}
