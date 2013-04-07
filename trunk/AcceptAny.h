#ifndef __ACCEPT_ANY__
#define __ACCEPT_ANY__

#include "AcceptSimple.h"

/** Accepts any char */
class StateAnyChar : public StateSearch
{
public:
	/** \brief Constructor */
	StateAnyChar();

	/** \brief returns true if this is end state */
	virtual bool Accept( char c, SearchStateArray& candidates );

	/** \brief Destructor */
	virtual ~StateAnyChar();
};

#endif