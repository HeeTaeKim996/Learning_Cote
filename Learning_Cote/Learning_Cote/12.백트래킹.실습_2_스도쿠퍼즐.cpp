#if 0
#include <string>
#include <vector>
#include <set>
#include <functional>

using namespace std;

bool Dfs(vector<vector<int>>& v, int index)
{
    if (index == 81) return true;

    int y = index / 9;
    int x = index % 9;

    auto MakeReserve = [&](int py, int px)
        {
            set<int> res = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            for (int y = 0; y < 9; y++)
            {
                int num = v[y][px];
                if (num == 0) continue;
                auto it = res.find(num);
                if (it != res.end()) res.erase(it);
            }
            for (int x = 0; x < 9; x++)
            {
                int num = v[py][x];
                if (num == 0) continue;
                auto it = res.find(num);
                if (it != res.end()) res.erase(it);
            }
            int sy = ( py / 3 ) * 3;
            int sx = (px / 3) * 3;
            for (int y = sy; y < sy + 3; y++)
            {
                for (int x = sx; x < sx + 3; x++)
                {
                    int num = v[y][x];
                    if (num == 0) continue;
                    auto it = res.find(num);
                    if (it != res.end()) res.erase(it);
                }
            }

            return res;
        };
    if (v[y][x] == 0)
    {
        set<int> ret = MakeReserve(y, x);
        for (int i : ret)
        {
            v[y][x] = i;
            if (Dfs(v, index + 1) == true) return true;
        }
        v[y][x] = 0;
    }
    else
    {
        if (Dfs(v, index + 1) == true) return true;
    }
    

    return false;
}



vector<vector<int>> solution(vector<vector<int>> v)
{
    if (Dfs(v, 0) == true)
    {
        printf("Succeed\n");
    }
    else
    {
        printf("Failed\n");
    }

    return v;
}

int main()
{
    printf("12.백트래킹.실습_2_스도쿠퍼즐");
    printf("\n\n\n");

    vector<vector<int>> v1 = 
    {
                      {5, 3, 0, 0, 7, 0, 0, 0, 0},
                      {6, 0, 0, 1, 9, 5, 0, 0, 0},
                      {0, 9, 8, 0, 0, 0, 0, 6, 0},
                      {8, 0, 0, 0, 6, 0, 0, 0, 3},
                      {4, 0, 0, 8, 0, 3, 0, 0, 1},
                      {7, 0, 0, 0, 2, 0, 0, 0, 6},
                      {0, 6, 0, 0, 0, 0, 2, 8, 0},
                      {0, 0, 0, 4, 1, 9, 0, 0, 5},
                      {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    vector<vector<int>> v2 = 
    {
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    auto Test = [](vector<vector<int>> v)
        {
            vector<vector<int>> ret = solution(v);
            for (int y = 0; y < 9; y++)
            {
                for (int x = 0; x < 9; x++)
                {
                    printf("%d ", ret[y][x]);
                }
                printf("\n");
            }
            printf("\n");
        };

    Test(v1);
    Test(v2);

    return 0;
}



#endif