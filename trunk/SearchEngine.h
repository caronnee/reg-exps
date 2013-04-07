#include "SearchEngineCommon.h"
#include "SearchStateArray.h"

class StateSearch;

class DLL_REGEXP_EXPORT SearchEngine
{
	/** text to search */
	char * _text;

	/** where in the text we are */
	int _textIndex;

	/** flags how should searchEngine behave - concatenate hyphen, lowercase evrything..? */
	int _flags;
	
	/** \brief head of the search ( when nothing is passed ) */
	State * _state;
	
	/** Actual state when the word can belong */
	SearchStateArray _actual;

	/** Clear state */
	void Clear();

public:

	enum Options
	{
		CaseSensitive,
		ConcateHyphen,
	};
	
	/** Constructor */
	SearchEngine();

	/** What to search */
	void SetPattern(const char * pattern);

	/**  Token to search through */
	void SetToken(const char * text);

	/** Set options */
	void SetOptions(int flags);

	/** \brief Search */
	/** It cleans itself instead of continueing where it ended. */
	int Search(const char * text, int & size);

	/** Continue */
	int Continue( int & size );

	~SearchEngine();
};