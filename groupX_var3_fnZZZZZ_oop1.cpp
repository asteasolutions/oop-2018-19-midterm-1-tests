/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 27.03.2019
//
#include <cstring>
#include <iostream>

const int MAX_STRING = 100;
const int MAX_DATE = 3 * 2 + 2 + 1;

///
/// Да се реализира клас Measurement, съхраняващ информация за едно измерване на температурата със следните атрибути:
/// - Място на измерването: символен низ с дължина до 100 символа
/// - Дата на измерването: символен низ във формат "DD/MM/YY"
/// - Измерена температура в градуси по Целзий: число с плаваща запетая
///
class Measurement {
  // моля, попълнете реализацията на класа тук
  char location[MAX_STRING];
  char date[MAX_DATE];
  double temperature;

public:
  // За класа да се реализират:
  // подходящи конструктори, например:

  // конструктор с параметри
  Measurement(char const* location = "<unknown location>", char const* date="01/01/80", double temperature = 0) {
    strncpy(this->location, location, MAX_STRING - 1);
    this->location[MAX_STRING - 1] = '\0';
    strncpy(this->date, date, MAX_DATE - 1);
    this->date[MAX_DATE - 1] = '\0';
    this->temperature = temperature;
  }

  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване

  // Методи за достъп до атрибутите
  char const* getLocation() const { return location; }
  char const* getDate()     const { return date; }
  double getTemperature()   const { return temperature; }
};

///
/// Да се реализира клас MaxTemperatures, описващ поредица от измервания на определени географски местоположения,
/// представени чрез масив от измервания, чиито максимален брой се задава при конструиране на списъка.
///

class MaxTemperatures {
  // моля, попълнете реализацията на класа тук
private:
  Measurement* items;
  unsigned capacity;
  unsigned size;

  void copy(MaxTemperatures const& other) {
    capacity = other.capacity;
    size = other.size;
    items = new Measurement[other.capacity];
    for (unsigned i = 0; i < other.size; i++) {
      items[i] = other.items[i];
    }
  }

public:
  // За класа да се реализират:
  // Конструктор с един параметър, задаващ максималния брой N на измервания, които ще бъдат съхранявани в списъка
  MaxTemperatures(unsigned N) : capacity(N), size(0) {
    items = new Measurement[capacity];
  }
  
  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване
  MaxTemperatures(MaxTemperatures const& other) {
    copy(other);
  }

  MaxTemperatures& operator=(MaxTemperatures const& other) {
    if (this != &other) {
        delete [] items;
        copy(other);
    }
    return *this;
  }

  ~MaxTemperatures() {
    delete [] items;
  }


  // Метод addMeasurement за добавяне на измерване към списъка (ако вече има измерване на същото място,
  // да остане само измерването с по-голяма стойност)
  void addMeasurement(Measurement const& item) {
    // search for existing item with the same location
    for (unsigned i = 0; i < size; i++) {
      if (strcmp(items[i].getLocation(), item.getLocation()) == 0) {
        // found it, take item with higher measurement
        if (item.getTemperature() > items[i].getTemperature())
          items[i] = item;
        return;
      }
    }
    // no existing item found, check if we have capacity to add the new one
    if (size < capacity) {
        items[size++] = item;
    } else {
        std::cerr << "List is full, cannot add more items" << std::endl;
    }
  }

  // Метод findAverage, който изчислява и връща средно аритметичното на всички запазени измервания
  double findAverage() const {
    if (size == 0) {
      std::cerr << "Cannot find average of an empty list!" << std::endl;
      return 0;
    }
    double total = 0;
    for (unsigned i = 0; i < size; i++) {
      total += items[i].getTemperature();
    }
    return total / size;
  }
  
  // Метод highestMeasurement, който връща най-високото измерване (ако има две или повече, да се върне някое
  // от тях, без значение кое)
  Measurement highestMeasurement() const {
    unsigned highestMesaurementIndex = 0;
    if (size == 0) {
        std::cerr << "List is empty, there is no highest measurement" << std::endl;
        return Measurement();
    }
    for (unsigned i = 1; i < size; i++) {
        if (items[i].getTemperature() > items[highestMesaurementIndex].getTemperature()) {
            highestMesaurementIndex = i;
        }
    }
    return items[highestMesaurementIndex];
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
#include "var3-tests.h"

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
