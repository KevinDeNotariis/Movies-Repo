#ifndef MOVIESCOLLECTION_H_
#define MOVIESCOLLECTION_H_

#include "Movie.h"

class Movies_Collection {
public:

//VIRIABILI

	std::vector<Movie> movies;
	std::vector<Movie> moviesAordered;
	std::vector<Movie> moviesYordered;
	std::vector<Movie> moviesToWatch;

//CONSTRUCTORS

	Movies_Collection();

	virtual ~Movies_Collection();

//METHODS

	void setMoviesAordered();
	void setMoviesYordered();
	void setMoviesToWatch();

	void toString(std::string, std::vector<std::string>);

};

#endif
