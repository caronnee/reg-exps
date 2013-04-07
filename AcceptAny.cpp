#include "stdafx.h"
#include "AcceptAny.h"

StateAnyChar::StateAnyChar(){}

bool StateAnyChar::Accept(char ch, SearchStateArray & cands)
{
	return State::Accept(cands,Next());
}

StateAnyChar::~StateAnyChar() { }