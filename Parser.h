#ifndef __REGEXP_PARSER
#define __REGEXP_PARSER

#include "Accept.h"
#include "SearchStateArray.h"
#include <vector>

// priority - 100 - not important, just end marks
// 0 must be processed as first

#define SPECIALS(XX) \
	SPECIALS_IMPLEMENTED(XX) \
	SPECIALS_WAITING(XX)

#define SPECIALS_IMPLEMENTED(XX) \
	XX(StopMark, '\0', 50, 0 ) \
	XX(Simple, '\0', 50, 1 ) \
	XX(DotMark, '.', 50, 1 ) \


#define SPECIALS_WAITING(XX) \
	XX(QMark, '?', 1, 1 ) \
	XX(Slash, '\\', 50, 2 )	\
	XX(Plus,'+', 1, 1 )	\
	XX(Star,'*', 1, 1 )	\
	XX(RSetBracket, '}', 1, 1 ) \
	XX(RBracket, ']', 1, 1 )	\
	XX(LCurly, ')', 1, 1 )	\
	XX(RCurly, '(', 2, 1 ) \
	XX(LBracket, '[', 2, 1 )	\
	XX(LSetBracket, '{', 2, 1 ) \

#define CREATE_ENUM(name, ch, priority, len)	Special##name,
#define CREATE_FCE_HEADERS(name, ch, priority, len) \
	void Process##name(const ParseValue & value);	\

enum SpecialChars
{
	SPECIALS(CREATE_ENUM)
	NSpecialChars
};

struct ParseValue
{
	SpecialChars flag;
	int var;
	int priority;
	int len;
	char* parameter;
	// defalut constructor does exactly what we want
};

typedef std::vector<ParseValue> Stack;

class Parser
{
	SearchStateArray _array;

	void ConcatState(State * state);

public:
	Parser();

	void ProcessStack(Stack & stack, int stopPriority);

	ParseValue GetParseValue(char * pattern, int& patternIndex );

	/** Creates head of the subtree. Return shead of the subtre*/
	State * Parse( char * pattern, int& len );

	/** Helper process function */
	SPECIALS(CREATE_FCE_HEADERS);
};
#endif