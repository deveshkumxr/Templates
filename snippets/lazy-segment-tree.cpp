#include <bits/stdc++.h>

using namespace std;

template <class T, class U>
struct SegmentTree {
    vector<T> st;
    vector<U> lazy;
    long long n;
    T identity_element;
    U identity_update;

    SegmentTree(long long n, T identity_element, U identity_update) {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(4 * n, identity_element);
        lazy.assign(4 * n, identity_update);
    }

    T combine(T l, T r) {
        T ans = (l + r);
        return ans;
    }

    void build_util(long long v, long long tl, long long tr, vector<T>& a) {
        if (tl == tr) {
            st[v] = a[tl];
            return;
        }
        long long tm = (tl + tr) >> 1;
        build_util(2 * v + 1, tl, tm, a);
        build_util(2 * v + 2, tm + 1, tr, a);
        st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
    }

    T apply(T curr, U upd, long long tl, long long tr) {
        T ans = upd;
        return ans;
    }

    U combine_update(U old_upd, U new_upd, long long tl, long long tr) {
        U ans = old_upd;
        ans = new_upd;
        return ans;
    }

    void push_down(long long v, long long tl, long long tr) {
        if (lazy[v] == identity_update) return;
        st[v] = apply(st[v], lazy[v], tl, tr);
        if (2 * v + 2 < 4 * n) {
            long long tm = (tl + tr) >> 1;
            lazy[2 * v + 1] = combine_update(lazy[2 * v + 1], lazy[v], tl, tm);
            lazy[2 * v + 2] = combine_update(lazy[2 * v + 2], lazy[v], tm + 1, tr);
        }
        lazy[v] = identity_update;
    }

    T query_util(long long v, long long tl, long long tr, long long l, long long r) {
        push_down(v, tl, tr);
        if (l > r or tr < l or tl > r) return identity_element;
        if (l <= tl and r >= tr) return st[v];
        long long tm = (tl + tr) >> 1;
        return combine(query_util(2 * v + 1, tl, tm, l, r), query_util(2 * v + 2, tm + 1, tr, l, r));
    }

    void update_util(long long v, long long tl, long long tr, long long l, long long r, U upd) {
        push_down(v, tl, tr);
        if (tr < l or tl > r) return;
        if (tl >= l and tr <= r) {
            lazy[v] = combine_update(lazy[v], upd, tl, tr);
            push_down(v, tl, tr);
        } else {
            long long tm = (tl + tr) >> 1;
            update_util(2 * v + 1, tl, tm, l, r, upd);
            update_util(2 * v + 2, tm + 1, tr, l, r, upd);
            st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
        }
    }

    void build(vector<T> a) {
        assert(a.size() == n);
        build_util(0, 0, n - 1, a);
    }

    T query(long long l, long long r) {
        return query_util(0, 0, n - 1, l, r);
    }

    void update(long long l, long long r, U upd) {
        update_util(0, 0, n - 1, l, r, upd);
    }
};