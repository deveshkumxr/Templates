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

ll tree[4 * mxN + 4];

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
    if (ss > r || se < l)
        return INT_MAX;
    if (ss >= l && se <= r)
        return tree[si];
    int sm = (ss + se) >> 1;
    return min(find(2 * si, ss, sm, l, r), find(2 * si + 1, sm + 1, se, l, r));
}

void update(int si, int ss, int se, int ind, int val)
{
    if (ss == se)
        tree[si] = val;
    else
    {
        int sm = (ss + se) >> 1;
        if (ind <= sm)
            update(2 * si, ss, sm, ind, val);
        else
            update(2 * si + 1, sm + 1, se, ind, val);
        tree[si] = min(tree[2 * si], tree[2 * si + 1]);
    }
}

int main()
{
    vector<int> v{2, -1, 3, -4, 5, 6};
    build(1, 1, 6, v);
    update(1, 1, 6, 4, 0);
    cout << find(1, 1, 6, 2, 5) << endl;
    update(1, 1, 6, 6, -10);
    cout << find(1, 1, 6, 2, 6) << endl;
    cout << find(1, 1, 6, 1, 3) << endl;
}