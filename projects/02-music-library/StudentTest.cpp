#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Song.hpp"
#include "Playlist.hpp"
#include "MusicLibrary.hpp"

using namespace music;

// --- Song Class Tests ---

TEST_CASE("1. Song: check default title") {
    Song s;
    CHECK(s.getTitle() == "Unknown");
}

TEST_CASE("2. Song: check custom artist") {
    Song s("SongA", "ArtistA", 120);
    CHECK(s.getArtist() == "ArtistA");
}

TEST_CASE("3. Song: check duration storage") {
    Song s("SongA", "ArtistA", 180);
    CHECK(s.getDuration() == 180);
}

TEST_CASE("4. Song: catch negative duration error") {
    CHECK_THROWS_AS(Song("Bad", "Artist", -5), std::invalid_argument);
}

TEST_CASE("5. Song: test time format 1:05") {
    Song s("S", "A", 65);
    CHECK(s.getFormattedDuration() == "1:05");
}

TEST_CASE("6. Song: test time format with zero padding") {
    Song s("S", "A", 60);
    CHECK(s.getFormattedDuration() == "1:00");
}

TEST_CASE("7. Song: verify static count increase") {
    int start = Song::getSongCount();
    Song temp;
    CHECK(Song::getSongCount() == start + 1);
}

// --- Playlist Class Tests ---

TEST_CASE("8. Playlist: check assigned name") {
    Playlist p("MyList");
    CHECK(p.getName() == "MyList");
}

TEST_CASE("9. Playlist: new list is empty") {
    Playlist p;
    CHECK(p.isEmpty() == true);
}

TEST_CASE("10. Playlist: count grows after add") {
    Playlist p;
    p.addSong(Song("S1", "A1", 100));
    CHECK(p.getCount() == 1);
}

TEST_CASE("11. Playlist: find existing track") {
    Playlist p;
    p.addSong(Song("FindMe", "Artist", 100));
    CHECK(p.findSong("FindMe") != nullptr);
}

TEST_CASE("12. Playlist: return null for missing track") {
    Playlist p;
    CHECK(p.findSong("NotHere") == nullptr);
}

TEST_CASE("13. Playlist: index removal reduces count") {
    Playlist p;
    p.addSong(Song("S1", "A1", 100));
    p.removeSong(0);
    CHECK(p.getCount() == 0);
}

TEST_CASE("14. Playlist: total duration sum check") {
    Playlist p;
    p.addSong(Song("S1", "A1", 60));
    p.addSong(Song("S2", "A2", 40));
    CHECK(p.getTotalDuration() == 100);
}

TEST_CASE("15. Playlist: format duration under one hour") {
    Playlist p;
    p.addSong(Song("S1", "A1", 75));
    CHECK(p.getFormattedTotalDuration() == "1:15");
}

// --- MusicLibrary Class Tests ---

TEST_CASE("16. Library: check owner assignment") {
    MusicLibrary lib("Naama");
    CHECK(lib.getOwnerName() == "Naama");
}

TEST_CASE("17. Library: count playlists correctly") {
    MusicLibrary lib;
    lib.createPlaylist("P1");
    CHECK(lib.getPlaylistCount() == 1);
}

TEST_CASE("18. Library: search for playlist by name") {
    MusicLibrary lib;
    lib.createPlaylist("Rock");
    CHECK(lib.findPlaylist("Rock") != nullptr);
}

TEST_CASE("19. Library: remove playlist by string name") {
    MusicLibrary lib;
    lib.createPlaylist("Pop");
    CHECK(lib.removePlaylist("Pop") == true);
}

TEST_CASE("20. Library: catch capacity exception") {
    CHECK_THROWS_AS(MusicLibrary("Error", 0), std::invalid_argument);
}