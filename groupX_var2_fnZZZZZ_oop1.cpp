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
/// Да се реализира клас Song, съхраняващ следната информация за песен:
/// - Заглавие: символен низ с дължина до 100 символа
/// - Име на изпълнител: символен низ с дължина до 100 символа
/// - Продължителност в секунди
///
class Song {
  // моля, попълнете реализацията на класа тук
  char title[MAX_STRING];
  char artist[MAX_STRING];
  unsigned length;

public:
  // За класа да се реализират:
  // подходящи конструктори, например:

  // конструктор с параметри
  Song(char const* title = "<unknown title>", char const* artist = "<unknown artist>", int length = 1) {
    strncpy(this->title, title, MAX_STRING - 1);
    this->title[MAX_STRING - 1] = '\0';
    strncpy(this->artist, artist, MAX_STRING - 1);
    this->artist[MAX_STRING - 1] = '\0';
    if (length <= 0) {
        std::cerr << "Length must be positive" << std::endl;
        length = 1;
    }
    this->length = length;
  }

  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване

  // Методи за достъп до атрибутите
  char const* getTitle() const { return title; }
  char const* getArtist() const { return artist; }
  int getLength() const { return length; }
};

///
/// Да се реализира клас Playlist, който описва списък за слушане на музика, представен чрез списък от песни,
/// чиито максимален брой се задава при конструиране на списъка.
///

class Playlist {
  // моля, попълнете реализацията на класа тук
private:
  Song* items;
  unsigned capacity;
  unsigned size;

  void copy(Playlist const& other) {
    capacity = other.capacity;
    size = other.size;
    items = new Song[other.capacity];
    for (unsigned i = 0; i < other.size; i++) {
      items[i] = other.items[i];
    }
  }

public:
  // За класа да се реализират:
  // Конструктор с един параметър, задаващ максималния брой N на песни, които ще бъдат съхранявани в списъка
  Playlist(unsigned N)  : capacity(N), size(0) {
    items = new Song[capacity];
  }

  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване
  Playlist(Playlist const& other) {
    copy(other);
  }

  Playlist& operator=(Playlist const& other) {
    if (this != &other) {
        delete [] items;
        copy(other);
    }
    return *this;
  }

  ~Playlist() {
    delete [] items;
  }

  // Метод addSong за добавяне на песен към списъка (ако вече има песен със същото заглавие и същия изпълнител,
  // да не се добавя нова песен)
  void addSong(Song const& item) {
    // search for existing item with the same name
    for (unsigned i = 0; i < size; i++) {
        if (strcmp(items[i].getTitle(), item.getTitle()) == 0 &&
            strcmp(items[i].getArtist(), item.getArtist()) == 0 ) {
            // found it, ignore
            return;
        }
    }
    // no existing item found, check if we have capacity to add the new one
    if (size < capacity) {
        items[size++] = item;
    } else {
        std::cerr << "Playlist is full, cannot add more items" << std::endl;
    }
  }

  // Метод totalLength, който изчислява и връща общата продължителност на всички песни в списъка
  int totalLength() const {
    int total = 0;
    for (unsigned i = 0; i < size; i++) {
      total += items[i].getLength();
    }
    return total;
  }

  
  // Метод longestSong, който връща най-дългата песен (ако има две или повече най-дълги песни, да се върне
  // някоя от тях, без значение коя)
  Song longestSong() const {
    unsigned longestSongIndex = 0;
    if (size == 0) {
        std::cerr << "List is empty, there is no longest song" << std::endl;
        return Song();
    }
    for (unsigned i = 1; i < size; i++) {
        if (items[i].getLength() > items[longestSongIndex].getLength()) {
            longestSongIndex = i;
        }
    }
    return items[longestSongIndex];
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
#include "var2-tests.h"

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
