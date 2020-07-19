#include "Movie.h"

Movie::Movie() {
	name="";
	description="";
	year=0;
	genre.resize(0);
	actors.resize(0);
	watched = false;
}

Movie::Movie(std::string _name, std::string _description, std::vector<std::string> _genre, int _year, std::vector<std::string> _actors, bool _watched)
{
	name = _name;
	description = _description;
	genre = _genre;
	year = _year;
	actors = _actors;
	watched = _watched;
}

Movie::~Movie() {
}

void Movie::coutYear()
{
	std::cout<<" ---- Anno: "<<year;
}
void Movie::coutGenre()
{
	std::cout<<" ---- Genere: ";
	for(unsigned int i=0; i<genre.size();i++)
	{
		std::cout<<genre.at(i);
		if(i!=genre.size()-1)
		{
			std::cout<<", ";
		}
	}
}
void Movie::coutActors()
{
	std::cout<<"\nAttori famosi:\n";
	for(int i=0; i<actors.size();i++)
	{
		std::cout<<actors.at(i)<<"\n";
	}
}
void Movie::coutDescription()
{
	std::cout<<"\n--------- Descrizione ---------"<<std::endl<<description<<std::endl;
}
void Movie::toString(std::vector<std::string> addenda)
{
	if(addenda.size()==0)
		std::cout<<name<<std::endl;
	else
	{
		std::vector<std::string>::iterator it;

		it=find(addenda.begin(), addenda.end(), "all");

		if(it != addenda.end())
		{
			std::cout<<"\n"<<name;
			coutYear();
			coutGenre();
			coutActors();
			coutDescription();
		}
		else
		{
			it = find(addenda.begin(), addenda.end(), "w");
			if( (it != addenda.end() && !watched) || (it == addenda.end()) )
			{
				std::cout<<"\n"<<name;

				it = find(addenda.begin(), addenda.end(), "y");
				if(it != addenda.end())
					coutYear();

				it = find(addenda.begin(), addenda.end(), "g");
				if(it != addenda.end())
					coutGenre();

				it = find(addenda.begin(), addenda.end(), "a");
				if(it != addenda.end())
					coutActors();

				it = find(addenda.begin(), addenda.end(), "p");
				if(it != addenda.end())
					coutDescription();
			}
		}
	}

	/*
	if(s == "name")
	{
		std::cout<<name<<std::endl;
	}
	else if(s == "name and genre")
	{
		std::cout<<name<<"  ---- Genere: ";
		for(unsigned int i=0; i<genre.size();i++)
		{
			std::cout<<genre.at(i);
			if(i!=genre.size()-1)
			{
				std::cout<<", ";
			}
		}
		std::cout<<std::endl;
	}
	else if(s == "name, year")
	{
		std::cout<<name<<" ---- Anno: "<<year<<std::endl;
	}
	else if(s == "name, genre and year")
	{
		std::cout<<name<<" ---- Anno: "<<year<<" ---- Genere: ";
		for(unsigned int i=0; i<genre.size();i++)
		{
			std::cout<<genre.at(i);
			if(i!=genre.size()-1)
			{
				std::cout<<", ";
			}
		}
		std::cout<<std::endl;
	}
	else if(s == "all")
	{
		std::cout<<name<<" ---- Anno: "<<year<<" ---- Genere: ";
		for(unsigned int i=0; i<genre.size();i++)
		{
			std::cout<<genre.at(i);
			if(i!=genre.size()-1)
			{
				std::cout<<", ";
			}
		}
		std::cout<<std::endl;
		std::cout<<"Attori famosi: ";
		for(int i=0; i<actors.size();i++)
		{
			std::cout<<actors.at(i);
			if(i != actors.size()-1)
			{
				std::cout<<"; ";
			}
		}
		std::cout<<std::endl;
		std::cout<<"--------- Descrizione ---------"<<
				std::endl<<description<<std::endl<<std::endl;
	}*/
}
