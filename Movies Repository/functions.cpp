#include "functions.h"

/* PER CERCARE SOTTO-STRINGA IN UNA STRINGA SENZA CONTARE MAIUSCOLE/MINUSCOLE */

template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

template<typename T>
int ci_find_substr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(),
        str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}
/*  ------------------------------------------------------------------------ */

void readFromText(Movies_Collection& moviesCollection)
{
	std::ifstream ifs_1("MovieList.txt", std::ios::in);
	int count = countLines(ifs_1);
	ifs_1.close();
	std::ifstream ifs("MovieList.txt");
	int i = 0;
	while(i<count)
	{
		std::string title;
		std::getline(ifs,title);
		i++;

		std::string description="";
		std::string dummy ="";
		while(dummy != "0")
		{
			std::getline(ifs,dummy);
			i++;
			if(dummy!= "0")
			{
				description += dummy;
				description += "\n";
			}

		}

		std::vector<std::string> genre;
		genre.resize(0);
		dummy="";
		while(dummy != "0")
		{
			std::getline(ifs,dummy);
			i++;
			if(dummy != "0")
			{
				genre.push_back(dummy);
			}
		}

		std::string _year;
		std::getline(ifs, _year);
		int year = std::atoi(_year.c_str());
		i++;

		std::vector<std::string> actors;
		actors.resize(0);
		dummy="";
		while(dummy != "0")
		{
			std::getline(ifs,dummy);
			i++;
			if(dummy != "0")
			{
				actors.push_back(dummy);
			}
		}

		std::string _watched;
		std::getline(ifs, _watched);
		bool watched = (_watched=="yes")?true:false;
		i++;

		Movie movie(title,description,genre,year,actors,watched);
		moviesCollection.movies.push_back(movie);
	}
}

int countLines(std::ifstream& ifs)
{
	int numLines = 0;
	std::string line;
	while(std::getline(ifs, line))
	{
		numLines++;
	}
	return numLines;
}

void ask(std::string& n)
{
	std::cout<<std::endl<<"\n*************************************"<<std::endl;
	std::cout<<"\n What would you like to do? (write ""help"" in order to visualize the possible entries) \n";
	std::getline(std::cin, n);
}

