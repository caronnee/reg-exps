#include "stdafx.h"
#include "AcceptSimple.h"
#include "SearchStateArray.h"

State::State() : _size(0) {}


State * State::Next() { return NULL; }

void State::SetNext( State * state ) {}

void State::SetSize( int size )
{
	_size = size + 1;
}

void State::NotAccept()
{
	_size = 0;
}

int State::GetSize() const
{
	return _size;
}

bool State::IsFinal()
{
	return false;
}

void State::Clear()
{
	_size = 0;
}

bool State::Accept( SearchStateArray & array, State * state )
{
	array.Add( state );
	state->SetSize( _size );
	return state->IsFinal();
}