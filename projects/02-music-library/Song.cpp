#include "Song.hpp"
#include <stdexcept>
#include <iomanip>
#include <sstream>

namespace music {

    // Initialize static counter
    int Song::songCount = 0;

    // Default constructor
    Song::Song() : title("Unknown"), artist("Unknown"), durationSeconds(0) {
        songCount++;
    }

    // Parameterized constructor with validation
    Song::Song(const std::string& title, const std::string& artist, int durationSeconds) 
        : title(title), artist(artist), durationSeconds(durationSeconds) {
        if (durationSeconds < 0) {
            throw std::invalid_argument("Duration cannot be negative");
        }
        songCount++;
    }

    // Copy constructor
    Song::Song(const Song& other) 
        : title(other.title), artist(other.artist), durationSeconds(other.durationSeconds) {
        songCount++;
    }

    // Copy assignment operator
    Song& Song::operator=(const Song& other) {
        if (this != &other) {
            title = other.title;
            artist = other.artist;
            durationSeconds = other.durationSeconds;
        }
        return *this;
    }

    // Move constructor
    Song::Song(Song&& other) noexcept 
        : title(std::move(other.title)), artist(std::move(other.artist)), 
          durationSeconds(other.durationSeconds) {
        other.durationSeconds = 0;
        songCount++;
    }

    // Move assignment operator
    Song& Song::operator=(Song&& other) noexcept {
        if (this != &other) {
            title = std::move(other.title);
            artist = std::move(other.artist);
            durationSeconds = other.durationSeconds;
            other.durationSeconds = 0;
        }
        return *this;
    }

    // Destructor
    Song::~Song() {
        songCount--;
    }

    // Setters
    void Song::setTitle(const std::string& title) { this->title = title; }
    void Song::setArtist(const std::string& artist) { this->artist = artist; }
    
    void Song::setDuration(int seconds) {
        if (seconds < 0) {
            throw std::invalid_argument("Negative duration");
        }
        this->durationSeconds = seconds;
    }

    // Static count getter
    int Song::getSongCount() { 
        return songCount; 
    }

    // Formatted duration MM:SS
    std::string Song::getFormattedDuration() const {
        const int secondsInMinute = 60;
        int minutesPart = durationSeconds / secondsInMinute;
        int secondsPart = durationSeconds % secondsInMinute;
        
        std::stringstream timeStream;
        timeStream << minutesPart << ":" << std::setfill('0') << std::setw(2) << secondsPart;
        return timeStream.str();
    }
}