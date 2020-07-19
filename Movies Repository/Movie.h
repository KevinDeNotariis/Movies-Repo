#ifndef MOVIE_H_
#define MOVIE_H_

#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <time.h>
#include <random>

class Movie{
public:
//VARIABILI
	std::string name;
	std::string description;
	std::vector<std::string> genre;
	int year;
	std::vector<std::string> actors;
	bool watched;

//COSTRUTTORI
	Movie();
	Movie(std::string _name, std::string _description, std::vector<std::string> _genre, int _year, std::vector<std::string> _actors, bool _watched);
	virtual ~Movie();

//METODI
	void toString(std::vector<std::string> addenda);

	void coutYear();
	void coutGenre();
	void coutActors();
	void coutDescription();
};

#endif
