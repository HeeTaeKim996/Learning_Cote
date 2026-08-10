#if 0
/*
    - 엑셀 컬럼 넘버링에 대표되는, 0 의 개념이 없는 넘버링 <-> 10진수 변환 알고리즘

    - 변환 알고리즘은 난해한데, 난 그나마 아래 방법이 이해되더라

    - 'y' == 25, 'z' == 26, 'aa' == 27 로, 알파벳에서 0 을 나타내는 값이 없다. 따라서 '0' == 0, 'a0' == 27 이 아니게 된다.
    - 0이 없는데, a..z 는 26개 이니, 엑셀 컬럼 넘버링은 0이 없는, 26진수 로 이해할 수 있다.

    - 위 특성으로 인해, 'a' ... 'y' 에서는 오류가 없지만, 'z' 를 Num -> Col 로 할 때, 오류가 생긴다.
     -> 예를들어, 아래 알고리즘에서 Col -> Num 으로 'z'를 변환하면, 26 이 된다. 하지만 Num -> Col 은 % 26, /= 26.. 으로 계산하기 때문에, 'z' 를 'a'' 로 읽어드리는 오류가 생긴다.
        즉 0이 있는 진수의 개념에서 'z' - 'a0' - 'aa' 에서, 'a0' 이 빠졌기 때문에, 이부분을 정정해야 한다.
        따라서 NumToColumn 함수에서 num % 26 == 0 일 경우에 한해서, += 'z', num--; 처리를 해줘야 한다.

    - 글로 적으니 복잡하게 느껴지는데, 정리하면,
      엑셀 컬럼 너버링은 0 이 없는 26 진수라 보면 되고, 이 특성으로 인해 0 이 있는 n진수와의 변환에서 누락 되는 부분이 생긴다.
      이 누락되는 부분은 k진수에서 k 번째 문자에 있기 때문에, 이 k 번째 문자에 한해서, 특별한 처리가 필요하다
*/




#include <string>
#include <vector>
#include <functional>
#include <algorithm>


using namespace std;
using int64 = long long;

string solution(long long n, vector<string> bans)
{
    auto ColumnToNum = [](const string& column) -> int64
        {
            int64 num = 0;
            int64 mul = 1;
            for (int i = column.size() - 1; i >= 0; i--)
            {
                num += (column[i] - 'a' + 1) * mul;
                mul *= 26;
            }

            return num;
        };

    auto NumToColumn = [](int64 num) -> string
        {
            string column = "";
            while (num > 0)
            {
                int res = num % 26;
                if (res == 0)
                {
                    column += 'z';
                    num--;
                }
                else
                {
                    column += 'a' + res - 1;
                }
                num /= 26;
            }
            return string(column.rbegin(), column.rend());
        };

#if 0
    auto Debug = [&](string test) -> void
        {
            int64 num = ColumnToNum(test);
            string reg = NumToColumn(num);
            printf("%lld, %s \n", num, reg.c_str());
        };
    string t1 = "y"; Debug(t1);
    string t2 = "z"; Debug(t2);
    string t3 = "aa"; Debug(t3);
#endif

    auto Compare = [](const string& a, const string& b) -> bool
        {
            if (a.length() != b.length()) return a.length() < b.length();
            return a < b;
        };
    sort(bans.begin(), bans.end(), Compare);

    for (int i = 0; i < bans.size(); i++)
    {
        if (ColumnToNum(bans[i]) > n) break;
        n++;
    }

    return NumToColumn(n);
}

int main()
{
    printf("999.기타_6_엑셀컬럼넘버링");
    printf("\n\n\n");

    int n1 = 30;
    vector<string> bans1 = { "d", "e", "bb", "aa", "ae" };
    printf("%s \n", solution(n1, bans1).c_str());
    // ah


    int n2 = 7388;
    vector<string> bans2 = { "gqk", "kdn", "jxj", "jxi", "fug", "jxg", "ewq", "len", "bhc" };
    printf("%s \n", solution(n2, bans2).c_str());
    // jxk

    return 0;
}

#endif