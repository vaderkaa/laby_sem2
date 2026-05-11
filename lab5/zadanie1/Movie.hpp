#pragma once

#include <string>
#include <variant>
#include <optional>
#include <list>

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
    const std::optional<std::string>& getDescription() const { return description; } //STD::DESCRIPTION!!!
    const std::variant<Director, std::string>& getDirector() const { return director; }
    const std::list<RatingType>& getRatings() const { return ratings; }
};