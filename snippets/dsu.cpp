#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> siz, par;
    int comps;

    DSU(int n) {
        par.resize(n + 1);
        siz.assign(n + 1, 1);
        iota(par.begin(), par.end(), 0);
        comps = n;
    }

    int find(int i) {
        if (par[i] == i) return i;
        return par[i] = find(par[i]);
    }

    void join(int u, int v) {
        if (same(u, v)) return;
        if (size(u) < size(v)) swap(u, v);
        u = find(u), v = find(v), comps--;
        par[v] = u, siz[u] += siz[v];
    }

    int size(int i) {
        return siz[find(i)];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};
