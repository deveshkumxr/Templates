#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 5e5 + 4;

vector<ll> st[4 * N + 4];

// build st -- 1-based idx
void build(int si, int ss, int se, vector<ll> &v)
{
    if (se == ss)
        st[si].push_back(v[ss - 1]);
    else
    {
        int sm = (ss + se) >> 1;
        build(2 * si, ss, sm, v);
        build(2 * si + 1, sm + 1, se, v);
        int i = 0, j = 0;
        while (i < st[2 * si].size() && j < st[2 * si + 1].size())
        {
            if (st[2 * si][i] < st[2 * si + 1][j])
                st[si].push_back(st[2 * si][i++]);
            else
                st[si].push_back(st[2 * si + 1][j++]);
        }
        while (i < st[2 * si].size())
        {
            st[si].push_back(st[2 * si][i++]);
        }
        while (j < st[2 * si + 1].size())
        {
            st[si].push_back(st[2 * si + 1][j++]);
        }
    }
}

// count of elements < cur
ll find(int si, int ss, int se, int l, int r, ll cur)
{
    if (ss > r || se < l)
        return 0;
    if (ss >= l && se <= r)
    {
        int cnt = lower_bound(begin(st[si]), end(st[si]), cur) - begin(st[si]);
        return cnt;
    }
    int sm = (ss + se) >> 1;
    return find(2 * si, ss, sm, l, r, cur) + find(2 * si + 1, sm + 1, se, l, r, cur);
}