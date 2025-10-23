#if 0
#include <string>
#include <queue>

using namespace std;


void main()
{
	printf("07.큐.필수문법");
	printf("\n\n\n");

	queue<int> q;

	// Push
	q.push(10);
	q.push(20);
	q.push(30);
	

	// Front
	int i = q.front(); 
	printf("%d \n", i);

	// Pop
	q.pop();
	printf("%d \n", q.front());

	// Empty
	bool b = q.empty();
	printf("%d \n", b);

}

#endif