#include <bits/stdc++.h>
using namespace std;

const int N = 1'000'000 + 5;

int spf[N], is_prime[N];
vector<int> primes;

void sieve() {
    for (int i = 2; i < N; i++) {
        if (not spf[i]) {
            is_prime[i] = 1;
            spf[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; i * primes[j] < N; j++) {
            spf[i * primes[j]] = primes[j];
            if (primes[j] == spf[i]) break;
        }
    }
}