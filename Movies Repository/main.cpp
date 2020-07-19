#include "functions.h"

int main()
{
	Movies_Collection moviesCollection;
	readFromText(moviesCollection);
	moviesCollection.setMoviesAordered();
	moviesCollection.setMoviesYordered();
	moviesCollection.setMoviesToWatch();

	Actors_Collection actorsCollection;
	actorsCollection.fillActors(moviesCollection);

	srand(time(NULL));

	std::string n="";
	while(n != "0")
	{
		ask(n);
		check(n, moviesCollection, actorsCollection);
	}
}
