#if 0

#include<vector>
#include <string>
#include <queue>
#include <functional>
using namespace std;


/*
    - 하단은 코테 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/1844  의 내용이다.
    - Dfs를 활용한 최단거리는, 게임의 네브메시에도 사용되는 개념이라 하여, 따로 정리했다.
    - 우선 위 코테문제와도 연관하여, Node 를 포인터로 가지면, 캐시 효율이 떨어져, 성능 100 으로 안나온다. 따라서 아래 코드처럼, Node를 2차원의 배열로 직접 들고 있어야 하고, Pos 로 현재 위치를 갱신하고, Node& 를 가져오는데 사용해야 한다.
    - 기존 그래프 에서는 From 에서 vector 또는 map 으로 to 들을 가지고 있어야 하지만, 최단거리에서는 캐시 성능을 좋게 하기 위해, 가변데이터를 갖고 있지 않고, to 에서 from 의 위치를 저장하여, 최단경로 를 기록해야 한다.
    - 아래에서 IsPossible에 주목해서, 반드시 IsPossible의 체크 대상 항목에, IsPossible 일 때에 Node에 변경하는 요소가 있어야 한다. 아래에서는 dist가 해당된다. 만약 그렇게 하지 않으면, queue 는 너비탐색이기 때문에, queue 에 중복된 Pos가 들어간다 ( 자식이 아닌, 손자 세대부터 )
    
    - 네브메시도 Dfs를 기반으로 한다고 함 (지피티) 큐가 아닌, Priority Queue 로, Bfs 의 직선도 아니고, Dfs의 펑퍼짐한 넓이도 아닌, 목표 방향을 향한 비대칭적 넓이 형태로 나아간다 한다. 정확한 구현 방법은 모른다.
      또한 네브메시도, Node를 2차원의 배열형태로 저장하여, 캐시친화적인 빠른 연산을 한다 함 (2.5D에서)
*/






struct Pos
{
    Pos(int InY, int InX) : y(InY), x(InX) {}
    Pos() {}

    bool operator==(const Pos& other) const noexcept
    {
        return y == other.y && x == other.x;
    }

    int y;
    int x;
};

struct Node
{
    int dist = INT32_MAX;
    bool passable = false;
    Pos prev; // 문제랑은 무관하지만, 경로 저장 용도
};

struct Graph
{
    void Initialize(const vector<vector<int>>& maps, const int yMax, const int xMax)
    {

        nodes = vector<vector<Node>>(yMax + 1, vector<Node>(xMax + 1));
        for (int y = 0; y < yMax + 1; y++)
        {
            for (int x = 0; x < xMax + 1; x++)
            {
                if (maps[y][x] == 1)
                {
                    nodes[y][x].passable = true;
                }
            }
        }
    };

    int Dfs(const vector<vector<int>> maps, Pos start, Pos end)
    {
        int yMax = maps.size() - 1;
        int xMax = maps[0].size() - 1;

        Initialize(maps, yMax, xMax);

        queue<Pos> q;
        q.push(start);

        nodes[start.y][start.x].dist = 0;

        auto IsPossible = [&](int y, int x)
            {
                if (y < 0 || y > yMax || x < 0 || x > xMax) return false;

                const Node& aimNode = nodes[y][x];

                if (aimNode.passable == false) return false;

                if (aimNode.dist != INT32_MAX) return false;

                return true;
            };
        int dir[4][2] =
        {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0}
        };

        while (!q.empty())
        {
            Pos curr = q.front();
            q.pop();

            if (curr == end)
            {
                { // 문제랑은 무관하지만, 경로 보여주기
#if 1
                    Pos temp = curr;
                    while (true)
                    {
                        printf("%d, %d // ", temp.y, temp.x);
                        temp = nodes[temp.y][temp.x].prev;
                        if (nodes[temp.y][temp.x].dist == 0) break;
                    }
#endif
                }
                return nodes[curr.y][curr.x].dist + 1;
            }

            for (const auto& d : dir)
            {
                if (IsPossible(curr.y + d[0], curr.x + d[1]))
                {
                    Pos aimPos(curr.y + d[0], curr.x + d[1]);
                    Node& node = nodes[aimPos.y][aimPos.x];
                    node.dist = nodes[curr.y][curr.x].dist + 1;

                    node.prev = curr; // 문제랑은 무관하지만, 경로 저장 용도

                    q.push(aimPos);
                }
            }
        }

        return -1;
    }

    vector<vector<Node>> nodes;
};


int solution(vector<vector<int> > maps)
{
    Graph graph;

    int answer = graph.Dfs(maps, Pos(0, 0), Pos(maps.size() - 1, maps[0].size() - 1));
    return answer;
}


void main()
{
    printf("11.그래프.알고리즘_최단거리");
    printf("\n\n\n");


}



#endif