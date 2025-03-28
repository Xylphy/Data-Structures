#ifndef HASH_TABLES_HASHTABLE_H
#define HASH_TABLES_HASHTABLE_H

#include <cstddef>

#include "AVLTree.h"
#include "Stack.h"

class HashTable {
  AVLTree** array;        // An array of pointers to nodes
  Stack* stack;           // Used for traversing between prime numbers
  size_t size, capacity;  // Current size and maximum capacity
  [[nodiscard]] auto hashFunction(int) const -> int;
  void reHash();
  auto getAllElements() -> pair<int, int>*;
  static auto isPrime(size_t value) -> bool;

 public:
  HashTable();
  void insertItem(pair<int, int>&);
  void deleteItem(int);
  void print();
  void getValue(int key);
};

#endif  // HASH_TABLES_HASHTABLE_H