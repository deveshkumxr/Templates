#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;

vector<int> tree[MAXN];
int depth[MAXN];
int dp[MAXN][20];

void dfs(int node, int parent, int d)
{
    depth[node] = d;
    dp[node][0] = parent;
    for (int k = 1; (1 << k) <= MAXN; k++)
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
    for (int child : tree[node])
    {
        if (child != parent)
        {
            dfs(child, node, d + 1);
        }
    }
}

int findLCA(int u, int v)
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

int findKthAncestor(int node, int k)
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