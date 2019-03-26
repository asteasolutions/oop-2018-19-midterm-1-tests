#include "doctest.h"
#include <cstring>

bool operator==(Song const& s1, Song const& s2) {
  return
    strcmp(s1.getTitle(), s2.getTitle()) == 0 &&
    strcmp(s1.getArtist(), s2.getArtist()) == 0 &&
    s1.getLength() == s2.getLength();
}

bool operator!=(Song const& s1, Song const& s2) {
  return !(s1 == s2);
}

TEST_CASE("Default Songs have the same values for all attributes") {
  const Song s1, s2;
  CHECK(s1 == s2);
}

TEST_CASE("Constructed Songs set values correctly") {
  const char TITLE1[] = "Bohemian Rhapsody";
  const char ARTIST1[] = "Queen";
  const char TITLE2[] = "July Morning";
  const char ARTIST2[] = "Uriah Heep";
  char TITLE[100] = "";
  strcpy(TITLE, TITLE1);
  char ARTIST[100] = "";
  strcpy(ARTIST, ARTIST1);
  const int LENGTH = 355;
  const Song si(TITLE, ARTIST, LENGTH);
  CHECK(strcmp(si.getTitle(), TITLE1) == 0);
  CHECK(strcmp(si.getArtist(), ARTIST1) == 0);
  CHECK(si.getLength() == LENGTH);
  // check if sharing is avoided
  strcpy(TITLE, TITLE2);
  strcpy(ARTIST, ARTIST2);
  CHECK(strcmp(si.getTitle(), TITLE1) == 0);
  CHECK(strcmp(si.getArtist(), ARTIST1) == 0);
}

TEST_CASE("Song is copied correctly and does not share memory") {
  const char TITLE[] = "Bohemian Rhapsody";
  const char ARTIST[] = "Queen";
  const int LENGTH = 355;
  const char TITLE2[] = "July Morning";
  const char ARTIST2[] = "Uriah Heep";
  const int LENGTH2 = 632;
  const Song* s1 = new Song(TITLE, ARTIST, LENGTH);
  const Song s2 = *s1;
  CHECK(*s1 == s2);
  CHECK(s1->getTitle() != s2.getTitle());
  CHECK(s1->getArtist() != s2.getArtist());
  delete s1;
  s1 = new Song(TITLE2, ARTIST2, LENGTH2);
  CHECK(strcmp(TITLE, s2.getTitle()) == 0);
  CHECK(strcmp(ARTIST, s2.getArtist()) == 0);
  CHECK(LENGTH == s2.getLength());
  delete s1;
}

TEST_CASE("Song is assigned correctly and does not share memory") {
  const char TITLE[] = "Bohemian Rhapsody";
  const char ARTIST[] = "Queen";
  const int LENGTH = 355;
  const char TITLE2[] = "July Morning";
  const char ARTIST2[] = "Uriah Heep";
  const int LENGTH2 = 632;
  const Song* s1 = new Song(TITLE, ARTIST, LENGTH);
  Song s2(TITLE2, ARTIST2, LENGTH2);
  s2 = *s1;
  CHECK(*s1 == s2);
  CHECK(s1->getTitle() != s2.getTitle());
  CHECK(s1->getArtist() != s2.getArtist());
  delete s1;
  s1 = new Song(TITLE2, ARTIST2, LENGTH2);
  CHECK(strcmp(TITLE, s2.getTitle()) == 0);
  CHECK(strcmp(ARTIST, s2.getArtist()) == 0);
  CHECK(LENGTH == s2.getLength());
  delete s1;
}

int testLength(int i) { return 5 * i + 107; }

Song createTestSong(int i, bool unique = true) {
   char TITLE[] = "XX Test Title";
   char ARTIST[] = "XX Test Artist";
   if (unique)
     ARTIST[0] = TITLE[0] = '0' + i / 10;
   ARTIST[1] = TITLE[1] = '0' + i % 10;
   const int LENGTH = testLength(i);
   return Song(TITLE, ARTIST, LENGTH);
 }

TEST_CASE("Playlist can hold 100 unique items") {
  const int MAX = 100;
  Playlist sl(MAX);
  CHECK(sl.totalLength() == 0);
  double checkTotalLength = 0;
  for(int i = 0; i < MAX; i++) {
    sl.addSong(createTestSong(i));
    checkTotalLength += testLength(i);
    CHECK(sl.totalLength() == checkTotalLength);
  }
}

TEST_CASE("Playlist::addSong ignores duplicate songs") {
  const int MAX = 100;
  Playlist sl(MAX);
  CHECK(sl.totalLength() == 0);
  double checkTotalLength = 0;
  for(int i = 0; i < MAX; i++) {
    sl.addSong(createTestSong(i, false));
    if (i < 10)
      checkTotalLength += testLength(i);
    CHECK(sl.totalLength() == checkTotalLength);
  }
}

TEST_CASE("Playlist::longestSong finds longest song") {
  const int MAX = 100;
  Playlist sl(MAX);
  double checkLongest = -1;
  int longestSongHash = -1;
  for(int i = 0; i < MAX; i++) {
    int hash = (31 * i + 79) % 101;
    sl.addSong(createTestSong(hash));
    if (testLength(hash) > checkLongest) {
      longestSongHash = hash;
      checkLongest = testLength(hash);
    }
    CHECK(sl.longestSong() == createTestSong(longestSongHash));
  }
}

TEST_CASE("Playlist is copied correctly and does not share memory") {
  const int MAX = 10;
  Playlist* pl1 = new Playlist(MAX * 2);
  for(int i = 0; i < MAX; i++)
    pl1->addSong(createTestSong(i));
  Playlist pl2 = *pl1;
  CHECK(pl1->totalLength() == pl2.totalLength());
  CHECK(pl1->longestSong() ==  pl2.longestSong());
  pl2.addSong(createTestSong(MAX));
  CHECK(pl1->totalLength() != pl2.totalLength());
  CHECK(pl1->longestSong() != pl2.longestSong());
  delete pl1;
  pl1 = new Playlist(MAX * 2);
  for(int i = 0; i < MAX; i++)
    pl1->addSong(createTestSong(i + MAX));
  CHECK(pl1->totalLength() != pl2.totalLength());
  CHECK(pl1->longestSong() != pl2.longestSong());
  delete pl1;
}

TEST_CASE("Playlist is assigned correctly and does not share memory") {
  const int MAX = 10;
  Playlist* pl1 = new Playlist(MAX * 2);
  for(int i = 0; i < MAX; i++)
    pl1->addSong(createTestSong(i));
  Playlist pl2(MAX);
  for(int i = 0; i < MAX; i++)
    pl2.addSong(createTestSong(i + MAX));
  pl2 = *pl1;
  CHECK(pl1->totalLength() == pl2.totalLength());
  CHECK(pl1->longestSong() == pl2.longestSong());
  pl2.addSong(createTestSong(MAX));
  CHECK(pl1->totalLength() != pl2.totalLength());
  CHECK(pl1->longestSong() != pl2.longestSong());
  delete pl1;
  pl1 = new Playlist(MAX * 2);
  for(int i = 0; i < MAX; i++)
    pl1->addSong(createTestSong(i + MAX));
  CHECK(pl1->totalLength() != pl2.totalLength());
  CHECK(pl1->longestSong() != pl2.longestSong());
  delete pl1;
}
