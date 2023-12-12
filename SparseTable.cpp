#include <bits/stdc++.h>
using namespace std;

int sparse(vector<int> &a)
{
    int n = a.size();
    int logn = log2(n) + 1;
    vector<vector<int>> sparseTable(n, vector<int>(logn));

    for (int i = 0; i < n; i++)
    {
        sparseTable[i][0] = a[i];
    }

    for (int j = 1; j < logn; j++)
    {
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
        }
    }
}
