#if 0

#include <iostream>
#include <string>

using namespace std;

void main()
{
	printf("04.필수문법_1_문자열_기본문법\n\n");


	// 문자열 찾기
	{
		string str = "Hello, C++ World!";

		size_t pos1 = str.find("Hello");
		cout << pos1 << endl; // 0

		size_t pos2 = str.find("C");
		cout << pos2 << endl; // 7

		size_t startIndex = 2;
		size_t pos3 = str.find("Hello", startIndex);
		cout << (pos3 == string::npos) << endl; // Cant Find

		printf("\n\n\n");

	}



	// 문자열 수정
	{
		string str = "APPLE";
		str += ", World!";
		cout << str << endl;

		str[7] = 'P';
		cout << str << endl;

		str.replace(0, 5, "Bye");
		cout << str << endl;
	}
}



#endif
