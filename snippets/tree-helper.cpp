#include <bits/stdc++.h>

using namespace std;

// struct based tree helper with 0-based indexing
struct Tree {
    int n, LOG, timer;
    vector<int> tin, tout, depth, flat, par;
    vector<vector<int>> adj, up;

    Tree(int n) {
        this->n = n;
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        par.resize(n);
        flat.resize(2 * n);
        timer = 0;
        adj.resize(n);
        LOG = ceil(log2(n));
        up.assign(n, vector<int>(LOG + 1));
    }

    void add_edge(int a, int b) {
        assert(0 <= a and a < n);
        assert(0 <= b and b < n);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    void build(int root) {
        depth[root] = 0;
        dfs(root, -1);
    }

    void dfs(int v, int p) {
        par[v] = p;
        flat[timer] = v;
        tin[v] = timer++;
        if (p != -1) depth[v] = depth[p] + 1;
        up[v][0] = (p == -1 ? v : p);
        for (int i = 1; i <= LOG; ++i) up[v][i] = up[up[v][i - 1]][i - 1];
        for (auto& u : adj[v])
            if (u != p) dfs(u, v);
        flat[timer] = v;
        tout[v] = timer++;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = LOG; i >= 0; i--)
            if (!is_ancestor(up[u][i], v)) u = up[u][i];
        return up[u][0];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int kth_node(int u, int v, int k) {
        int l = lca(u, v), d = depth[v] + depth[u] - 2 * depth[l];
        assert(0 <= k and k <= d);
        int dul = depth[u] - depth[l];
        if (k <= dul) {
            int ans = u;
            for (int i = 0; i <= LOG; i++)
                if (k & (1 << i)) ans = up[ans][i];
            return ans;
        }
        int dvl = depth[v] - depth[l], dd = dvl - (k - dul), ans = v;
        for (int i = 0; i <= LOG; i++)
            if (dd & (1 << i)) ans = up[ans][i];
        return ans;
    }

    int kth_ancestor(int u, int k, int root = 0) {
        return kth_node(u, root, k);
    }
};

// normal function based

const int N = 100005;
vector<int> g[N];
int depth[N], dp[N][20];

void dfs(int node, int parent, int d) {
    depth[node] = d;
    dp[node][0] = parent;
    for (int k = 1; (1 << k) <= N; k++) {
        if (dp[node][k - 1] != -1) {
            dp[node][k] = dp[dp[node][k - 1]][k - 1];
        } else {
            break;
        }
    }
    for (auto& child : g[node]) {
        if (child != parent) {
            dfs(child, node, d + 1);
        }
    }
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    for (int i = 19; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = dp[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 19; i >= 0; i--) {
        if (dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[u][0];
}

int K(int node, int k) {
    for (int i = 0; k > 0 && node != -1; i++) {
        if (k & 1) {
            node = dp[node][i];
        }
        k >>= 1;
    }
    return node;
}


