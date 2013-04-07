#include "SearchEngine.h"
#include <iostream>

int GErrors = 0;
#if _DEBUG
#define BREAK_INTO_CODE __debugbreak()
#else
#define BREAK_INTO_CODE
#endif

#define DoAssert(val) if (!(val)) { GErrors++; BREAK_INTO_CODE; }

#include <vector>

void Test(const char * token, const char * pattern, int desiredOutput)
{
	SearchEngine engine;
	engine.SetPattern(pattern);

	engine.SetToken(token);
	int found = 0;
	int size = -1;
	while (true)
	{
		int index = engine.Continue(size);
		if ( index < 0 )
			break;
		printf("Found at %s\n", &token[index]);

		found++;
	}
	
	//DoAssert( found == desiredOutput );
	printf( "Found recurences : %d. %s\n", found, found == desiredOutput ? "Correct":"Fail" );
}

int main()
{
	// token,
	Test("ababbbaaabxbgb","b.b",4);
	Test("aaataaabab","aa",4);
	Test("abababba","bab",2);
	return 0;
}