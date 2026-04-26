#pragma once

#include "Song.hpp"

class Playlist
{
private:
    Song* songs;
    unsigned int capacity;
    unsigned int size;

public:
    Playlist(unsigned int initial_capacity = 10);

    //KONSTRUKTOR KOPIUJACY - dla I-wartosci - robie kopie, bo oryginal musi przetrwac
    Playlist(const Playlist& other); //const!!! bo tylko kopiuje

    //OPERATOR PRZYPISANIA
    Playlist& operator=(const Playlist& other); //zwraca referencje do klasy, bo oddaje dostep do tego samego obiektu, nad ktorym skonczyla pracowac

    //KONSTRUKTOR PRZENOSZACY - dla r-wartosci - robie przeniesienie, bo oryginal i tak zaraz umrze
    //uzywane, gdy TWORZE obiekt i OD RAZU przypisuje mu wynik funkcji
    Playlist(Playlist&& other); //bez const!!! bo to przenosimy, wiec dam nullptr na stare miejsce potem

    //OPERATOR PRZYPISANIA Z PRZENIESIENIEM
    //uzywane, obiekt JUZ ISTNIEJE i przypisuje mu wynik funkcji
    Playlist& operator=(Playlist&& other); //znowu bez const!!! i zwraca referencje do klasy, bo oddaje dostep do tego samego obiektu, nad ktorym skonczyla pracowac

    //DESTRUKTOR
    ~Playlist();

    //ADD SONGS
    void add_song(const Song& song);

    //GET SIZE - jest getterem, bo wyciaga wartosc prywatnego pola
    unsigned int get_size() const { return size; }

    //PRINT
    void print() const;

private:
    void resize(unsigned int new_capacity);
};