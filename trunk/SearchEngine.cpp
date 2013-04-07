#include "stdafx.h"
#include "SearchEngine.h"
#include "Accept.h"
#include "Parser.h"

// TODO register all the states for later correct removal. Next is not enough, there can be comples expressions

SearchEngine::SearchEngine() : _flags(0), _state(NULL), _text(NULL), _textIndex(0)
{
	_actual.Clear();
}

void SearchEngine::SetOptions( int flags )
{
	_flags = flags;
}

void SearchEngine::SetToken(const char * text)
{
	if (!_state)
		return;
	_state->Clear();
	_actual.Clear();
	int len = strlen(text);
	if (_text)
		delete[] _text;
	len++;
	_text = new char [len];
	memcpy( _text, text, sizeof(char)*len );// copy also the last sign
	_textIndex = 0;
}
int SearchEngine::Search( const char * text, int & size )
{
	if (!_state)
		return -1;
	SetToken(text);
	return Continue(size);
}

int SearchEngine::Continue( int & size )
{
	if (!_text)
		return -1;
	int len = strlen( _text );
	int res = -1;
	while ( (_textIndex < len) && ( res < 0 ) )
	{
		_actual.Add(_state); // from the beginning again and again	
		int n = _actual.Size();		
		// if any of the current states is final, we've found the ocurence. 
		for ( int i = 0; i<n ; i++ )
		{
			if ( _actual[i]->Accept(_text[_textIndex], _actual) )
			{
				res = _textIndex;
				size = _actual[i]->GetSize();
				res -= size;
			}
		}
		_actual.RemoveFirst(n);
		_textIndex++;
	}
	return res;
}

void SearchEngine::SetPattern( const char * pattern )
{
	int len = strlen(pattern);
	char * copyPattern = new char[len];
	memcpy(copyPattern, pattern, len);
	Parser parser;
	_state = parser.Parse(copyPattern,len);
	_actual.Clear();
	delete[] copyPattern;
}

void SearchEngine::Clear()
{
	_flags = 0;
	_actual.Clear();
	while(_state)
	{
		State * s = _state;
		_state = _state->Next();
		delete s;
	}
	
	if (_text)
	{
		delete[] _text;
		_text = NULL;
	}
}

SearchEngine::~SearchEngine()
{
	Clear();
}