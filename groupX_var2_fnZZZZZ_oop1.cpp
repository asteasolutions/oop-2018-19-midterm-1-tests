/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 27.03.2019
//

///
/// Да се реализира клас Song, съхраняващ следната информация за песен:
/// - Заглавие: символен низ с дължина до 100 символа
/// - Име на изпълнител: символен низ с дължина до 100 символа
/// - Продължителност в секунди
///
class Song {
  // моля, попълнете реализацията на класа тук

public:
  // За класа да се реализират:
  // подходящи конструктори, например:

  // конструктор по подразбиране
  Song();
  // конструктор с параметри
  Song(char const* title, char const* artist, int length);

  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване

  // Методи за достъп до атрибутите
  char const* getTitle() const;
  char const* getArtist() const;
  int getLength() const;
  
  // Други помощни методи, ако е необходимо
};

///
/// Да се реализира клас Playlist, който описва списък за слушане на музика, представен чрез списък от песни,
/// чиито максимален брой се задава при конструиране на списъка.
///

class Playlist {
  // моля, попълнете реализацията на класа тук

public:
  // За класа да се реализират:
  // Конструктор с един параметър, задаващ максималния брой N на песни, които ще бъдат съхранявани в списъка
  Playlist(unsigned N);
  
  // Ако е необходимо: деструктор, конструктор за копиране, оператор за присвояване

  // Метод addSong за добавяне на песен към списъка (ако вече има песен със същото заглавие и същия изпълнител,
  // да не се добавя нова песен)
  void addSong(Song const& song);

  // Метод totalLength, който изчислява и връща общата продължителност на всички песни в списъка
  int totalLength() const;
  
  // Метод longestSong, който връща най-дългата песен (ако има две или повече най-дълги песни, да се върне
  // някоя от тях, без значение коя)
  Song longestSong() const;
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
// #include "var2-tests.h"

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
