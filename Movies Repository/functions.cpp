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
	std::cout<<"\n Cosa vuoi fare? (scrivi ""help"" per visualizzare i comandi) \n";
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
		std::cout<<"0 --> Termina il programma;\n";
		std::cout<<"1 --> Visualizza i film in ordine alfabetico;\n";
		std::cout<<"2 --> Visualizza i film in ordine di uscita;\n";
		std::cout<<"sbn --> \"SearchByName\" = Cerca film per nome; \n";
		std::cout<<"sby --> \"SearchByYear\" = Cerca film per anno di uscita; \n";
		std::cout<<"sbg --> \"SearchByGenre\" = Cerca film per Genere;\n";
		std::cout<<"sba --> \"SearchByActor\" = Cerca film in cui e' presente l'attore scelto;\n";
		std::cout<<"sbc --> \"SearchByCharacter\" = Cerca film in cui e' presente il personaggio scelto;\n";
		std::cout<<"sa --> \"SearchActor\" = Cerca attore, con film e personaggi che ha interpretato;\n";
		std::cout<<"r --> \"Random\" = Estrai film casuale;\n";
		std::cout<<"rbg --> \"RandomByGenre\" = Estrai film casuale contenente il dato genere; \n";
		std::cout<<"rnw --> \"RandomNotWatched\" = Estrai un film casuale tra quelli non visti; \n";
		std::cout<<"stat --> Visualizza statistiche;\n";
		std::cout<<"act --> Visualizza tutti gli attori con i film e ruoli interpretati;\n";
		std::cout<<"\n------- Aggiungi una virgola piu' una delle seguenti (si possono concatenare) -------\n\n";
		std::cout<<"y --> \"Year\" = Visualizza anche l'anno del film;\n";
		std::cout<<"g --> \"Genre\" = Visualizza anche i generi a cui appartiene il film;\n";
		std::cout<<"p --> \"Plot\" = Visualizza anche la trama del film;\n";
		std::cout<<"a --> \"Actors\" = Visualizza anche gli attori famosi;\n";
		std::cout<<"w --> \"Watched\" = Visualizza solo i film non visti;\n";
		std::cout<<"all --> Visualizza tutte le caratteristiche del film;\n";
	}
	else if(n == "1")
		moviesCollection.toString("a", addenda);
	else if(n == "2")
		moviesCollection.toString("y", addenda);
	else if(n == "sbn")
	{
		std::string searchName;
		std::cout<<"***************************\n";
		std::cout<<"COSA VUOI TROVARE?\n";
		std::getline(std::cin, searchName);
		searchByName(searchName, moviesCollection, addenda);
	}
	else if(n == "sby")
	{
		std::string searchYear;
		std::cout<<"***************************\n";
		std::cout<<"L'ANNO DEI FILM CHE VUOI CERCARE?\n";
		std::cin>>searchYear;
		searchByYear(std::atoi(searchYear.c_str()), moviesCollection, addenda);
	}
	else if(n == "sbg")
	{
		std::string searchGenre;
		std::cout<<"***************************\n";
		std::cout<<"IL GENERE DEI FILM CHE VUOI CERCARE?\n";
		std::cin>>searchGenre;
		searchByGenre(searchGenre, moviesCollection, addenda);
	}
	else if(n == "sba")
	{
		std::string searchActor;
		std::cout<<"***************************\n";
		std::cout<<"CHE ATTORE VUOI CONSIDERARE?\n";
		std::getline(std::cin, searchActor);
		searchByActor(searchActor, moviesCollection, actorsCollection, addenda);
	}
	else if(n == "sbc")
	{
		std::string searchCharacter;
		std::cout<<"***************************\n";
		std::cout<<"CHE PERSONAGGIO VUOI CONSIDERARE?\n";
		std::getline(std::cin, searchCharacter);
		searchByCharacter(searchCharacter, moviesCollection, addenda);
	}
	else if(n == "sa")
	{
		std::string search_actor;
		std::cout<<"***************************\n";
		std::cout<<"CHE ATTORE VUOI CERCARE? \n";
		std::getline(std::cin, search_actor);
		searchActor(search_actor, actorsCollection);
	}
	else if(n == "r")
	{
		std::cout<<"***************************\n";
		std::cout<<"IL FILM SCELTO PER TE E':\n\n";
		getRandomMovie(moviesCollection, addenda, "all");
	}
	else if(n == "rbg")
	{
		std::cout<<"***************************\n";
		std::cout<<"SCRIVI IL GENERE DEL FILM CHE VUOI ESTRARRE CASUALMENTE:\n";
		std::string searchGenre;
		std::cin>>searchGenre;
		std::cout<<"\n";
		getRandomMovieGivenGenre(searchGenre, moviesCollection, addenda);
	}
	else if(n == "rnw")
	{
		std::cout<<"***************************\n";
		std::cout<<"IL FILM SCELTO PER TE E':\n\n";
		getRandomMovie(moviesCollection, addenda, "not watched");
	}
	else if(n == "stat")
	{
		std::cout<<"***************************\n";
		std::cout<<"Numero di Film: "<<moviesCollection.movies.size()<<"\n";
		std::cout<<"Numero di Film ancora da vedere: ";
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
		std::cout<<"MI DISPIACE, MA NON E' PRESENTE NESSUN FILM CON IL NOME RICHIESTO\n";
	}

	std::cout<<"\n\nNumero di film trovati: "<<correspondences.movies.size()<<"\n";
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
		std::cout<<"MI DISPIACE, MA NON E' PRESENTE NESSUN FILM DEL GENERE RICHIESTO\n";

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
		std::cout<<"MI DISPIACE MA NON ESISTONO FILM DEL GENERE CERCATO\n";
}

