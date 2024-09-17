#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 4;

long long st[4 * N + 4];

long long combine(long long x, long long y) { return min(x, y); }

// build st -- 1-based indexing
void build(int si, int ss, int se, vector<int> &arr)
{
    if (ss == se)
        st[si] = arr[ss - 1];
    else
    {
        int sm = (ss + se) >> 1;
        build(2 * si, ss, sm, arr);
        build(2 * si + 1, sm + 1, se, arr);
        st[si] = combine(st[2 * si], st[2 * si + 1]);
    }
}

// value for [l, r]
long long query(int si, int ss, int se, int l, int r)
{
    if (ss > r || se < l)
        return INT_MAX;
    if (ss >= l && se <= r)
        return st[si];
    int sm = (ss + se) >> 1;
    return combine(query(2 * si, ss, sm, l, r), query(2 * si + 1, sm + 1, se, l, r));
}

// walk on st -- direct query
long long walk(int si, int ss, int se, int l, int r, long long x)
{
    if (ss > r || se < l || st[si] > x)
        return INT_MAX;
    if (ss >= l && se <= r)
    {
        if (ss == se)
            return ss;
        int sm = (ss + se) >> 1;
        if (st[2 * si] <= x)
            return walk(2 * si, ss, sm, l, r, x);
        return walk(2 * si + 1, sm + 1, se, l, r, x);
    }
    int sm = (ss + se) >> 1;
    return min(walk(2 * si, ss, sm, l, r, x), walk(2 * si + 1, sm + 1, se, l, r, x));
}

// point update for ind
void update(int si, int ss, int se, int ind, long long val)
{
    if (ss == se)
        st[si] = val;
    else
    {
        int sm = (ss + se) >> 1;
        if (ind <= sm)
            update(2 * si, ss, sm, ind, val);
        else
            update(2 * si + 1, sm + 1, se, ind, val);
        st[si] = combine(st[2 * si], st[2 * si + 1]);
    }
}