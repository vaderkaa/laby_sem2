#include "SongDuration.hpp"
#include "Song.hpp"
#include "Playlist.hpp"

#include <iostream>
#include <vector>
#include <memory>

int main() {

    std::cout << "*************** PART 1 (SongDuration) ***************\n\n";

    SongDuration duration1(0, 125);  // 2m 5s
    SongDuration duration2(3, 98);  // 4m 38s

    std::cout << "Duration 1: " << duration1.get_formatted() << " (" << duration1.get_total_seconds() << "s)\n";

    std::cout << "Duration 2: " << duration2.get_formatted() << " (" << duration2.get_total_seconds() << "s)\n";

    std::cout << "\n*************** PART 2 (Song) ***************\n\n";

    Song song1;
    Song song2("Recursion Anthem", duration2, "Stack Overflow");
    Song song3("Binary Love", 3, 45, "The Algorithms");
    {
        Song song4("Segmentation Fault", duration1);
        Song song5("Git Happens", 2);

        song1.print();
        song2.print();
        song3.print();
        song4.print();
        song5.print();
        std::cout << "\nTotal songs: " << Song::get_total_songs() << std::endl;
    }
    std::cout << "\nTotal songs: " << Song::get_total_songs() << std::endl << std::endl;

    song1.set_title("Polymorphic Dreams");
    song1.set_artist("Object-Oriented Orchestra");
    song1.set_duration(300);
    std::cout << "get_title(): " << song1.get_title() << std::endl;
    std::cout << "get_artist(): " << song1.get_artist() << std::endl;
    std::cout << "get_duration(): " << song1.get_duration() << std::endl;

    std::cout << "\n*************** PART 3 (Playlist) ***************\n\n";

    Playlist playlist;
    playlist.add_song(song1);
    playlist.add_song(song2);
    playlist.add_song(song3);

    std::cout << "Playlist size: " << playlist.get_size() << std::endl;
    playlist.print();

    Playlist playlist_copy1(playlist);
    std::cout << "\nPlaylist copy (constructor):" << std::endl;
    playlist_copy1.print();

    Playlist playlist_copy2 = playlist;
    playlist_copy2 = playlist;
    std::cout << "\nPlaylist copy (assignment):" << std::endl;
    playlist_copy2.print();

    Playlist playlist_move1(std::move(playlist_copy1));
    std::cout << "\nPlaylist moved (constructor):" << std::endl;
    playlist_move1.print();
    std::cout << "\nMoved from:\n";
    playlist_copy1.print();

    Playlist playlist_move2;
    playlist_move2 = std::move(playlist_copy2);
    std::cout << "\nPlaylist moved (assignment):" << std::endl;
    playlist_move2.print();
    std::cout << "\nMoved from:\n";
    playlist_copy2.print();

    std::cout << "\n*************** PART 4 (Smart Pointers) ***************\n\n";

    struct Dummy {
        char id;
        Dummy(char id) : id(id) {
            std::cout << id << " created" << std::endl;
        }
        ~Dummy() {
            std::cout << id << " destroyed" << std::endl;
        }
    };

    //INTELIGENTNE WSKAZNIKI - zamiast pilnowac pamieci samodzielnie, obiekty robia to za nas - nie ma wyciekow pamieci lub podwojnych zwolnien
    //smart pointers to opakowania na surowe wskazniki - jesli opakowanie umiera, to sprzata swoja zawartosc

    //std::shared_ptr - kilka czesci programu ma dostep do tego samego obiektu i zadna nie jest ta "glowna"
    // [TODO 1]: Zdefiniuj dwa puste wektory przechowujace shared_ptr do Dummy
    
    //przed klamerka beda zyly dluzej niz w klamerce
    std::vector<std::shared_ptr<Dummy>> v1;
    std::vector<std::shared_ptr<Dummy>> v2;

    {
        // [TODO 1]: Zdefiniuj 3 zmienne przechowujace shared_ptr do Dummy z identyfikatorami A, B i C
        std::shared_ptr<Dummy> A = std::make_shared<Dummy>('A'); //prawa: wskaznik o nazwie A, ktory bedzie patrzyl na obiekt typu Dummy
        //lewa: rezerwacja miejsca na obiekt typu Dummy o literce A i licznik odwolan do niego
        //nastepuje rezerwacja pamieci na literke A, wyswietla A created, licznik odwolan zotaje ustawiony na 1
        std::shared_ptr<Dummy> B = std::make_shared<Dummy>('B'); //powstaje obiekt B, licznik = 1
        std::shared_ptr<Dummy> C = std::make_shared<Dummy>('C'); //powstaje obiekt C, licznik = 1

        // [TODO 1]: Dodaj A, B i C do v1
        //push_back zadziala, bo shared_ptr kocha byc kopiowany
        v1.push_back(A); //licznik dla A to 2, bo A jest trzymany przez zmienna lokalna A i wektor v1
        v1.push_back(B); //licznik dla B to 2
        v1.push_back(C); //licznik dla C to 2

        // [TODO 1]: Dodaj B i C do v2
        v2.push_back(B); //licznik dla B to 3
        v2.push_back(C); //licznik dla C to 3
    }
    //zmienne lokalne A, B, C gina, liczniki to teraz 1, 2, 2, ale reszta obiektow nie umiera

    std::cout << "\nClearing v1" << std::endl;
    v1.clear(); //A spada na 0 i ginie, B, C spadaja na 1
    //bez klamerek A spada na 1, B, C spadaja na 2
    std::cout << std::endl;

    std::cout << "Clearing v2" << std::endl;
    v2.clear(); //B, C spadaja na 0 i gina
    //bez klamerek B, C spadaja na 1 i nie gina
    std::cout << std::endl;

    //std::unique_ptr - tylko jeden wskaznik moze posiadac dany obiekt w danej chwili, unique_ptr jest niekopiowany, jest tylko jeden!!!
    // [TODO 2]: Zdefiniuj pusty wektor przechowujacy unique_ptr do Dummy
    std::vector<std::unique_ptr<Dummy>> v3; //dynamiczna tablica, ktora bedzie przechowywac wskazniki na obiekty typu Dummy
    //jesli usune wektor lub jego element, to wskazniki automatycznie wywolaja destruktory obiektow typu Dummy

    // [TODO 2]: Dodaj do v3 dwa unique_ptr z identyfikatorami D i E
    v3.emplace_back(std::make_unique<Dummy>('D'));
    //emplace_back - sprytniejsze push_back, bo zamiast tworzyc wskaznik i go kopiowac, emplace_back tworzy go bezposrednio wewnatrz wektora (bez tego trzebaby jakos std::move)
    //std::make_unique - tworzenie obiektu typu Dummy z literka D
    v3.emplace_back(std::make_unique<Dummy>('E'));

    std::cout << std::endl;

    return 0;
}