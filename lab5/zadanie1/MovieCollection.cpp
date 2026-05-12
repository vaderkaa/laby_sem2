#include "Movie.hpp"
#include "MovieCollection.hpp"

const std::map<char, std::vector<Movie<double>>>& MovieCollection::getMoviesByLetter() const
{
    return moviesByLetter;
}

std::vector<Movie<double>> MovieCollection::getAllMovies() const
{
    std::vector<Movie<double>> result;
    for(const auto& [letter, movieList] : moviesByLetter) //automatycznie przypisuje pair.first = letter i pair.second = movieList z moviesByLetter
        result.insert(result.end(), movieList.begin(), movieList.end());
    return result;
}

void MovieCollection::addMovie(const Movie<double>& movie)
{
    if(!movie.getTitle().empty())
    {
        char firstLetter = movie.getTitle()[0];
        moviesByLetter[firstLetter].push_back(movie); //klucz i wartosc
    }
}

std::ostream& operator<<(std::ostream& os, const MovieCollection& collection)
{
    const auto& data = collection.getMoviesByLetter(); //zwraca referencje do mojej mapy
    for(const auto& [letter, movieList] : data)
    {
        os << "=== " << letter << " ===\n";
        for(const auto& movie : movieList)
            os << movie << "\n";
    }
    return os;
}