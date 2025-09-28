#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<vector<int>> findNumber(int*** mtrx, int l, int m, int n, int z)
{
    vector<vector<int>> result;

    for (int i = 0; i < l; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
            {
                if (mtrx[i][j][k] == z)
                    result.push_back(vector<int>{i, j, k});
            }
    return result;
}

void test1task()
{
    int*** mtrx = new int**[10];
    for (int i = 0; i < 10; i++)
    {
        mtrx[i] = new int*[10];
        for (int j = 0; j < 10; j++)
        {
            mtrx[i][j] = new int[10];
            for (int k = 0; k < 10; k++)
            {
                mtrx[i][j][k] = rand() % 100;
            }
        }
    }

    int z = 4;
    vector<vector<int>> findings = findNumber(mtrx, 10, 10, 10, z);
    cout << findings.size() << endl;
}

//-----------------------------------------------------------------------

class Matrix
{
private:
    int** matrix;
    int size;

    void clear()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrix[i][j] = 0;
    }
public:
    Matrix(int size)
    {
        this->size = size;
        matrix = new int*[size];
        for (int i = 0; i < size; i++)
        {
            matrix[i] = new int[size];
        }
        clear();
    }
    void fillClockwise()
    {
        clear();
        int t = 0, b = size - 1, l = 0, r = size - 1;
        int c = 1;
        int x, y;
        bool completed = false;
        while(!completed)
        {
            // top row
            if (l > r) break;
            y = t;
            for (x = l; x <= r; x++)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            if (completed) break;
            t++;

            // right row
            if (t > b) break;
            x = r;
            for (y = t; y <= b; y++)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            if (completed) break;
            r--;

            // bottom row
            y = b;
            for (x = r; x >= l; x--)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            if (completed) break;
            b--;

            // left row
            x = l;
            for (y = b; y >= t; y--)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            l++;
        }
    }
    void fillCounterClockwise()
    {
        clear();
        int t = 0, b = size - 1, l = 0, r = size - 1;
        int c = 1;
        int x, y;
        bool completed = false;
        while(!completed)
        {
            // top row
            if (l > r) break;
            y = t;
            for (x = r; x >= l; x--)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            if (completed) break;
            t++;

            // left row
            x = l;
            for (y = t; y <= b; y++)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            l++;

            // bottom row
            y = b;
            for (x = l; x <= r; x++)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            if (completed) break;
            b--;

            // right row
            if (t > b) break;
            x = r;
            for (y = b; y >= t; y--)
            {
                if (matrix[y][x] > 0)
                {
                    completed = true; break;
                }
                matrix[y][x] = c;
                c++;
            }
            if (completed) break;
            r--;
        }
    }
    void print()
    {
        int length = 0;
        int vol = size * size;
        while (vol > 0)
        {
            vol = vol / 10;
            length++;
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << setfill('0') << setw(length) << matrix[i][j] << " " ;
            }
            cout << endl;
        }
    }
};

void test2()
{
    int size = 3 + rand() % 15;
    Matrix matrix(size);
    if (rand() % 2 == 1)
        matrix.fillCounterClockwise();
    else
        matrix.fillClockwise();
    matrix.print();
}

int main()
{
    srand(time(NULL));
    test2();
    return 0;
}


