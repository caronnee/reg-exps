#include "stdafx.h"
#include "SearchStateArray.h"

SearchStateArray::SearchStateArray(): _n(0), _allocated(0), _states(NULL), _offset(0)
{
}

State * SearchStateArray::operator[](int index)
{
	index += _offset;
	if ( index < _n )
		return _states[index];
	return NULL;
}

int SearchStateArray::Size() const
{
	return _n - _offset;
}

void SearchStateArray::Clear()
{
	if (_states)
	{
		delete[] _states;
		_states = NULL;
	}
	_offset = 0;
	_n = 0;
	_allocated = 0;
}

SearchStateArray::~SearchStateArray()
{
	Clear();
}

void SearchStateArray::Resize( const int& newSize )
{
	if (_offset + _n > newSize)
	{
		for ( int i =0; i < Size(); i++)
		{
			_states[0] = _states[i + _offset];
		}
		_offset = 0;
	}
	else
	{
		DoAssert( newSize > _allocated );
		State ** nArray = new State* [newSize];
		memcpy(nArray,_states,_n*sizeof(State *));
		if (_states)
			delete[] _states;
		_states = nArray;
		_allocated = newSize;
	}
}

void SearchStateArray::Add( State * state )
{
	if ((_n + _offset) >= _allocated )
	{
		Resize(_allocated *2 + 1);
	}
	_states[_n] = state;
	_n++;
}

void SearchStateArray::RemoveLast(const int &len)
{
	_n-= len;
}

State *& SearchStateArray::Last()
{
	return _states[Size() -1];
}

void SearchStateArray::RemoveFirst(const int &len)
{
	_offset+=len;
}