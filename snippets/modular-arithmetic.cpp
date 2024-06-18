#include <bits/stdc++.h>

using namespace std;

const int M = 998244353;
long long fact[1000005], ifact[1000005];

long long gcd(long long a, long long b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
long long lcm(long long a, long long b) { return a * b / gcd(a, b); }
long long exp(long long a, long long b, long long mod = M) {a %= mod; long long res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
long long inv(long long a, long long b = M) {return exp(a, b - 2, b);}
long long nCr(long long n, long long r, long long m = M) {long long val1 = fact[n]; long long val2 = ifact[n - r]; long long val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
long long add(long long a, long long b, long long m = M) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
long long mul(long long a, long long b, long long m = M) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
long long sub(long long a, long long b, long long m = M) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
long long dvd(long long a, long long b, long long m = M) {a = a % m; b = b % m; return (mul(a, inv(b, m), m) + m) % m;}
