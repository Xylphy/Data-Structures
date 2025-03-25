#include <vector>
#include <functional>

class DHeap
{

public:
	DHeap(size_t children, std::function<bool(size_t, size_t)> compare);

	auto insert(size_t key) -> void;
	[[nodiscard]] auto size() -> size_t;
	auto is_empty() -> bool;
	auto change_key(size_t index, size_t key) -> void;
	auto delete_key(size_t index) -> void;
	auto print() -> void;
	auto pop() -> size_t;
	auto peek() -> size_t;
	auto heapify() -> void;
	auto invert() -> void;

private:
	auto bubble_up(size_t index) -> void;
	auto bubble_down(size_t index) -> void;
	auto heapify(size_t index) -> void;

	size_t d;
	std::vector<size_t> heap;
	std::function<bool(size_t, size_t)> compare;
};
