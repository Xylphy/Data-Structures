#include <iostream>

#include "HashTable.h"

using namespace std;

auto main() -> int {
  auto *hashTable = new HashTable();
  char operation;
  int number;
  int number2;
  pair<int, int> pair;
  do {
    cout << "Op: ";
    cin >> operation;
    switch (operation) {
      case '+':
        cin >> number >> number2;
        pair = make_pair(number, number2);
        hashTable->insertItem(pair);
        break;
      case '-':
        cin >> number;
        hashTable->deleteItem(number);
        break;
      case 'p':
        hashTable->print();
        break;
      case 'g':
        cin >> number;
        cout << "The value of key " << number << ": ";
        hashTable->getValue(number);
      default:
        break;
    }
  } while (operation == '+' || operation == '-' || operation == 'p' ||
           operation == 'g');
  return 0;
}
