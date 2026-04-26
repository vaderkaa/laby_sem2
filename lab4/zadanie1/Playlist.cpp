#include "Song.hpp"
#include "Playlist.hpp"

#include <iostream>

//KONSTRUKTOR
Playlist::Playlist(unsigned int initial_capacity) : capacity(initial_capacity), size(0)
{
    this->songs = new Song[initial_capacity];
}

//KONSTRUKTOR KOPIUJACY
Playlist::Playlist(const Playlist& other) : capacity(other.capacity), size(other.size)
{
    this->songs = new Song[capacity];
    for(unsigned int i = 0; i < size; i++) //musi byc UNSIGNED int i, bo pole size jest tego typu!!!
        this->songs[i] = other.songs[i];
}

//OPERATOR PRZYPISANIA
Playlist& Playlist::operator=(const Playlist& other) //lewa strona to this, prawa to const
{
    if(this != &other) //this jest wskaznikiem, sprawdzamy samoprzypisanie, bo jesli to jest to samo, w tym samym miejscu w pamieci, to nic nie robimy
    {
        delete[] songs; //usuwamy this->songs, bo przypisuje cos nowego, wiec usuwam stare, juz nie bede korzystac z tego miejsca, bo moglabym cos nadpisac
        capacity = other.capacity;
        size = other.size;
        songs = new Song[capacity];
        for(unsigned int i = 0; i < size; i++)
            this->songs[i] = other.songs[i];
    }
    return *this; //zwraca caly obiekt
}

//KONSTRUKTOR PRZENOSZACY
Playlist::Playlist(Playlist&& other) : songs(other.songs), capacity(other.capacity), size(other.size) //songs i other.songs patrza w to samo miejsce, this przejmuje wladze
{
    other.songs = nullptr; //usuwamy tamto, bo juz mamy wszystko, bez new, bo tablica juz istnieje, po prostu przjelismy nad nia kontrole
    //poza tym wtedy destruktor obiektu other nie usunie nam naszej tablicy
    other.capacity = 0;
    other.size = 0;
}

//OPERATOR PRZYPISANIA Z PRZENIESIENIEM
Playlist& Playlist::operator=(Playlist&& other) //lewa strona to this, prawa to obiekt tymczasowy, ktory zaraz umrze i tak
{
    if(this != &other) //&other zwraca adres obiektu, dokladnie tak jak w zwyklym operatorze przypisania
    {
        delete[] songs; //usuwam stare, zeby wstawic nowe
        this->songs = other.songs; //uzywam tego miejsca w pamieci, bo po co kopiowac, skoro i tak zaraz umrze
        this->capacity = other.capacity;
        this->size = other.size;
        other.songs = nullptr; //usuwam to, co mialo i tak zaraz umrzec
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

//DESTRUKTOR
Playlist::~Playlist() { delete[] this->songs; }

//RESIZE - prywatna metoda
void Playlist::resize(unsigned int new_capacity)
{
    Song* new_songs = new Song[new_capacity];
    for(unsigned int i = 0; i < this->size; i++)
        new_songs[i] = this->songs[i];
    this->songs = new_songs;
    this->capacity = new_capacity;
}

//ADD SONGS
void Playlist::add_song(const Song& song)
{
    if(size == capacity)
        resize(2*capacity);
    songs[size++] = song; //postinkrementacja
}

//PRINT
void Playlist::print() const
{
    if(size == 0)
        std::cout << "Playlist is empty" << std::endl;
    else
    {
        for(unsigned int i = 0; i < size; i++)
        {
            std::cout << i + 1 << ". ";
            songs[i].print();
        }
    }
}