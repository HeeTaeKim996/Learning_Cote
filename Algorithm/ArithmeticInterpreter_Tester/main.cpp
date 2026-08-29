#include "stdafx.h"
#include "Parser.h"


void test(string query)
{
    Parser::instance()->parse(query);
}

int main()
{
	test("4 + 7.5");
	test("(4 - 2) * 3.5");
}

