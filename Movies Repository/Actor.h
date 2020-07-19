#ifndef ACTOR_H_
#define ACTOR_H_

#include "MoviesCollection.h"

class Actor {
public:
	//VARIABILI
	std::string name;

	// mappa di <personaggio interpretato, film>
	std::multimap<std::string, Movie> characterToMovie;
	// mappa di <nome del film, personaggio interpretato>
	std::multimap<std::string, std::string> movieToCharacter;

	//COSTRUTTORI
	Actor();

	//METODI
	void toString(std::string);
	void fillVariables(Movie, std::string);
	bool operator==(Actor);
	bool operator==(std::string);
};

#endif
