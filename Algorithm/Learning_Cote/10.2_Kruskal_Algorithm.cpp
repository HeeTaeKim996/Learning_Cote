#if 0

#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct Node
{
    int rank = 0;
    Node* root = nullptr;
};

struct Set
{
    static Node* getRoot(Node* node)
    {
        if (node->root == nullptr) return node;

        node->root = getRoot(node->root);

        return node->root;
    }

    static bool unionNodes(Node* a, Node* b)
    {
        Node* rootA = getRoot(a);
        Node* rootB = getRoot(b);

        if (rootA == rootB) return false;

        if (rootA->rank < rootB->rank)
        {
            rootA->root = rootB;
        }
        else if (rootA->rank > rootB->rank)
        {
            rootB->root = rootA;
        }
        else
        {
            rootB->root = rootA;
            rootA->rank++;
        }

        return true;
    }
};



int solution(int n, vector<vector<int>> costs)
{
    vector<Node*> nodes;
    nodes.reserve(n);
    while (n-- > 0)
    {
        nodes.push_back(new Node());
    }

    auto compare = [](const vector<int>& v1, vector<int>& v2) -> bool
        {
            return v1[2] < v2[2];
        };
    sort(costs.begin(), costs.end(), compare);

    //for (vector<int>& v : costs) { printf("(%d, %d, %d)\n",v[0], v[1], v[2]); }

    int answer = 0;
    for (const vector<int>& cost : costs)
    {
        if (Set::unionNodes(nodes[cost[0]], nodes[cost[1]]))
        {
            answer += cost[2];
        }
    }


    return answer;
}



int main()
{
    printf("10.2_Kruskal_Algorithm\n\n\n");


    // 유명한 Kruskal 알고리즘이다. 라우터간 최소비용 연결 문제 해결법으로 대표적이다.
    
    // 원리는 간단하다.
    // 1) sort 로 cost 를 오름차순으로 정렬
    // 2) set 을 사용하여, A-B 가 연결되있지 않다면(root 가 같지 않다면) 비용을 들여 연결


    /*
    https://school.programmers.co.kr/learn/courses/30/lessons/42861
   
    costs[i][0] = 섬 인덱스 1
    costs[i][1] = 섬 인덱스 2
    costs[i][2] = 연결 비용
    */


    // 예제 1
    int n1 = 4;
    vector<vector<int>> costs1 =
    {
        {0, 1, 1},
        {0, 2, 2},
        {1, 2, 5},
        {1, 3, 1},
        {2, 3, 8}
    };

    int result1 = solution(n1, costs1);
    printf("%d\n", result1);
    // result1 == 4


    // 예제 2
    int n2 = 5;
    vector<vector<int>> costs2 =
    {
        {0, 1, 5},
        {1, 2, 3},
        {2, 3, 3},
        {3, 1, 4},
        {2, 4, 6},
        {4, 0, 7}
    };

    int result2 = solution(n2, costs2);
    // result2 == 17
    printf("%d\n", result2);

    return 0;
}

#endif