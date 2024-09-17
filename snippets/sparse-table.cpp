#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Sparse {
    vector<vector<T>> table;
    int n, K;

    T combine(T l, T r) {
        return min(l, r);
    }

    Sparse(const vector<T>& v) {
        n = (int)v.size();
        K = log2(n) + 1;
        table.assign(n, vector<T>(K, 0));
        for (int i = 0; i < n; ++i) table[i][0] = v[i];
        for (int j = 1; j < K; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                table[i][j] = combine(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) {
        const int width = r - l + 1, k = log2(width);
        T ans = combine(table[r - (1 << k) + 1][k], table[l][k]);
        return ans;
    }
};
