#include "Movie.h"
#include <stdexcept>

Movie::Movie()
{
    movieName = "None";
    mpaaRating = "None";
}

void Movie::setName(string title)
{
    movieName = title;
}

string Movie::getName()
{
    return movieName;
}

void Movie::sortAlphabetically(Movie movies[], int numMovies)
{
    if (numMovies < 0 || (!movies && numMovies > 0))
        throw std::invalid_argument("Invalid movie array or length");
    int min = 0;
    int j = 0;
    int i = 0;

    for (i = 0; i < numMovies; i++)
    {
        min = i;

        for (j = i + 1; j < numMovies; j++)
        {

            if (movies[j].getName() < (movies[min].getName()))
            {
                min = j;
            }
        }

        if (min != i)
        {
            Movie temp = movies[i];
            movies[i] = movies[min];
            movies[min] = temp;
        }
    }
}

void Movie::setRating(string rating)
{
    mpaaRating = rating;
}

string Movie::getRating()
{
    return mpaaRating;
}
