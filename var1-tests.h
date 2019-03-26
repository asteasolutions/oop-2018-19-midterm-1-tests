#include "doctest.h"
#include <cstring>

bool operator==(ShoppingItem const& si1, ShoppingItem const& si2) {
  return
    strcmp(si1.getName(), si2.getName()) == 0 &&
    si1.getQuantity() == si2.getQuantity() &&
    si1.getUnitPrice() == si2.getUnitPrice();
}

bool operator!=(ShoppingItem const& si1, ShoppingItem const& si2) {
  return !(si1 == si2);
}

TEST_CASE("Default ShoppingItems have the same values for all attributes") {
  const ShoppingItem si1, si2;
  CHECK(si1 == si2);
}

TEST_CASE("Constructed ShoppingItems set values correctly") {
  const char NAME1[] = "T-shirt";
  const char NAME2[] = "Skirt";
  char NAME[100] = "";
  strcpy(NAME, NAME1);
  const int QUANTITY = 4;
  const double PRICE = 24.99;
  const ShoppingItem si(NAME, QUANTITY, PRICE);
  CHECK(strcmp(si.getName(), NAME1) == 0);
  CHECK(si.getQuantity() == QUANTITY);
  CHECK(si.getUnitPrice() == PRICE);
  // check if sharing is avoided
  strcpy(NAME, NAME2);
  CHECK(strcmp(si.getName(), NAME1) == 0);
}

TEST_CASE("ShoppingItem is copied correctly and does not share memory") {
  const char NAME[] = "T-shirt";
  const int QUANTITY = 4;
  const double PRICE = 24.99;
  const char NAME2[] = "Skirt";
  const int QUANTITY2 = 5;
  const double PRICE2 = 15.99;
  const ShoppingItem* si1 = new ShoppingItem(NAME, QUANTITY, PRICE);
  const ShoppingItem si2 = *si1;
  CHECK(strcmp(si1->getName(), si2.getName()) == 0);
  CHECK(*si1 == si2);
  CHECK(si1->getName() != si2.getName());
  delete si1;
  si1 = new ShoppingItem(NAME2, QUANTITY2, PRICE2);
  CHECK(strcmp(NAME, si2.getName()) == 0);
  CHECK(QUANTITY == si2.getQuantity());
  CHECK(PRICE == si2.getUnitPrice());
  delete si1;
}

TEST_CASE("ShoppingItem is assigned correctly and does not share memory") {
  const char NAME[] = "T-shirt";
  const int QUANTITY = 4;
  const double PRICE = 24.99;
  const char NAME2[] = "Skirt";
  const int QUANTITY2 = 5;
  const double PRICE2 = 15.99;
  const ShoppingItem* si1 = new ShoppingItem(NAME, QUANTITY, PRICE);
  ShoppingItem si2(NAME2, QUANTITY2, PRICE2);
  si2 = *si1;
  CHECK(*si1 == si2);
  CHECK(si1->getName() != si2.getName());
  delete si1;
  si1 = new ShoppingItem(NAME2, QUANTITY2, PRICE2);
  CHECK(strcmp(NAME, si2.getName()) == 0);
  CHECK(QUANTITY == si2.getQuantity());
  CHECK(PRICE == si2.getUnitPrice());
  delete si1;
}

int testQuantity(int i) { return 3 * i + 1; }

double testPrice(int i) { return (5 * i + 2 ) / 8.0; }

ShoppingItem createTestShoppingItem(int i, bool unique = true) {
   char NAME[] = "XX Test item";
   if (unique)
     NAME[0] = '0' + i / 10;
   NAME[1] = '0' + i % 10;
   const int QUANTITY = testQuantity(i);
   const double PRICE = testPrice(i);
   return ShoppingItem(NAME, QUANTITY, PRICE);
 }

TEST_CASE("ShoppingList can hold 100 unique items") {
  const int MAX = 100;
  ShoppingList sl(MAX);
  CHECK(sl.totalPrice() == 0);
  double checkTotalPrice = 0;
  for(int i = 0; i < MAX; i++) {
    sl.addItem(createTestShoppingItem(i));
    checkTotalPrice += testQuantity(i) * testPrice(i);
    CHECK(sl.totalPrice() == checkTotalPrice);
  }
}

TEST_CASE("ShoppingList::addItem increments existing ShoppingItem reusing old price") {
  const int MAX = 100;
  ShoppingList sl(MAX);
  CHECK(sl.totalPrice() == 0);
  double checkTotalPrice = 0;
  for(int i = 0; i < MAX; i++) {
    checkTotalPrice += testQuantity(i) * testPrice(i % 10);
    sl.addItem(createTestShoppingItem(i, false));
    CHECK(sl.totalPrice() == checkTotalPrice);
  }
}

TEST_CASE("ShoppingList::mostExpensive finds most expensive item") {
  const int MAX = 100;
  ShoppingList sl(MAX);
  double checkMostExpensive = -1;
  int mostExpensiveHash = -1;
  for(int i = 0; i < MAX; i++) {
    int hash = (31 * i + 79) % 101;
    sl.addItem(createTestShoppingItem(hash));
    if (testQuantity(hash) * testPrice(hash) > checkMostExpensive) {
      mostExpensiveHash = hash;
      checkMostExpensive = testQuantity(hash) * testPrice(hash);
    }
    CHECK(sl.mostExpensive() == createTestShoppingItem(mostExpensiveHash));
  }
}

TEST_CASE("ShoppingList is copied correctly and does not share memory") {
  const int MAX = 10;
  ShoppingList* sl1 = new ShoppingList(MAX * 2);
  for(int i = 0; i < MAX; i++)
    sl1->addItem(createTestShoppingItem(i));
  ShoppingList sl2 = *sl1;
  CHECK(sl1->totalPrice() == sl2.totalPrice());
  CHECK(sl1->mostExpensive() ==  sl2.mostExpensive());
  sl2.addItem(createTestShoppingItem(MAX));
  CHECK(sl1->totalPrice() != sl2.totalPrice());
  CHECK(sl1->mostExpensive() != sl2.mostExpensive());
  delete sl1;
  sl1 = new ShoppingList(MAX * 2);
  for(int i = 0; i < MAX; i++)
    sl1->addItem(createTestShoppingItem(i + MAX));
  CHECK(sl1->totalPrice() != sl2.totalPrice());
  CHECK(sl1->mostExpensive() != sl2.mostExpensive());
  delete sl1;
}

TEST_CASE("ShoppingList is assigned correctly and does not share memory") {
  const int MAX = 10;
  ShoppingList* sl1 = new ShoppingList(MAX * 2);
  for(int i = 0; i < MAX; i++)
    sl1->addItem(createTestShoppingItem(i));
  ShoppingList sl2(MAX);
  for(int i = 0; i < MAX; i++)
    sl2.addItem(createTestShoppingItem(i + MAX));
  sl2 = *sl1;
  CHECK(sl1->totalPrice() == sl2.totalPrice());
  CHECK(sl1->mostExpensive() == sl2.mostExpensive());
  sl2.addItem(createTestShoppingItem(MAX));
  CHECK(sl1->totalPrice() != sl2.totalPrice());
  CHECK(sl1->mostExpensive() != sl2.mostExpensive());
  delete sl1;
  sl1 = new ShoppingList(MAX * 2);
  for(int i = 0; i < MAX; i++)
    sl1->addItem(createTestShoppingItem(i + MAX));
  CHECK(sl1->totalPrice() != sl2.totalPrice());
  CHECK(sl1->mostExpensive() != sl2.mostExpensive());
  delete sl1;
}