void check(std::string n, Movies_Collection moviesCollection, Actors_Collection actorsCollection)
{
	std::vector<std::string> addenda;
	addenda.resize(0);
	int numb=0;

	for(char c : n)
		if(c==',')
			numb++;

	for(int i=0; i<numb; i++)
	{
		size_t comma = n.find_last_of(",");
		addenda.push_back(n.substr(comma+2));
		n.erase(n.begin()+comma,n.end());
	}

	if(n == "help")
	{
		std::cout<<"\n*********** HELP ***********\n\n";
		std::cout<<"0 --> Quit the program;\n";
		std::cout<<"1 --> Show movies in alphabetical order;\n";
		std::cout<<"2 --> Show movies in year of production order;\n";
		std::cout<<"sbn --> \"SearchByName\" = Search movie by name; \n";
		std::cout<<"sby --> \"SearchByYear\" = Search movie by year of production; \n";
		std::cout<<"sbg --> \"SearchByGenre\" = Searc movie by genre;\n";
		std::cout<<"sba --> \"SearchByActor\" = Search movies in which the selected actor is present;\n";
		std::cout<<"sbc --> \"SearchByCharacter\" = Search movies in which the selected fictional character is present;\n";
		std::cout<<"sa --> \"SearchActor\" = Search actor, with movies and characters interpreted;\n";
		std::cout<<"r --> \"Random\" = Extract random movie;\n";
		std::cout<<"rbg --> \"RandomByGenre\" = Extract random movie of the selected genre; \n";
		std::cout<<"rnw --> \"RandomNotWatched\" = Extract random movie from -not watched- ones; \n";
		std::cout<<"stat --> Show Statistics;\n";
		std::cout<<"act --> Show all actors and roles interpred;\n";
		std::cout<<"\n------- Add a comma and one of the following (with possibile concatenation) -------\n\n";
		std::cout<<"y --> \"Year\" = Also show the year of production;\n";
		std::cout<<"g --> \"Genre\" = Also show the genre;\n";
		std::cout<<"p --> \"Plot\" = Also show the plot;\n";
		std::cout<<"a --> \"Actors\" = Also show the principal actors;\n";
		std::cout<<"w --> \"Watched\" = Only show -not watched- movies;\n";
		std::cout<<"all --> Show every characteristic of the movie;\n";
	}
	else if(n == "1")
		moviesCollection.toString("a", addenda);
	else if(n == "2")
		moviesCollection.toString("y", addenda);
	else if(n == "sbn")
	{
		std::string searchName;
		std::cout<<"***************************\n";
		std::cout<<"WHAT WOULD YOU LIKE TO FIND?\n";
		std::getline(std::cin, searchName);
		searchByName(searchName, moviesCollection, addenda);
	}
	else if(n == "sby")
	{
		std::string searchYear;
		std::cout<<"***************************\n";
		std::cout<<"WHAT IS THE YEAR OF PRODUCTION OF THE MOVIES YOU WOULD LIKE TO FIND?\n";
		std::cin>>searchYear;
		searchByYear(std::atoi(searchYear.c_str()), moviesCollection, addenda);
	}
	else if(n == "sbg")
	{
		std::string searchGenre;
		std::cout<<"***************************\n";
		std::cout<<"WHAT IS THE GENRE OF THE MOVIES YOU WOULD LIKE TO FIND?\n";
		std::cin>>searchGenre;
		searchByGenre(searchGenre, moviesCollection, addenda);
	}
	else if(n == "sba")
	{
		std::string searchActor;
		std::cout<<"***************************\n";
		std::cout<<"wHAT ACTOR WOULD YOU LIKE TO CONSIDER?\n";
		std::getline(std::cin, searchActor);
		searchByActor(searchActor, moviesCollection, actorsCollection, addenda);
	}
	else if(n == "sbc")
	{
		std::string searchCharacter;
		std::cout<<"***************************\n";
		std::cout<<"WHAT CHARACTER WOULD YOU LIKE TO CONSIDER?\n";
		std::getline(std::cin, searchCharacter);
		searchByCharacter(searchCharacter, moviesCollection, addenda);
	}
	else if(n == "sa")
	{
		std::string search_actor;
		std::cout<<"***************************\n";
		std::cout<<"WHAT ACTOR WOULD YOU LIKE TO SEARCH? \n";
		std::getline(std::cin, search_actor);
		searchActor(search_actor, actorsCollection);
	}
	else if(n == "r")
	{
		std::cout<<"***************************\n";
		std::cout<<"THE MOVIE CHOSEN FOR YOU IS:\n\n";
		getRandomMovie(moviesCollection, addenda, "all");
	}
	else if(n == "rbg")
	{
		std::cout<<"***************************\n";
		std::cout<<"WRITE THE GENRE OF THE MOVIE YOU WOULD LIKE TO RANDOMLY PICK:\n";
		std::string searchGenre;
		std::cin>>searchGenre;
		std::cout<<"\n";
		getRandomMovieGivenGenre(searchGenre, moviesCollection, addenda);
	}
	else if(n == "rnw")
	{
		std::cout<<"***************************\n";
		std::cout<<"THE MOVIE CHOSEN FOR YOU IS:\n\n";
		getRandomMovie(moviesCollection, addenda, "not watched");
	}
	else if(n == "stat")
	{
		std::cout<<"***************************\n";
		std::cout<<"Number of movies: "<<moviesCollection.movies.size()<<"\n";
		std::cout<<"Number of unwatched movies: ";
		int n=0;
		for(unsigned int i=0; i<moviesCollection.movies.size(); i++)
			if(!moviesCollection.movies.at(i).watched)
				n++;

		std::cout<<n<<"\n";
	}
	else if(n == "act")
	{
		actorsCollection.toString("");
	}
}

void searchByName(std::string name, Movies_Collection moviesCollection, std::vector<std::string> addenda)
{
	Movies_Collection correspondences;

	for(unsigned int i=0; i<moviesCollection.movies.size(); i++)
	{
		if(ci_find_substr(moviesCollection.movies.at(i).name, name) != -1)
		{
			correspondences.movies.push_back(moviesCollection.movies.at(i));
		}
	}
	if(correspondences.movies.size() != 0)
	{
		correspondences.setMoviesAordered();
		correspondences.toString("a", addenda);
	}
	else
	{
		std::cout<<"I'M SORRY, BUT NO SUCH MOVIE EXISTS\n";
	}

	std::cout<<"\n\n Number of movies found: "<<correspondences.movies.size()<<"\n";
}

