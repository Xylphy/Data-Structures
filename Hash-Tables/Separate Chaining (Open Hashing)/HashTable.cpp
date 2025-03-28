#include "HashTable.h"

#include <cmath>

#include "AVLTree.h"

// Constructor
HashTable::HashTable()
    : array(new AVLTree*[1]), stack(new Stack()), size(0), capacity(1) {
  for (int i = 0; i < 1; ++i) {
    array[i] = new AVLTree();
  }
  stack->push(1);
}

// Function for finding prime. We will skip prime number 2 for now
auto HashTable::isPrime(size_t value) -> bool {
  for (size_t i = 2; i <= value / 2; i++) {
    if (value % i == 0) {
      return false;
    }
  }
  return true;
}

// Resize if it reaches the upper bound and lower bound of load factor
void HashTable::reHash() {
  constexpr float UPPER_BOUND = 0.75;
  if (static_cast<float>(size) >=
      ceil(static_cast<double>(capacity) * UPPER_BOUND)) {
    // If the load factor reaches the upper bound ceiling, we will push the
    // current capacity to the stack and find new prime number for the capacity
    stack->push((int)capacity);

    pair<int, int>* newArray = getAllElements();

    while (!isPrime((capacity += 2))) {
    }

    array = (AVLTree**)realloc(array, sizeof(AVLTree*) * capacity);
    for (size_t i = 0; i < capacity; ++i) {
      array[i] = new AVLTree();
    }

    // Reinsert the elements
    for (size_t i = 0; i < size; ++i) {
      array[hashFunction(newArray[i].first)]->insertNode(newArray[i]);
    }

    delete newArray;
  } else if (!stack->isEmpty() && size <= (size_t)stack->peek()) {
    // If the size is less than or equal to the previous prime number, we'll
    // resize the capacity to the previous prime number
    pair<int, int>* newArray = getAllElements();

    capacity = (size_t)stack->pop();

    array = (AVLTree**)realloc(array, sizeof(AVLTree*) * capacity);

    // Reinsert the elements
    for (size_t i = 0; i < size; ++i) {
      array[hashFunction(newArray[i].first)]->insertNode(newArray[i]);
    }

    delete newArray;
  }
}

// Function for getting all the elements of the hashtable and return an array of
// pairs
auto HashTable::getAllElements() -> pair<int, int>* {
  auto* newArray = new pair<int, int>[size];

  size_t index = 0;
  for (size_t i = 0; i < capacity; ++i) {
    while (!array[i]->isEmpty()) {
      newArray[index++] = array[i]->removeRoot();
    }
  }

  return newArray;
}

auto HashTable::hashFunction(int value) const -> int {
  return value % (int)capacity;
}

// Function for inserting elements
void HashTable::insertItem(pair<int, int>& keyValue) {
  Node* searchedNode =
      array[hashFunction(keyValue.first)]->searchNode(keyValue.first);
  if (searchedNode != nullptr) {
    searchedNode->pair = keyValue;
  } else {
    reHash();
    array[hashFunction(keyValue.first)]->insertNode(keyValue);
    size++;
  }
}

// Function for deleting elements by key
void HashTable::deleteItem(int key) {
  if (array[hashFunction(key)]->searchNode(key) != nullptr) {
    array[hashFunction(key)]->deleteNode(key);
    size--;
    reHash();
  } else {
    cout << "Element does not exist\n";
  }
}

void HashTable::print() {
  cout << "\nSize: " << size << "\nCapacity: " << capacity << "\n\n";

  for (size_t i = 0; i < capacity; ++i) {
    cout << "table[" << i << "] --> ";
    array[i]->printTree();
    cout << '\n';
  }
}

void HashTable::getValue(int key) {
  Node* node = array[hashFunction(key)]->searchNode(key);
  cout << ((node != nullptr) ? to_string(node->pair.second) : "(None) ")
       << '\n';
}