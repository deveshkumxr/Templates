#include <bits/stdc++.h>

using namespace std;

// 1--based
template <class T>
class Merge
{
public:
    vector<vector<T>> st;
    int n;

    Merge(int n) : n(n)
    {
        st.resize(4 * n + 4);
    }

    void build(vector<T> &v)
    {
        assert(v.size() == n);
        buildUtil(1, 1, n, v);
    }

    long long query(int l, int r, T q)
    {
        return queryUtil(1, 1, n, l + 1, r + 1, q);
    }

private:
    void buildUtil(int si, int ss, int se, vector<T> &v)
    {
        if (se == ss)
        {
            st[si].push_back(v[ss - 1]);
        }
        else
        {
            int sm = (ss + se) >> 1;
            buildUtil(2 * si, ss, sm, v);
            buildUtil(2 * si + 1, sm + 1, se, v);
            merge(st[2 * si].begin(), st[2 * si].end(), st[2 * si + 1].begin(), st[2 * si + 1].end(), back_inserter(st[si]));
        }
    }

    // change this
    long long queryUtil(int si, int ss, int se, int l, int r, T q)
    {
        if (ss > r || se < l)
        {
            return 0;
        }
        // here
        if (ss >= l && se <= r)
        {
            return lower_bound(st[si].begin(), st[si].end(), q) - st[si].begin();
        }
        int sm = (ss + se) >> 1;
        return queryUtil(2 * si, ss, sm, l, r, q) + queryUtil(2 * si + 1, sm + 1, se, l, r, q);
    }
};