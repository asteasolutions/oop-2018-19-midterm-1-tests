/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 27.03.2019
//

///
/// Да се напише клас ShoppingItem, съхраняващ информация за покупка в магазин:
/// - Наименование: символен низ с дължина до 100 символа
/// - Брой закупени продукти: естествено число
/// - Единична цена: положително число с плаваща запетая
///
class ShoppingItem {
  // моля, попълнете реализацията на класа тук

public:
  // За класа да се реализират:
  // подходящи конструктори, например:

  // конструктор с параметри
  ShoppingItem(char const* name, int num, double price);

  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване

  // Методи за достъп до атрибутите
  char const* getName() const;
  int getQuantity() const;
  double getUnitPrice() const;
};

///
/// Да се напише клас ShoppingList, който описва списък за пазаруване, представен чрез масив от покупки,
/// чиито максимален брой се задава при конструиране на списъка.
///

class ShoppingList {
  // моля, попълнете реализацията на класа тук

public:
  // За класа да се реализират:
  // Конструктор с един параметър, задаващ максималния брой N на покупки, които ще бъдат съхранявани в списъка
  ShoppingList(int N);
  
  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване
  
  // Метод addItem за добавяне на покупка към списъка (ако вече има покупка със същото наименование,
  // да не се добавя нова покупка, а да се увеличи броят на продуктите в старата,
  // като се използва първата получена цена)
  void addItem(ShoppingItem const& item);

  // Метод totalPrice, който изчислява и връща общата цена на всички покупки в списъка
  double totalPrice() const;
  
  // Метод mostExpensive, който връща най-скъпата покупка (ако има две или повече най-скъпи покупки,
  // да се върне някоя от тях, без значение коя)
  ShoppingItem mostExpensive() const;
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
// #include "var1-tests.h"

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