#ifndef ACTORSCOLLECTION_H_
#define ACTORSCOLLECTION_H_

#include "Actor.h"

class Actors_Collection {
public:

	//VARIABILI
	std::vector<Actor> actors;

	//COSTRUTTORI
	Actors_Collection();
	virtual ~Actors_Collection();

	//METODI
	void fillActors(Movies_Collection);
	void toString(std::string);
	void setAordered();
};

#endif
