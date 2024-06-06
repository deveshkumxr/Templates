#include <bits/stdc++.h>

using namespace std;

// class based tree helper with 0-based indexing
class Tree
{
public:
    int n, LOG;
    vector<vector<int>> adj;

    int timer;
    vector<int> tin, tout, depth, flat, par;
    vector<vector<int>> up;

    Tree(int n)
    {
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

    void add_edge(int a, int b)
    {
        assert(0 <= a and a < n);
        assert(0 <= b and b < n);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    void build(int root)
    {
        depth[root] = 0;
        dfs(root, -1);
    }

    void dfs(int v, int p)
    {
        par[v] = p;
        flat[timer] = v;
        tin[v] = timer++;
        if (p != -1)
            depth[v] = depth[p] + 1;
        up[v][0] = (p == -1 ? v : p);
        for (int i = 1; i <= LOG; ++i)
            up[v][i] = up[up[v][i - 1]][i - 1];

        for (int u : adj[v])
        {
            if (u != p)
                dfs(u, v);
        }
        flat[timer] = v;
        tout[v] = timer++;
    }

    bool is_ancestor(int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int get_lca(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = LOG; i >= 0; --i)
        {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    int get_dist(int u, int v)
    {
        int l = get_lca(u, v);
        return depth[u] - depth[l] + depth[v] - depth[l];
    }

    int get_kth_node_in_path(int u, int v, int k)
    {
        int l = get_lca(u, v);
        int d = depth[v] - depth[l] + depth[u] - depth[l];

        assert(0 <= k and k <= d);

        int dist_from_u_to_l = depth[u] - depth[l];
        if (k <= dist_from_u_to_l)
        {
            int ans = u;
            for (int i = 0; i <= LOG; i++)
            {
                if (k & (1 << i))
                {
                    ans = up[ans][i];
                }
            }
            return ans;
        }
        else
        {
            int dist_from_v_to_l = depth[v] - depth[l];
            int find_d = dist_from_v_to_l - (k - dist_from_u_to_l);
            int ans = v;
            for (int i = 0; i <= LOG; i++)
            {
                if (find_d & (1 << i))
                {
                    ans = up[ans][i];
                }
            }
            return ans;
        }
    }

    int get_kth_ancestor(int u, int k, int root = 0)
    {
        return get_kth_node_in_path(u, root, k);
    }
};


// normal function based

const int N = 100005;
vector<int> g[N];
int depth[N], dp[N][20];

void dfs(int node, int parent, int d)
{
    depth[node] = d;
    dp[node][0] = parent;
    for (int k = 1; (1 << k) <= N; k++)
    {
        if (dp[node][k - 1] != -1)
        {
            dp[node][k] = dp[dp[node][k - 1]][k - 1];
        }
        else
        {
            break;
        }
    }
    for (auto &child : g[node])
    {
        if (child != parent)
        {
            dfs(child, node, d + 1);
        }
    }
}

int LCA(int u, int v)
{
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }
    for (int i = 19; i >= 0; i--)
    {
        if (depth[u] - (1 << i) >= depth[v])
        {
            u = dp[u][i];
        }
    }
    if (u == v)
    {
        return u;
    }
    for (int i = 19; i >= 0; i--)
    {
        if (dp[u][i] != dp[v][i])
        {
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[u][0];
}

int K(int node, int k)
{
    for (int i = 0; k > 0 && node != -1; i++)
    {
        if (k & 1)
        {
            node = dp[node][i];
        }
        k >>= 1;
    }
    return node;
}
