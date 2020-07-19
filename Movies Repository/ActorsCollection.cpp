#include "ActorsCollection.h"

Actors_Collection::Actors_Collection() {
	actors.resize(0);
}

Actors_Collection::~Actors_Collection() {
}
void Actors_Collection::fillActors(Movies_Collection moviesCollection)
{
	for(unsigned int i=0; i<moviesCollection.movies.size(); i++)
	{
		for(unsigned int j=0; j<moviesCollection.movies.at(i).actors.size(); j++)
		{
			Actor a;
			a.fillVariables(moviesCollection.movies.at(i), moviesCollection.movies.at(i).actors.at(j));
			std::vector<Actor>::iterator it = find(actors.begin(), actors.end(), a);

			if(it == actors.end())
			{
				actors.push_back(a);
			}
			else
			{
				(*it).fillVariables(moviesCollection.movies.at(i), moviesCollection.movies.at(i).actors.at(j));
			}
		}
	}
	setAordered();
}

void Actors_Collection::setAordered()
{
	std::map<std::string, Actor> pair;
	std::vector<Actor> _actors;

	for(unsigned int i=0; i<actors.size(); i++)
		pair[actors.at(i).name] = actors.at(i);

	std::vector<std::string> titles;
	titles.resize(0);

	for(unsigned int i=0; i<actors.size(); i++)
		titles.push_back(actors.at(i).name);

	std::sort(titles.begin(),titles.end());

	for(unsigned int i=0; i<actors.size(); i++)
		_actors.push_back(pair[titles.at(i)]);

	actors = _actors;
}

void Actors_Collection::toString(std::string)
{
	for(auto x: actors)
	{
		x.toString("");
	}
}
