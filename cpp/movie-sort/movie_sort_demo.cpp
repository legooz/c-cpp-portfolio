#include <iostream>
#include "Movie.h"
using namespace std;

int main()
{
    Movie movies[6];

    movies[0].setName("Red Sparrow");
    movies[0].setRating("R");

    movies[1].setName("Avengers: Infinity War");
    movies[1].setRating("PG-13");

    movies[2].setName("A Wrinkle In Time");
    movies[2].setRating("PG");

    movies[3].setName("Black Panther");
    movies[3].setRating("PG-13");

    movies[4].setName("Ready Player One");
    movies[4].setRating("PG-13");

    movies[5].setName("The Incredibles 2");
    movies[5].setRating("G");

    cout << "Before sorting " << endl;
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << movies[i].getName() << ", ";
        cout << movies[i].getRating() << endl;
    }

    cout << endl;
    cout << "After sorting " << endl;
    cout << endl;

    movies->sortAlphabetically(movies, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << movies[i].getName() << ", ";
        cout << movies[i].getRating() << endl;
    }

    return 0;
}
