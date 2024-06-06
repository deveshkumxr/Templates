#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:

    vector<int> size, par;

    DSU(int n)
    {
        par.resize(n + 1);
        size.resize(n + 1, 1);
        iota(par.begin(), par.end(), 0);
    }

    int find(int i)
    {
        if (par[i] == i)
            return i;
        return par[i] = find(par[i]);
    }

    int set_size(int i)
    {
        return size[find(i)];
    }

    void unite(int u, int v)
    {
        if (same(u, v))
            return;
        if (set_size(u) < set_size(v))
            swap(u, v);
        u = find(u), v = find(v);
        par[v] = u, size[u] += size[v];
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }
};
