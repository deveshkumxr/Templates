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
    int find(int n)
    {
        if (par[n] == n)
            return n;
        return par[n] = find(par[n]);
    }
    void rankUnion(int u, int v)
    {
        int pu = find(u), pv = find(v);
        if (pu == pv)
            return;
        if (rank[pu] > rank[pv])
            par[pv] = pu;
        else if (rank[pu] < rank[pv])
            par[pu] = pv;
        else
            rank[pu]++, par[pv] = pu;
    }
    void sizeUnion(int u, int v)
    {
        int pu = find(u), pv = find(v);
        if (pu == pv)
            return;
        if (size[pu] >= size[pv])
            par[pv] = pu, size[pu] += size[pv];
        else
            size[pv] += size[pu], par[pu] = pv;
    }
    bool sameUnion(int u, int v)
    {
        return find(u) == find(v);
    }
};
