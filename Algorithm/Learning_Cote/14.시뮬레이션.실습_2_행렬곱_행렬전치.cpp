#if 0
#include <string>
#include <vector>
#include <functional>

using namespace std;

struct Matrix
{
	Matrix(vector<vector<int>>&& InMat)
	{
        mat = std::move(InMat);
        row = mat.size();
        col = mat[0].size();
	}

    Matrix Transpose() const noexcept
    {
        vector<vector<int>> ret(col, vector<int>(row, -1));
        for (int y = 0; y < row; y++)
        {
            for (int x = 0; x < col; x++)
            {
                ret[x][y] = mat[y][x];
            }
        }
        return Matrix(std::move(ret));
    }

    Matrix operator*(const Matrix& other) const noexcept
    {
        Matrix t = other.Transpose();
        vector<vector<int>> ret(row, vector<int>(other.col));
        
        auto Dot = [&](const vector<int>& a, const vector<int>& b)
            {
                int sum = 0;
                for (int i = 0; i < a.size(); i++)
                {
                    sum += a[i] * b[i];
                }
                return sum;
            };

        for (int y = 0; y < row; y++)
        {
            for (int x = 0; x < other.col; x++)
            {
                ret[y][x] = Dot(mat[y], t.mat[x]);
            }
        }

        return Matrix(std::move(ret));
    }

	vector<vector<int>> mat;
	int row;
	int col;
};


void main()
{
	printf("14.시뮬레이션.실습_2_행렬곱_행렬전치");
	printf("\n\n\n");

    auto PrintMat = [&](vector<vector<int>> vecs)
        {
            for (vector<int>& vec : vecs)
            {
                for (int i : vec) printf("%2d ", i);
                printf("\n");
            }
            printf("\n");
        };

    vector<vector<int>> v1
    {
                     {1, 2, 3},
                     {4, 5, 6},
                     {7, 8, 9},
    };
    vector<vector<int>> v2 =

    {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1},
    };
    Matrix m1(std::move(v1));
    Matrix m2(std::move(v2));
    Matrix r1 = m1 * m2;
    Matrix tr1 = r1.Transpose();
    PrintMat(tr1.mat);
    /*
    출력값 :
    30 84 138
    24 69 114
    18 54 90
    */



    vector<vector<int>> v3 =
    {
        {2, 4 ,6},
        {1, 3, 5},
        {7, 8, 9},
    };
    vector<vector<int>> v4 =
    {
        {9, 1, 2},
        {4, 5, 6},
        {7, 3, 8},
    };
    Matrix m3(std::move(v3));
    Matrix m4(std::move(v4));
    Matrix r2 = m3 * m4;
    Matrix tr2 = r2.Transpose();
    PrintMat(tr2.mat);
    /*
    출력값:
    76 56 158
    40 31 74
    76 60 134
    */
}




#endif