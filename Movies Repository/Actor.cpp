#include "Actor.h"

Actor::Actor() {
	name="";
}
void Actor::fillVariables(Movie m, std::string s)
{
	std::string _name;
	std::string _character;
	std::string actor=s;

	for(unsigned int i=0; i<m.actors.size(); i++)
		if(m.actors.at(i)==s)
			actor=m.actors.at(i);

	std::size_t parenthesis = actor.find_first_of("(");
	_name = actor.substr(0, parenthesis-1);
	size_t numb= actor.find_first_of(")")-actor.find_first_of("(")-1;
	_character = actor.substr(parenthesis+1,numb);

	characterToMovie.insert(std::pair<std::string, Movie>(_character, m));
	movieToCharacter.insert(std::pair<std::string, std::string>(m.name, _character));
	name = _name;
}
void Actor::toString(std::string n)
{
	std::cout<<"\n"<<name<<" ha interpretato:\n\n";
	for(auto x: movieToCharacter)
		std::cout<<"- "<<x.second<<" nel film: "<<x.first<<"\n";
}
bool Actor::operator==(Actor a)
{
	if(name == a.name)
		return true;
	else
		return false;
}
bool Actor::operator==(std::string s)
{
	if(name == s)
		return true;
	else
		return false;
}
