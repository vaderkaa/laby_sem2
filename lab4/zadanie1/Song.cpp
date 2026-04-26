#include "Song.hpp"
#include "SongDuration.hpp"

#include <iostream>

unsigned int Song::count_songs = 0;

Song::Song() : title("Untitled"), artist("Unknown"), duration(0, 0) { Song::count_songs++; } //kolejnosc na liscie inicjalizacyjnej musi byc taka sama jak w klasie!!!
Song::Song(const std::string& title, const SongDuration& duration, const std::string& artist) : title(title), artist(artist), duration(duration) { Song::count_songs++; }
Song::Song(const std::string& title, unsigned int minutes, unsigned int seconds, const std::string& artist) : title(title), artist(artist), duration(minutes, seconds) { Song::count_songs++; }
Song::~Song() { Song::count_songs--; } //tu tez zmieniamy statica!!!

void Song::print() const
{
    std::cout << title << ", Artist: " << artist << " [" << duration.get_formatted() << "]" << std::endl;
}

unsigned int Song::get_total_songs() //tu juz nie ma static, bo kompilator sam wie, ze to jest static
{
    return Song::count_songs;
}