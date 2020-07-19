#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "ActorsCollection.h"

int countLines(std::ifstream& ifs);

void readFromText(Movies_Collection& moviesCollection);

void ask(std::string& n);

void check(std::string n, Movies_Collection moviesCollection, Actors_Collection actorsCollection);

void searchByName(std::string name, Movies_Collection moviesCollection, std::vector<std::string> addenda);

void searchByYear(int year, Movies_Collection moviesCollection, std::vector<std::string> addenda);

void searchByGenre(std::string genre, Movies_Collection moviesCollection, std::vector<std::string> addenda);

void searchByActor(std::string actor, Movies_Collection moviesCollection, Actors_Collection actorsCollection, std::vector<std::string> addenda);

void searchByCharacter(std::string actor, Movies_Collection moviesCollection, std::vector<std::string> addenda);

void searchActor(std::string actor, Actors_Collection actors);

void getRandomMovie(Movies_Collection moviesCollection, std::vector<std::string> addenda, std::string w);

void getRandomMovieGivenGenre(std::string genre, Movies_Collection moviesCollection, std::vector<std::string> addenda);


#endif
