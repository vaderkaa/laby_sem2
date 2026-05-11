#pragma once

#include <string>
#include <variant>
#include <optional>
#include <list>
#include <iostream>

template<class RatingType>
class Movie
{
public:
    struct Director
    {
        std::string name;
        int numberOfOscars;   
        Director(const std::string& name, int numberOfOscars) : name(name), numberOfOscars(numberOfOscars) {} 
    };

private:
    std::string title;
    int year;
    std::variant<Director, std::string> director; //struktura Director albo imie
    std::optional<std::string> description;
    std::list<RatingType> ratings;

public:
    explicit Movie(const std::string& title, int year, const std::variant<Director, std::string>& director, //sam dopasuje to, co podam, do variantu
    const std::optional<std::string>& description = std::nullopt) //jesli nic nie podam, to pustka
    : title(title), year(year), director(director), description(description) {}
    
    const std::string& getTitle() const { return title; } //prawo tylko do odczytu, referencja, zeby nie kopiowac i metoda nic nie zmieni
    int getYear() const { return year; } //nie modyfikuje, a kopiowanie jest szybkie
    const std::optional<std::string>& getDescription() const { return description; } //STD::OPTIONAL!!!
    const std::variant<Director, std::string>& getDirector() const { return director; }
    const std::list<RatingType>& getRatings() const { return ratings; }

    RatingType getAverageRating() const //zwraca wynik W TYM SAMYM TYPIE, w ktorym przechowuje oceny (niewiadomo czy double czy int), metoda nic nie modyfikuje
    {
        if(ratings.empty())
            return RatingType(0); //obiekt tymczasowy

        RatingType sum(0); //taka sama precyzja jak oceny, skladnia konstruktora, to samo co RatingType sum = 0;
        for (const auto& it : ratings)
            sum += it;
        return sum/ratings.size();
    }

    RatingType getTopRating() const
    {
        if(ratings.empty())
            return RatingType(0); //obiekt tymczasowy

        auto it = ratings.begin(); //ustawiam na poczatek
        RatingType top = *it; //ustawiam top na pierwsza wartosc
        for (; it != ratings.end(); ++it) //; - brak inicjalizacji, bo it juz jest stworzony
        //!=, bo end() wskazuje na miejsce za ostatnim elementem
        {
            if (*it > top)
                top = *it;
        }
        return top;
    }

    bool operator<(const Movie& other) //czy this < other?
    {
        if(this->title == other.title)
            return this->year < other.year;
        
        return this->title < other.title;
    }

    bool operator==(const Movie& other)
    {
        return this->title == other.title && this->year == other.year;
    }

    Movie& operator+(const RatingType& other)
    {
        this->ratings.push_back(other);
        return *this; //ZWRACA SIEBIE!!!
    }
};

template<class RatingType>
std::ostream& operator<<(std::ostream& os, const Movie<RatingType>& movie) //zwraca referencje do strumienia, zeby moc pisac cout << m1 << m2; MUSI BYC <RatingType>!!!
{
    os << movie.getTitle() << " (" << movie.getYear() << "), ";
    if (std::holds_alternative<typename Movie<RatingType>::Director>(movie.getDirector())) //std::holds_alternative<T> - sprawdza, czy w wariancie znajduje sie typ T
    //typename, bo odwoluje sie do innej klasy, sciezka do struktury wewnatrz tej klasy
    {
        const auto& director = std::get<typename Movie<RatingType>::Director>(movie.getDirector()); //std::get<T> - pobranie wartosci z wariantu o typie T
        //const - nie zmienie rezysera, & - nie tworze kopii, auto - typ sie sam dostosuje
        os << "Director: " << director.name << " (Oscars: " << director.numberOfOscars << "), ";
    }
    else
        os << "Director: " << std::get<std::string>(movie.getDirector()) << ", ";

    os << "Avg: " << movie.getAverageRating() << ", Top: " << movie.getTopRating();

    if (movie.getDescription()) //optional, wiec zwraca true albo false
    {
        os << "\nDescription: " << *movie.getDescription();
    }

    return os;
}