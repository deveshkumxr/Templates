#include <bits/stdc++.h>

using namespace std;

template <class T, class U>
// T -> node, U->update
class Seg
{
public:
    vector<T> st;
    vector<U> lazy;
    long long n;
    T identity_element; // I such that combine(x,I) = x
    U identity_update;  // I such that apply(x,I) = x

    Seg(long long n, T identity_element, U identity_update)
    {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(4 * n, identity_element);
        lazy.assign(4 * n, identity_update);
    }

    T combine(T l, T r)
    {
        // combines left and right child
        T ans = (l + r);
        return ans;
    }

    void buildUtil(long long v, long long tl, long long tr, vector<T> &a)
    {
        if (tl == tr)
        {
            st[v] = a[tl];
            return;
        }
        long long tm = (tl + tr) >> 1;
        buildUtil(2 * v + 1, tl, tm, a);
        buildUtil(2 * v + 2, tm + 1, tr, a);
        st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
    }

    // change the folong longowing 2 functions

    T apply(T curr, U upd, long long tl, long long tr)
    {
        // current state and new update in [tl, tr]
        T ans = upd;
        return ans;
    }

    U combineUpdate(U old_upd, U new_upd, long long tl, long long tr)
    {
        // combining old and new updates
        U ans = old_upd;
        ans = new_upd;
        return ans;
    }

    void push_down(long long v, long long tl, long long tr)
    {
        if (lazy[v] == identity_update)
            return;
        st[v] = apply(st[v], lazy[v], tl, tr);
        if (2 * v + 2 < 4 * n)
        {
            long long tm = (tl + tr) >> 1;
            lazy[2 * v + 1] = combineUpdate(lazy[2 * v + 1], lazy[v], tl, tm);
            lazy[2 * v + 2] = combineUpdate(lazy[2 * v + 2], lazy[v], tm + 1, tr);
        }
        lazy[v] = identity_update;
    }

    T queryUtil(long long v, long long tl, long long tr, long long l, long long r)
    {
        push_down(v, tl, tr);
        if (l > r)
            return identity_element;
        if (tr < l or tl > r)
        {
            return identity_element;
        }
        if (l <= tl and r >= tr)
        {
            return st[v];
        }
        long long tm = (tl + tr) >> 1;
        return combine(queryUtil(2 * v + 1, tl, tm, l, r), queryUtil(2 * v + 2, tm + 1, tr, l, r));
    }

    void updateUtil(long long v, long long tl, long long tr, long long l, long long r, U upd)
    {
        push_down(v, tl, tr);
        if (tr < l or tl > r)
            return;
        if (tl >= l and tr <= r)
        {
            lazy[v] = combineUpdate(lazy[v], upd, tl, tr);
            push_down(v, tl, tr);
        }
        else
        {
            long long tm = (tl + tr) >> 1;
            updateUtil(2 * v + 1, tl, tm, l, r, upd);
            updateUtil(2 * v + 2, tm + 1, tr, l, r, upd);
            st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
        }
    }

    void build(vector<T> a)
    {
        assert(a.size() == n);
        buildUtil(0, 0, n - 1, a);
    }

    T query(long long l, long long r)
    {
        return queryUtil(0, 0, n - 1, l, r);
    }

    void update(long long l, long long r, U upd)
    {
        updateUtil(0, 0, n - 1, l, r, upd);
    }
};