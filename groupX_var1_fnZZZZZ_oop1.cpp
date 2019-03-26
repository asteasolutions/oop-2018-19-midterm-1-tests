/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 27.03.2019
//

#include <cstring>
#include <iostream>

const int MAX_STRING = 100;

///
/// Да се напише клас ShoppingItem, съхраняващ информация за покупка в магазин:
/// - Наименование: символен низ с дължина до 100 символа
/// - Брой закупени продукти: естествено число
/// - Единична цена: положително число с плаваща запетая
///
class ShoppingItem {
  // моля, попълнете реализацията на класа тук
private:
  char name[MAX_STRING];
  unsigned numProducts;
  double price;

public:
  // За класа да се реализират:
  // подходящи конструктори, например:

  // конструктор с параметри
  ShoppingItem(char const* name = "<unknown>", int num = 1, double price = 1.0) {
    strncpy(this->name, name, MAX_STRING - 1);
    this->name[MAX_STRING - 1] = '\0';
    if (price <= 0) {
        std::cerr << "Price must be positive" << std::endl;
        price = 1.0;
    }
    this->price = price;
    if (num == 0) {
        std::cerr << "There must be at least one product" << std::endl;
        num = 1;
    }
    this->numProducts = num;
  }

  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване

  // Методи за достъп до атрибутите
  char const* getName() const { return name; }
  int getQuantity()     const { return numProducts; }
  double getUnitPrice() const { return price; }

  void addQuantity(int q) { numProducts += q; }

  double getCost() const { return numProducts * price; }

};

///
/// Да се напише клас ShoppingList, който описва списък за пазаруване, представен чрез масив от покупки,
/// чиито максимален брой се задава при конструиране на списъка.
///

class ShoppingList {
  // моля, попълнете реализацията на класа тук
private:
  ShoppingItem* items;
  unsigned capacity;
  unsigned size;

  void copy(ShoppingList const& other) {
    capacity = other.capacity;
    size = other.size;
    items = new ShoppingItem[other.capacity];
    for (unsigned i = 0; i < other.size; i++) {
      items[i] = other.items[i];
    }
  }

public:
  // За класа да се реализират:
  // Конструктор с един параметър, задаващ максималния брой N на покупки, които ще бъдат съхранявани в списъка
  ShoppingList(unsigned N) : capacity(N), size(0) {
    items = new ShoppingItem[capacity];
  }

  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване
  ShoppingList(ShoppingList const& other) {
    copy(other);
  }

  ShoppingList& operator=(ShoppingList const& other) {
    if (this != &other) {
        delete [] items;
        copy(other);
    }
    return *this;
  }

  ~ShoppingList() {
    delete [] items;
  }


  // Метод addItem за добавяне на покупка към списъка (ако вече има покупка със същото наименование,
  // да не се добавя нова покупка, а да се увеличи броят на продуктите в старата,
  // като се използва първата получена цена)
  void addItem(ShoppingItem const& item) {
    // search for existing item with the same name
    for (unsigned i = 0; i < size; i++) {
        if (strcmp(items[i].getName(), item.getName()) == 0) {
            // found it, only increase the number of products of the existing item
            unsigned newProducts = item.getQuantity();
            items[i].addQuantity(newProducts);
            return;
        }
    }
    // no existing item found, check if we have capacity to add the new one
    if (size < capacity) {
        items[size++] = item;
    } else {
        std::cerr << "Shopping list is full, cannot add more items" << std::endl;
    }
  }

  unsigned getNumItems() const { return size; }

  // Метод totalPrice, който изчислява и връща общата цена на всички покупки в списъка
  double totalPrice() const {
    double total = 0;
    for (unsigned i = 0; i < size; i++) {
        total += items[i].getCost();
    }
    return total;
  }

  // Метод mostExpensive, който връща най-скъпата покупка (ако има две или повече най-скъпи покупки,
  // да се върне някоя от тях, без значение коя)
  ShoppingItem mostExpensive() const {
    unsigned mostExpensiveIndex = 0;
    if (size == 0) {
        std::cerr << "List is empty, there is no most expensive item" << std::endl;
        return ShoppingItem();
    }
    for (unsigned i = 1; i < size; i++) {
        if (items[i].getCost() > items[mostExpensiveIndex].getCost()) {
            mostExpensiveIndex = i;
        }
    }
    return items[mostExpensiveIndex];
  }
};

///

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------
#include "var1-tests.h"

int main() {

  //-------------------------------------------------------------------------
  //
  // ВАЖНО: При предаване на работата във тялото на функцията main не трябва да се
  //        изпълнява нищо друго освен долния ред.
  //
  //-------------------------------------------------------------------------
  doctest::Context().run();

  return 0;
}
