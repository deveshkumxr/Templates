#include <bits/stdc++.h>
using namespace std;

const int M = 998244353;

template <unsigned int mod = M>
struct mint {
    unsigned int x;

    mint() : x(0) {}

    mint(long long _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }

    mint& operator+=(const mint& a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    mint& operator-=(const mint& a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }


    mint& operator*=(const mint& a) {
        x = (long long)x * a.x % mod;
        return *this;
    }

    mint pow(long long pw) const {
        mint res = 1;
        mint cur = *this;
        while (pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }

    mint inv() const {
        assert(x != 0);
        unsigned int t = x;
        unsigned int res = 1;
        while (t != 1) {
            unsigned int z = mod / t;
            res = (long long)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }

    mint& operator/=(const mint& a) {
        return *this *= a.inv();
    }

    mint operator+(const mint& a) const {
        return mint(*this) += a;
    }

    mint operator-(const mint& a) const {
        return mint(*this) -= a;
    }

    mint operator*(const mint& a) const {
        return mint(*this) *= a;
    }

    mint operator/(const mint& a) const {
        return mint(*this) /= a;
    }

    bool operator==(const mint& a) const {
        return x == a.x;
    }

    bool operator!=(const mint& a) const {
        return x != a.x;
    }

    bool operator<(const mint& a) const {
        return x < a.x;
    }

    friend ostream& operator<<(std::ostream& os, mint const& a) {
        return os << a.x;
    }

    friend istream& operator>>(istream& is, mint& a) {
        long long _x;
        is >> _x;
        a = mint(_x);
        return is;
    }
};

template <unsigned int mod = M>
struct Factorials {
    using Mint = mint<mod>;
    vector<Mint> f, fi;

    Factorials() : f(), fi() {}

    Factorials(int n) {
        n += 8;
        f = vector<Mint>(n);
        fi = vector<Mint>(n);
        f[0] = 1;
        for (int i = 1; i < n; i++) f[i] = f[i - 1] * i;
        fi[n - 1] = f[n - 1].inv();
        for (int i = n - 1; i > 0; i--) fi[i - 1] = fi[i] * i;
    }

    Mint C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return f[n] * fi[k] * fi[n - k];
    }

    Mint P(int n, int k) {
        if (k < 0 || k > n) return 0;
        return f[n] * fi[n - k];
    }
};

template <unsigned int mod = M>
struct Powers {
    using Mint = mint<mod>;
    vector<Mint> p, pi;

    Powers() : p(), pi() {}

    Powers(int n, Mint x) {
        n += 8;
        if (x == 0) {
            p = vector<Mint>(n);
            p[0] = 1;
        } else {
            p = vector<Mint>(n);
            pi = vector<Mint>(n);
            p[0] = pi[0] = 1;
            Mint xi = x.inv();
            for (int i = 1; i < n; i++) {
                p[i] = p[i - 1] * x;
                pi[i] = pi[i - 1] * xi;
            }
        }
    }

    Mint pow(int n) {
        if (n >= 0)
            return p[n];
        else
            return pi[-n];
    }
};

template <unsigned int mod = M>
struct Inverses {
    using Mint = mint<mod>;
    vector<Mint> ii;

    Inverses() : ii() {}

    Inverses(int n) {
        n += 8;
        ii = vector<Mint>(n);
        ii[1] = 1;
        for (int x = 2; x < n; x++) ii[x] = Mint() - ii[mod % x] * (mod / x);
    }

    Mint inv(Mint x) {
        assert(x != 0);
        unsigned int t = x.x;
        unsigned int res = 1;
        while (t >= (int)ii.size()) {
            unsigned int z = mod / t;
            res = (long long)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return ii[t] * res;
    }
};

using Z = mint<>;