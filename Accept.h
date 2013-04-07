#ifndef ___ACCEPTS___
#define ___ACCEPTS___

#include "SearchStateArray.h"

class State
{
	// minimal number of states we had to pass
	int _size;

protected:
	
	// size
	void SetSize( int size );

	// what happens when this is not accepted
	void NotAccept();

	// set this state as accepted
	bool Accept( SearchStateArray & array, State * state );
public:
    /** Constructor */
	State();

	/** next state */
	State * Next();

	/** */
	virtual void SetNext(State * state) = 0;

	/** \brief return true if there is nothin else to go ( final state ) */
	virtual bool Accept( char c, SearchStateArray& candidates ) = 0;

	/** check if this is final state */
	virtual bool IsFinal();

	virtual void Clear();

	// minimal size that this
	int GetSize() const;
};

class StateFinal : public State
{
public:
	StateFinal(): State() { }
	virtual bool Accept( char c, SearchStateArray& candidates ) { return false; }
	// virtual function
	void SetNext(State * state) {}
	virtual bool IsFinal() { return true; }
	virtual ~StateFinal() {} // do nothing
};


#endif // ___ACCEPTS___