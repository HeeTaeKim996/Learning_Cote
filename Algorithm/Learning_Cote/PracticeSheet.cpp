#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) 
{
    sort(people.begin(), people.end());

    int start = 0;
    int last = people.size() - 1;

    int answer = 0;
    int weight = 0;
    while (start <= last)
    {
        if (people[start] + people[last] <= limit)
        {
            start++;
            last--;
        }
        else
        {
            last--;
        }
        answer++;

    }

    

    

    return answer;
}