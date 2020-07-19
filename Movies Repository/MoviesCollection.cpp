#include "MoviesCollection.h"

Movies_Collection::Movies_Collection() {
	movies.resize(0);
	moviesAordered.resize(0);
	moviesYordered.resize(0);
	moviesToWatch.resize(0);
}
Movies_Collection::~Movies_Collection() {
}
void Movies_Collection::toString(std::string n, std::vector<std::string> addenda)
{
	if(n == "a")
	{
		std::cout<<"---------------------------------"<<std::endl;
		std::cout<<"ECCO I FILM IN ORDINE ALFABETICO: "<<std::endl;
		for(unsigned int i=0; i<moviesAordered.size(); i++)
			moviesAordered.at(i).toString(addenda);
	}
	else if(n == "y")
	{
		std::cout<<"---------------------------------"<<std::endl;
		std::cout<<"ECCO I FILM IN ORDINE DI USCITA: "<<std::endl;
		for(unsigned int i=0; i<moviesYordered.size(); i++)
			moviesYordered.at(i).toString(addenda);
	}
	else if(n == "w")
	{
		std::cout<<"---------------------------------"<<std::endl;
		std::cout<<"ECCO I FILM NON ANCORA VISTI: "<<std::endl;
		for(unsigned int i=0; i<moviesToWatch.size(); i++)
			moviesToWatch.at(i).toString(addenda);
	}
	/*else if(n == "a, all")
	{
		std::cout<<"---------------------------------"<<std::endl;
		std::cout<<"ECCO I FILM IN ORDINE ALFABETICO CON TUTTE LE CARATTERISTICHE: "<<std::endl<<std::endl;
		for(unsigned int i=0; i<moviesAordered.size(); i++)
			moviesAordered.at(i).toString("all");
	}*/
}
void Movies_Collection::setMoviesAordered()
{
	std::map<std::string, Movie> pair;
	for(unsigned int i=0; i<movies.size(); i++)
		pair[movies.at(i).name] = movies.at(i);

	std::vector<std::string> titles;
	titles.resize(0);

	for(unsigned int i=0; i<movies.size(); i++)
		titles.push_back(movies.at(i).name);

	std::sort(titles.begin(),titles.end());
	for(unsigned int i=0; i<movies.size(); i++)
		moviesAordered.push_back(pair[titles.at(i)]);
}
bool comparingYears(Movie m1, Movie m2)
{
	return (m1.year<m2.year);
}
void Movies_Collection::setMoviesYordered()
{
	moviesYordered = movies;
	std::sort(moviesYordered.begin(), moviesYordered.end(), comparingYears);
}

void Movies_Collection::setMoviesToWatch()
{
	for(unsigned int i=0; i<movies.size(); i++)
		if(!movies.at(i).watched)
			moviesToWatch.push_back(movies.at(i));

	std::vector<Movie> _moviesToWatch;
	std::map<std::string, Movie> pair;
	for(unsigned int i=0; i<moviesToWatch.size(); i++)
		pair[moviesToWatch.at(i).name] = moviesToWatch.at(i);

	std::vector<std::string> titles;
	titles.resize(0);

	for(unsigned int i=0; i<moviesToWatch.size(); i++)
		titles.push_back(moviesToWatch.at(i).name);

	std::sort(titles.begin(),titles.end());
	for(unsigned int i=0; i<moviesToWatch.size(); i++)
		_moviesToWatch.push_back(pair[titles.at(i)]);

	moviesToWatch = _moviesToWatch;
}
