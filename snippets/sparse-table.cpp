#include <bits/stdc++.h>
using namespace std;

class Sparse
{
    vector<vector<int>> table;
    int n;
    int K;

public:
    Sparse(const vector<int> &arr)
    {
        n = arr.size();
        K = log2(n) + 1;
        table.assign(n, vector<int>(K, 0));

        for (int i = 0; i < n; ++i)
        {
            table[i][0] = arr[i];
        }

        for (int j = 1; j < K; ++j)
        {
            for (int i = 0; i + (1 << j) <= n; ++i)
            {
                table[i][j] = table[i][j - 1] | table[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int query(int L, int R)
    {
        int width = R - L + 1;
        int k = log2(width);
        int result = table[R - (1 << k) + 1][k] | table[L][k];
        return result;
    }
};
