#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mod = 1e9 + 7, fact[100005];

long long modpow(long long a, long long b, long long p)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}

ll inv(ll a)
{
    return modpow(a, mod - 2, mod);
}

void build(int n)
{
    fact[0] = 1;
    for (ll i = 1; i <= n; i++)
        fact[i] = (fact[i - 1] * i) % mod;
}

ll nCr(int n, int r)
{
    ll num = fact[n], den = (inv(fact[r]) * inv(fact[n - r])) % mod;
    return (num * den) % mod;
}
