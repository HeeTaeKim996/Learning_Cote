#pragma once
#include <string>

// бс FLAG
#define FLAG_USE_WSTRING



#ifndef FLAG_USE_WSTRING

#define STRING string
#define CHAR char
#else

#define STRING wstring
#define CHAR wchar_t

#endif


class StringMatch
{
public:
	static void test();

public:
	static int BruoteForce(const STRING& txt, const STRING& search);

	static int KMP(const STRING& txt, const STRING& search);

	static int BoyerMoor(const STRING& txt, const STRING& search);
};





