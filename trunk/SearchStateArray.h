#ifndef __SEARCH_STATE_ARRAY
#define __SEARCH_STATE_ARRAY

#include "SearchEngineCommon.h"

class State;

class DLL_REGEXP_EXPORT SearchStateArray
{
	/** \brief where the array starts */
	int _offset;

	/** \brief number of accesible elements */
	int _n;
	
	/** \brief Number of allocated elements */
	int _allocated;
	
	/** \brief Array of the states */
	State ** _states;

	/** \brief Resizes the array */
	void Resize( const int& newSize );
public:

	/** \brief size of the accesible array */
	int Size() const;

	/** \brief Constructor */
	SearchStateArray();
	
	/** \brief acces via index */
	State * operator[](int index);
	
	/* \brief Destroys everything allocated */
	void Clear();

	/** \brief adds value to the array */
	void Add( State * state );

	/** \brief removed first value from the array */
	void RemoveFirst(const int& i =1);

	/**\brief removed teh last element */
	void RemoveLast(const int & i = 1);

	/** \brief Return last added element */
	State *& Last();

	/** Destructor */
	~SearchStateArray();
};
#endif