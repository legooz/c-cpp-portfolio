#pragma once
#include <iostream>
#include <string>

using namespace std;

class Movie
{
private:
    string movieName;
    string mpaaRating;

public:
    Movie();
    void setName(string title);
    string getName();
    void sortAlphabetically(Movie movies[], int numMovies);
    void setRating(string rating);
    string getRating();
};
