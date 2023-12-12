#include <iostream>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

const int mxN = 2e5 + 4;
ll INF = 1e15, mod = 1e9 + 7;

ll tree[4 * mxN + 4], lazy[4 * mxN + 4];

// Range Min Queries
void build(int si, int ss, int se, vector<int> &arr)
{
    if (ss == se)
        tree[si] = arr[ss - 1];
    else
    {
        int sm = (ss + se) >> 1;
        build(2 * si, ss, sm, arr);
        build(2 * si + 1, sm + 1, se, arr);
        tree[si] = min(tree[2 * si], tree[2 * si + 1]);
    }
}

ll find(int si, int ss, int se, int l, int r)
{
    if(lazy[si]){
        ll del=lazy[si], range=se-ss+1;
        lazy[si]=0;
        tree[si]+=(del*range);
        if(se!=ss) lazy[2*si]+=del, lazy[2*si+1]+=del;
    }
    if (ss > r || se < l)
        return INT_MAX;
    if (ss >= l && se <= r)
        return tree[si];
    int sm = (ss + se) >> 1;
    return min(find(2 * si, ss, sm, l, r), find(2 * si + 1, sm + 1, se, l, r));
}

void update(int si, int ss, int se, int l, int r, int val)
{
    if(lazy[si]){
        ll del=lazy[si], range=se-ss+1;
        lazy[si]=0;
        tree[si]+=(del*range);
        if(se!=ss) lazy[2*si]+=del, lazy[2*si+1]+=del;
    }
    if (ss > r || se < l)
        return;
    if (ss >= l && se <= r){
        ll del=val, range=se-ss+1;
        tree[si]+=(del*range);
        if(se!=ss) lazy[2*si]+=del, lazy[2*si+1]+=del;
        return;
    }
    int sm = (ss + se) >> 1;
    update(2*si, ss, sm, l, r, val);
    update(2*si+1, sm+1, se, l, r, val);
    tree[si] = min(tree[2*si], tree[2*si+1]);
}