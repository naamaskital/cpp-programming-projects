#include "MusicLibrary.hpp"
#include <stdexcept>

namespace music {

    // Initialize global static counter
    int MusicLibrary::totalSongsAddedEver = 0;

    // Grow the playlist array
    void MusicLibrary::resize() {
        capacity *= 2;
        Playlist** nextArray = new Playlist*[static_cast<size_t>(capacity)];
        for (int i = 0; i < count; i++) {
            nextArray[i] = playlists[i];
        }
        delete[] playlists;
        playlists = nextArray;
    }

    // Default constructor
    MusicLibrary::MusicLibrary() : ownerName("Anonymous"), capacity(2), count(0) {
        playlists = new Playlist*[static_cast<size_t>(capacity)];
    }

    // Parameterized constructor
    MusicLibrary::MusicLibrary(const std::string& ownerName, int initialCapacity) 
        : ownerName(ownerName), capacity(initialCapacity), count(0) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
        playlists = new Playlist*[static_cast<size_t>(capacity)];
    }

    // Deep copy constructor
    MusicLibrary::MusicLibrary(const MusicLibrary& other) 
        : ownerName(other.ownerName), capacity(other.capacity), count(other.count) {
        playlists = new Playlist*[static_cast<size_t>(capacity)];
        for (int i = 0; i < count; i++) {
            playlists[i] = new Playlist(*(other.playlists[i]));
        }
    }

    // Copy assignment operator
    MusicLibrary& MusicLibrary::operator=(const MusicLibrary& other) {
        if (this != &other) {
            clear();
            delete[] playlists;
            ownerName = other.ownerName;
            capacity = other.capacity;
            count = other.count;
            playlists = new Playlist*[static_cast<size_t>(capacity)];
            for (int i = 0; i < count; i++) {
                playlists[i] = new Playlist(*(other.playlists[i]));
            }
        }
        return *this;
    }

    // Move constructor
    MusicLibrary::MusicLibrary(MusicLibrary&& other) noexcept 
        : ownerName(std::move(other.ownerName)), playlists(other.playlists), 
          capacity(other.capacity), count(other.count) {
        other.playlists = nullptr;
        other.count = 0;
        other.capacity = 0;
    }

    // Move assignment operator
    MusicLibrary& MusicLibrary::operator=(MusicLibrary&& other) noexcept {
        if (this != &other) {
            clear();
            delete[] playlists;
            ownerName = std::move(other.ownerName);
            playlists = other.playlists;
            capacity = other.capacity;
            count = other.count;
            other.playlists = nullptr;
            other.count = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Destructor (Cascade destruction)
    MusicLibrary::~MusicLibrary() {
        clear();
        delete[] playlists;
    }

    void MusicLibrary::setOwnerName(const std::string& name) { this->ownerName = name; }
    
    int MusicLibrary::getTotalSongsAddedEver() { 
        return totalSongsAddedEver; 
    }
    
    void MusicLibrary::incrementTotalSongs() { 
        totalSongsAddedEver++; 
    }

    // Create and return a new empty playlist
    Playlist& MusicLibrary::createPlaylist(const std::string& name) {
        if (count == capacity) {
            resize();
        }
        playlists[count] = new Playlist(name);
        return *playlists[count++];
    }

    // Add existing playlist and update stats
    void MusicLibrary::addPlaylist(const Playlist& playlist) {
        if (count == capacity) {
            resize();
        }
        playlists[count] = new Playlist(playlist);
        for(int i = 0; i < playlist.getCount(); ++i) {
            incrementTotalSongs();
        }
        count++;
    }

    // Remove playlist by index
    bool MusicLibrary::removePlaylist(int index) {
        if (index < 0 || index >= count) {
            return false;
        }
        delete playlists[index];
        for (int i = index; i < count - 1; i++) {
            playlists[i] = playlists[i + 1];
        }
        count--;
        return true;
    }

    // Remove playlist by name
    bool MusicLibrary::removePlaylist(const std::string& name) {
        for (int i = 0; i < count; i++) {
            if (playlists[i]->getName() == name) {
                return removePlaylist(i);
            }
        }
        return false;
    }

    // Search for playlist pointer
    Playlist* MusicLibrary::findPlaylist(const std::string& name) const {
        for (int i = 0; i < count; i++) {
            if (playlists[i]->getName() == name) {
                return playlists[i];
            }
        }
        return nullptr;
    }

    // Total duration across all playlists
    int MusicLibrary::getTotalDuration() const {
        int total = 0;
        for (int i = 0; i < count; i++) {
            total += playlists[i]->getTotalDuration();
        }
        return total;
    }

    // Total song count across all playlists
    int MusicLibrary::getTotalSongCount() const {
        int total = 0;
        for (int i = 0; i < count; i++) {
            total += playlists[i]->getCount();
        }
        return total;
    }

    // Clear and delete all playlist objects
    void MusicLibrary::clear() {
        for (int i = 0; i < count; i++) {
            delete playlists[i];
            playlists[i] = nullptr;
        }
        count = 0;
    }
}