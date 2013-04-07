#include "stdafx.h"
#include "parser.h"
#include "AcceptSimple.h"
#include "AcceptAny.h"
#include <vector>

#define MAKE_PARSE_VALUE(name, ch, prio, len) { Special##name, ch, prio, len, NULL },
#define GENERATE_SWITCH(name, ch, priority, len ) case Special##name: \
{ \
	int index=0, patternLen=0;\
	Process##name(stack.back());	\
	stack.pop_back();	\
	break; \
}

#define CREATE_DUMMY_PROCESS(name, ch, priority, len) \
	void Parser::Process##name( const ParseValue& value) { }

SPECIALS_WAITING(CREATE_DUMMY_PROCESS)

Parser::Parser() 
{
	_array.Clear();
}

void Parser::ProcessStack(Stack & stack, int stopPriority)
{
	while ( !stack.empty() && (stack.back().priority >= stopPriority) )
	{
		DoAssert(!stack.empty());
		switch(stack.back().flag)
		{
			SPECIALS(GENERATE_SWITCH)
		default:
			DoAssert(false);
		}
	}
}

ParseValue Parser::GetParseValue(char * pattern, int& patternIndex)
{
	static ParseValue parseValue[] = { SPECIALS(MAKE_PARSE_VALUE) };
	ParseValue ret = parseValue[SpecialSimple];
	for ( int pIndex =0; pIndex < NSpecialChars ; pIndex++ )
		{
			if (parseValue[pIndex].var == pattern[patternIndex] )
				ret = parseValue[pIndex];
		}
	ret.parameter = &pattern[patternIndex];
	return ret;
}

State * Parser::Parse( char * pattern, int& len )
{	
	std::vector<ParseValue> stack;

	ParseValue stopMark = {SpecialStopMark, -1, -1};
	stack.push_back(stopMark);
	_array.Add( new StateFinal() );
	int patternIndex = 0;
	while ( true )
	{
		if ( patternIndex == len )
			break;

		// find priority
		ParseValue val = GetParseValue(pattern, patternIndex);
		
		while ( stack.back().priority > val.priority ) // we can add only higher priority
		{
			ProcessStack(stack, val.priority );
		}
		
		ParseValue value(val);
		value.var = patternIndex;
		stack.push_back(value);
		patternIndex += value.len;
	}
	ProcessStack( stack,-1 );
	DoAssert( stack.empty() );
	DoAssert(_array.Size() == 1);
	return _array[0];
}

void Parser::ConcatState(State  * state)
{
	state->SetNext(_array.Last());
	_array.Last() = state;
}

/** Process methods */
void Parser::ProcessStopMark(const ParseValue & value)
{
	if (_array.Size() <2)
		return; // nothing to concatenate
	State * last = _array.Last();
	_array.RemoveLast();
	_array.Last()->SetNext(last);
}
void Parser::ProcessSimple(const ParseValue & value)
{
	DoAssert(value.len == 1);
	StateSearch  * state = new StateSearch(*value.parameter);
	ConcatState(state);
}
void Parser::ProcessDotMark(const ParseValue & value)
{
	DoAssert(value.len == 1);
	StateSearch * state = new StateAnyChar();
	ConcatState(state);
}