void searchByYear(int year, Movies_Collection moviesCollection, std::vector<std::string> addenda)
{
	Movies_Collection correspondence;
	for(unsigned int i=0; i<moviesCollection.movies.size();i++)
		if(moviesCollection.movies.at(i).year == year)
			correspondence.movies.push_back(moviesCollection.movies.at(i));

	if(correspondence.movies.size() != 0)
	{
		correspondence.setMoviesAordered();
		correspondence.toString("a", addenda);
	}
	else
		std::cout<<"MI DISPIACE, MA NON E' PRESENTE NESSUN FILM DELL'ANNO RICHIESTO\n";

	std::cout<<"\n\nNumero di film trovati: "<<correspondence.movies.size()<<"\n";
}

void searchByGenre(std::string genre, Movies_Collection moviesCollection, std::vector<std::string> addenda)
{
	Movies_Collection correspondence;
	std::string GENRE = genre;
	std::transform(GENRE.begin(), GENRE.end(), GENRE.begin(), ::toupper);
	for(unsigned int i=0; i<moviesCollection.movies.size(); i++)
		for(unsigned int j=0; j<moviesCollection.movies.at(i).genre.size(); j++)
			if(moviesCollection.movies.at(i).genre.at(j) == genre || moviesCollection.movies.at(i).genre.at(j) == GENRE)
				correspondence.movies.push_back(moviesCollection.movies.at(i));

	if(correspondence.movies.size() != 0)
	{
		correspondence.setMoviesAordered();
		correspondence.toString("a", addenda);
	}
	else
		std::cout<<"I'M SORRY, BUT NO MOVIE OF THE REQUESTED GENRE EXISTS \n";

	std::cout<<"\n\nNumero di film trovati: "<<correspondence.movies.size()<<"\n";
}

void searchByActor(std::string actor, Movies_Collection moviesCollection, Actors_Collection actorsCollection, std::vector<std::string> addenda)
{
	Movies_Collection m;
	for(unsigned i=0; i<actorsCollection.actors.size(); i++)
	{
		if(ci_find_substr(actorsCollection.actors.at(i).name, actor) != -1)
		{
			for(auto x: actorsCollection.actors.at(i).characterToMovie)
				m.movies.push_back(x.second);
		}
	}
	m.setMoviesAordered();
	m.toString("a", addenda);
}

void searchByCharacter(std::string character, Movies_Collection moviesCollection, std::vector<std::string> addenda)
{
	Movies_Collection m;
	for(unsigned i=0; i<moviesCollection.movies.size(); i++)
	{
		for(unsigned j=0; j<moviesCollection.movies.at(i).actors.size(); j++)
			if(ci_find_substr(moviesCollection.movies.at(i).actors.at(j), character) != -1)
				m.movies.push_back(moviesCollection.movies.at(i));
	}
	m.setMoviesAordered();
	m.toString("a", addenda);
}

void getRandomMovie(Movies_Collection moviesCollection, std::vector<std::string> addenda, std::string w)
{
	if(w == "all")
	{
		int n = rand() % moviesCollection.movies.size();
		moviesCollection.movies.at(n).toString(addenda);
	}
	else if(w == "not watched")
	{
		int n = rand() % moviesCollection.moviesToWatch.size();
		moviesCollection.moviesToWatch.at(n).toString(addenda);
	}
}

void searchActor(std::string actor, Actors_Collection actors)
{
	for(auto x : actors.actors)
		if(ci_find_substr(x.name, actor) != -1)
			x.toString("");
}

void getRandomMovieGivenGenre(std::string genre, Movies_Collection moviesCollection, std::vector<std::string> addenda)
{
	Movies_Collection correspondence;
	std::string GENRE = genre;
	std::transform(GENRE.begin(), GENRE.end(), GENRE.begin(), ::toupper);
	for(unsigned int i=0; i<moviesCollection.movies.size(); i++)
		for(unsigned int j=0; j<moviesCollection.movies.at(i).genre.size(); j++)
			if(moviesCollection.movies.at(i).genre.at(j) == genre || moviesCollection.movies.at(i).genre.at(j) == GENRE)
				correspondence.movies.push_back(moviesCollection.movies.at(i));

	if(correspondence.movies.size() != 0)
	{
		int n = rand() % correspondence.movies.size();
		correspondence.movies.at(n).toString(addenda);
	}
	else
		std::cout<<"I'M SORRY, BUT NO MOVIE OF THE REQUESTED GENRE EXISTS\n";
}

