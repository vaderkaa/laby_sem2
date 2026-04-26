#pragma once

#include "SongDuration.hpp"

#include <string>

class Song
{
private:
    std::string title;
    std::string artist;
    SongDuration duration;

public:
    static unsigned int count_songs; //pole nalezy do calej klasy Song

    //KONSTRUKTORY I DESTRUKTORY
    Song();
    Song(const std::string& title, const SongDuration& duration, const std::string& artist = "Unknown"); //w hpp wartosci domyslne, od lewej nie ma, do prawej sa
    Song(const std::string& title, unsigned int minutes, unsigned int seconds = 0, const std::string& artist = "Unknown");
    ~Song();

    //GETTERY I SETTERY
    const std::string& get_title() const { return this->title; } //pierwsze const - wynik do odczytu, drugie const - metoda nic nie zmieni
    const std::string& get_artist() const { return this->artist; } //referencje!!!
    const unsigned int get_duration() const { return this->duration.get_total_seconds(); } //tutaj to pierwsze const nie jest potrzebne

    void set_title(const std::string& title) { this->title = title; }
    void set_artist(const std::string& artist) { this->artist = artist; }
    void set_duration(unsigned int seconds) { this->duration = SongDuration(0, seconds); }

    //METODY
    void print() const;

    static unsigned int get_total_songs(); //nie daje sie const, nie ma this, bo nie jest dla konkretnej piosenki
};