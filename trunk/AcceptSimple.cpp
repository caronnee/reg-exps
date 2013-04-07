#include "stdafx.h"
#include "AcceptSimple.h"

StateSearch::StateSearch(char ch) : _ch(ch), _state(NULL)
{
}

State * StateSearch::Next()
{
	return _state;
}

StateSearch::~StateSearch()
{
	_state = NULL;
}

void StateSearch::SetNext( State * state )
{
	_state = state;
}

bool StateSearch::Accept( char c, SearchStateArray & array )
{
	if (c == _ch)
	{
		return State::Accept(array, Next());
	}
	NotAccept();
	return false;
}

StateAnyChar::StateAnyChar(){}

bool StateAnyChar::Accept(char ch, SearchStateArray & cands)
{
	return true;
}

StateAnyChar::~StateAnyChar()	{}

StateInterval::StateInterval( const char * pattern )
{
	_intervals.Clear();

	//char * pattern = new char = Validate(p);
	int len = strlen(pattern);
	int index =0;
	while(index < len-2)
	{
		/*if (pattern[index+1]=='-')
		{
		Interval interval(pattern[index], pattern[index+2]);
		_intervals.push_back(interval);
		index+=3;
		continue;
		}
		Interval interval(pattern[index], pattern[index]);
		_intervals.push_back(interval);*/
	}
	//process the last two/one. These can be just ordinary
	/*for ( int i = index; pattern[index]!='\0'; index++)
	{
	Interval interval(pattern[index], pattern[index]);
	_intervals.push_back(interval);
	}*/
}

void StateInterval::Validate( char * pattern )
{
	//TODO
}

bool StateInterval::Accept( char ch, SearchStateArray & array )
{
	for ( int i =0; i < _intervals.Size(); i++)
		if (_intervals[i]->Accept(ch, array ))
			return true;

	return false;
}

StateInterval::~StateInterval()
{
	_intervals.Clear();
}

StateNotInterval::StateNotInterval( const char * pattern ) : StateInterval(pattern)
{
}

bool StateNotInterval::Accept( char ch, SearchStateArray & array  )
{
	return !StateInterval::Accept(ch,array);
}

StateNotInterval::~StateNotInterval()
{
	//nothing
}