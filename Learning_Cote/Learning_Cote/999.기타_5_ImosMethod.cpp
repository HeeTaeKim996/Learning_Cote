#if 0
#include <string>
#include <vector>
#include <functional>

using namespace std;


int Imos2D(vector<vector<int>> board, vector<vector<int>> skill)
{
    int yMax = board.size() - 1;
    int xMax = board[0].size() - 1;

    vector<vector<int>>imos(yMax + 2, vector<int>(xMax + 2, 0));

    auto PaintPoint = [&](const vector<int>& sk)
        {
            int val = sk[0] == 1 ? -sk[5] : sk[5];

            imos[sk[1]][sk[2]] += val;
            imos[sk[1]][sk[4] + 1] -= val;
            imos[sk[3] + 1][sk[2]] -= val;
            imos[sk[3] + 1][sk[4] + 1] += val;
        };


    auto Paint = [&]()
        {
            // 가로 페인트
            for (int y = 0; y <= yMax; y++)
            {
                for (int x = 1; x <= xMax; x++)
                {
                    imos[y][x] += imos[y][x - 1];
                }
            }

            // 세로 페인트
            for (int x = 0; x <= xMax; x++)
            {
                for (int y = 1; y <= yMax; y++)
                {
                    imos[y][x] += imos[y - 1][x];
                }
            }
        };



    auto Debug = [&]()
        {
            for (int y = 0; y < yMax + 2; y++)
            {
                for (int x = 0; x < xMax + 2; x++) printf("%2d ", imos[y][x]);
                printf("\n");
            }
            printf("\n");
        };


    for (const vector<int>& sk : skill)
    {
        PaintPoint(sk);
    }
    Paint();

    int answer = 0;
    for (int y = 0; y <= yMax; y++)
    {
        for (int x = 0; x <= xMax; x++)
        {
            int val = board[y][x] + imos[y][x];
            if (val > 0) answer++;
        }
    }

    return answer;
}
    
int Imos1D(vector<int> enters, vector<int> exits)
{
    int max = -INT32_MAX;
    for (int i : exits) if (i > max) max = i;

    vector<int> imos(max + 2, 0);

    auto MakePoint = [&](int enter, int exit)
        {
            imos[enter] += 1;
            imos[exit + 1] -= 1;
        };
    auto Paint = [&]()
        {
            for (int i = 1; i <= max; i++)
            {
                imos[i] += imos[i - 1];
            }
        };

    for (int i = 0; i < enters.size(); i++)
    {
        MakePoint(enters[i], exits[i]);
    }
    Paint();

    int ret = -INT32_MAX;
    for (int i = 0; i <= max; i++)
    {
        if (imos[i] > ret) ret = imos[i];
    }

    return ret;
}


void main()
{
	printf("999.기타_5_ImosMethod");
	printf("\n\n\n");


    vector<vector<int>> board1 = {
        {5, 5, 5, 5, 5},
        {5, 5, 5, 5, 5},
        {5, 5, 5, 5, 5},
        {5, 5, 5, 5, 5}
    };

    vector<vector<int>> skill1 = {
        {1, 0, 0, 3, 4, 4},
        {1, 2, 0, 2, 3, 2},
        {2, 1, 0, 3, 1, 2},
        {1, 0, 1, 3, 3, 1}
    };
    printf("Imos2D : %d \n", Imos2D(board1, skill1));
    // result = 10



    // 2번 테스트 케이스
    vector<vector<int>> board2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<vector<int>> skill2 = {
        {1, 1, 1, 2, 2, 4},
        {1, 0, 0, 1, 1, 2},
        {2, 2, 0, 2, 0, 100}
    };
    printf("Imos2D : %d \n", Imos2D(board2, skill2));
    // result = 6


    // Imos 1D
    vector<int> s = { 0, 2, 5, 8 };  // 손님 i의 입장 시간
    vector<int> e = { 3, 6, 7, 9 };  // 손님 i의 퇴장 시간
    printf("Imos1D : %d \n", Imos1D(s, e));
    // result = 2

}




#endif