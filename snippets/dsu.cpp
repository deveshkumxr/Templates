#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:
    vector<int> rank, size, par;

    DSU(int n)
    {
        rank.resize(n + 1, 0);
        par.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i < n + 1; i++)
            par[i] = i;
    }

    int get_par(int i)
    {
        if (par[i] == i)
            return i;
        return par[i] = get_par(par[i]);
    }

    int get_size(int i)
    {
        return size[get_par(i)];
    }

    void rank_union(int u, int v)
    {
        int pu = get_par(u), pv = get_par(v);
        if (pu == pv)
            return;
        if (rank[pu] > rank[pv])
            par[pv] = pu;
        else if (rank[pu] < rank[pv])
            par[pu] = pv;
        else
            rank[pu]++, par[pv] = pu;
    }

    void size_union(int u, int v)
    {
        int pu = get_par(u), pv = get_par(v);
        if (pu == pv)
            return;
        if (size[pu] >= size[pv])
            par[pv] = pu, size[pu] += size[pv];
        else
            size[pv] += size[pu], par[pu] = pv;
    }

    bool same_union(int u, int v)
    {
        return get_par(u) == get_par(v);
    }
};
