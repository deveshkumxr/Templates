#include <bits/stdc++.h>

using ll = long long;
using namespace std;

const int M = 998244353;
ll fact[1000005], ifact[1000005];

ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll exp(ll a, ll b, ll mod = M) {a %= mod; ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll inv(ll a, ll b = M) {return exp(a, b - 2, b);}
ll nCr(ll n, ll r, ll m = M) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
ll add(ll a, ll b, ll m = M) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mul(ll a, ll b, ll m = M) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll sub(ll a, ll b, ll m = M) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll dvd(ll a, ll b, ll m = M) {a = a % m; b = b % m; return (mul(a, inv(b, m), m) + m) % m;}
