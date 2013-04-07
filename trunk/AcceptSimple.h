#ifndef __ACCEPT_SIMPLE
#define __ACCEPT_SIMPLE

#include "Accept.h"

class StateSearch : public State
{
protected:
	// next state
	State * _state;

	// what it should match
	char _ch;
	
public:

	/** \brief constructor */
	StateSearch(char c = 0);

	State * Next();

	void SetNext(State * state);

    bool Accept( char c, SearchStateArray & array );

	/** Destructor */
	virtual ~StateSearch();
};

class StateIntervalSimple : public StateSearch
{
	int _start, _end;

public:
	StateIntervalSimple():_start(0), _end(0)
	{}
};

class StateInterval: public StateSearch
{
	SearchStateArray _intervals;

public:
	StateInterval(const char * pattern);
	virtual bool Accept( char c, SearchStateArray& candidates );
	virtual ~StateInterval();
	void Validate(char * pattern);
};

class StateAnyChar:public StateSearch
{
public:
	StateAnyChar();
	virtual bool Accept( char c, SearchStateArray& candidates );
	virtual ~StateAnyChar();
};

class StateNotInterval : public StateInterval
{
public:
	StateNotInterval(const char * pattern);
	virtual bool Accept( char c, SearchStateArray& candidates );
	virtual ~StateNotInterval();
};

class StateOr : public StateSearch
{
	SearchStateArray _array;
public:
	StateOr(const char * pattern);
	void Clear();
	virtual bool Accept( char c, SearchStateArray& candidates );
	virtual ~StateOr();
};

#endif