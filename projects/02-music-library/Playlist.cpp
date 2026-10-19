#include "Playlist.hpp"
#include <stdexcept>
#include <iomanip>
#include <sstream>

namespace music {

    // Initialize static counter
    int Playlist::totalPlaylistsCreated = 0;

    // Internal helper to resize the dynamic array
    void Playlist::resize() {
        capacity *= 2;
        Song** nextArray = new Song*[static_cast<size_t>(capacity)];
        for (int i = 0; i < count; i++) {
            nextArray[i] = songs[i];
        }
        delete[] songs;
        songs = nextArray;
    }

    // Default constructor
    Playlist::Playlist() : name("Untitled"), capacity(4), count(0) {
        songs = new Song*[static_cast<size_t>(capacity)];
        totalPlaylistsCreated++;
    }

    // Parameterized constructor
    Playlist::Playlist(const std::string& name, int initialCapacity) 
        : name(name), capacity(initialCapacity), count(0) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
        songs = new Song*[static_cast<size_t>(capacity)];
        totalPlaylistsCreated++;
    }

    // Copy constructor (Deep Copy)
    Playlist::Playlist(const Playlist& other) 
        : name(other.name), capacity(other.capacity), count(other.count) {
        songs = new Song*[static_cast<size_t>(capacity)];
        for (int i = 0; i < count; i++) {
            songs[i] = new Song(*(other.songs[i]));
        }
        totalPlaylistsCreated++;
    }

    // Copy assignment operator
    Playlist& Playlist::operator=(const Playlist& other) {
        if (this != &other) {
            clear();
            delete[] songs;
            name = other.name;
            capacity = other.capacity;
            count = other.count;
            songs = new Song*[static_cast<size_t>(capacity)];
            for (int i = 0; i < count; i++) {
                songs[i] = new Song(*(other.songs[i]));
            }
        }
        return *this;
    }

    // Move constructor
    Playlist::Playlist(Playlist&& other) noexcept 
        : name(std::move(other.name)), songs(other.songs), 
          capacity(other.capacity), count(other.count) {
        other.songs = nullptr;
        other.count = 0;
        other.capacity = 0;
        totalPlaylistsCreated++;
    }

    // Move assignment operator
    Playlist& Playlist::operator=(Playlist&& other) noexcept {
        if (this != &other) {
            clear();
            delete[] songs;
            name = std::move(other.name);
            songs = other.songs;
            capacity = other.capacity;
            count = other.count;
            other.songs = nullptr;
            other.count = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Destructor
    Playlist::~Playlist() {
        clear();
        delete[] songs;
    }

    void Playlist::setName(const std::string& name) { this->name = name; }
    
    int Playlist::getTotalPlaylistsCreated() { 
        return totalPlaylistsCreated; 
    }

    // Add a new song copy to the array
    void Playlist::addSong(const Song& song) {
        if (count == capacity) {
            resize();
        }
        songs[count] = new Song(song);
        count++;
    }

    // Remove song by index and shift array
    bool Playlist::removeSong(int index) {
        if (index < 0 || index >= count) {
            return false;
        }
        delete songs[index];
        for (int i = index; i < count - 1; i++) {
            songs[i] = songs[i + 1];
        }
        count--;
        return true;
    }

    // Remove song by matching title and artist
    bool Playlist::removeSong(const std::string& title, const std::string& artist) {
        for (int i = 0; i < count; i++) {
            if (songs[i]->getTitle() == title && songs[i]->getArtist() == artist) {
                return removeSong(i);
            }
        }
        return false;
    }

    // Search for a song pointer by title
    Song* Playlist::findSong(const std::string& title) const {
        for(int i = 0; i < count; i++) {
            if(songs[i]->getTitle() == title) {
                return songs[i];
            }
        }
        return nullptr;
    }

    // Sum of all song durations
    int Playlist::getTotalDuration() const {
        int totalSeconds = 0;
        for (int i = 0; i < count; i++) {
            totalSeconds += songs[i]->getDuration();
        }
        return totalSeconds;
    }

    // Format duration as H:MM:SS or M:SS
    std::string Playlist::getFormattedTotalDuration() const {
        int totalSeconds = getTotalDuration();
        const int secondsInHour = 3600;
        const int secondsInMinute = 60;
        
        int hoursPart = totalSeconds / secondsInHour;
        int minutesPart = (totalSeconds % secondsInHour) / secondsInMinute;
        int secondsPart = totalSeconds % secondsInMinute;
        
        std::stringstream timeStream;
        if (hoursPart > 0) {
            timeStream << hoursPart << ":" << std::setfill('0') << std::setw(2) << minutesPart 
                       << ":" << std::setfill('0') << std::setw(2) << secondsPart;
        } else {
            timeStream << minutesPart << ":" << std::setfill('0') << std::setw(2) << secondsPart;
        }
        return timeStream.str();
    }

    // Clear all songs from memory
    void Playlist::clear() {
        for (int i = 0; i < count; i++) {
            delete songs[i];
            songs[i] = nullptr;
        }
        count = 0;
    }
}