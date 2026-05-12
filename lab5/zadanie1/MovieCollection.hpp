#pragma once
#include "Movie.hpp"

#include <map>
#include <vector>
#include <iostream>

class MovieCollection
{
private:
    std::map<char, std::vector<Movie<double>>> moviesByLetter;

public:
    const std::map<char, std::vector<Movie<double>>>& getMoviesByLetter() const;
    std::vector<Movie<double>> getAllMovies() const;
    void addMovie(const Movie<double>& movie);

};

std::ostream& operator<<(std::ostream& os, const MovieCollection& collection);

