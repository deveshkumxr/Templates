#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

long long gcd(long long a, long long b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
long long lcm(long long a, long long b) { return a * b / gcd(a, b); }
long long exp(long long a, long long b, long long mod) {a %= mod; long long res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
long long inv(long long a, long long b) {return exp(a, b - 2, b);}
long long add(long long a, long long b, long long m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
long long mul(long long a, long long b, long long m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
long long sub(long long a, long long b, long long m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
long long dvd(long long a, long long b, long long m) {a = a % m; b = b % m; return (mul(a, inv(b, m), m) + m) % m;}

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
const long long base = gen() % N + 32;

// string hashing
struct Hashing {
    string s;
    int n;
    int primes;
    vector<long long> hash_primes = {1000000009, 100000007};
    vector<vector<long long>> hash_values, power_of_base, inverse_power_of_base;

    Hashing(string a) {
        primes = hash_primes.size();
        hash_values.resize(primes);
        power_of_base.resize(primes);
        inverse_power_of_base.resize(primes);
        s = a;
        n = s.length();
        for (int i = 0; i < (int)hash_primes.size(); i++) {
            power_of_base[i].resize(n + 1);
            inverse_power_of_base[i].resize(n + 1);
            power_of_base[i][0] = 1;
            for (int j = 1; j <= n; j++) power_of_base[i][j] = (base * power_of_base[i][j - 1]) % hash_primes[i];
            inverse_power_of_base[i][n] = inv(power_of_base[i][n], hash_primes[i]);
            for (int j = n - 1; j >= 0; j--) inverse_power_of_base[i][j] = mul(inverse_power_of_base[i][j + 1], base, hash_primes[i]);
        }
        for (int i = 0; i < (int)hash_primes.size(); i++) {
            hash_values[i].resize(n);
            for (int j = 0; j < n; j++) {
                hash_values[i][j] = ((s[j] - 'a' + 1LL) * power_of_base[i][j]) % hash_primes[i];
                hash_values[i][j] = (hash_values[i][j] + (j > 0 ? hash_values[i][j - 1] : 0LL)) % hash_primes[i];
            }
        }
    }

    vector<long long> substring_hash(int l, int r) {
        vector<long long> hash(primes);
        for (int i = 0; i < primes; i++) {
            long long val1 = hash_values[i][r];
            long long val2 = l > 0 ? hash_values[i][l - 1] : 0LL;
            hash[i] = mul(sub(val1, val2, hash_primes[i]), inverse_power_of_base[i][l], hash_primes[i]);
        }
        return hash;
    }
};

// unordered_map custom hash
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};