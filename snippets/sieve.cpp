#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

// is prime
int is_prime[N];
void Sieve()
{
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; i < N; i++) is_prime[i] = 1;
    for (int p = 2; p < N; p++)
    {
        if (is_prime[p])
        {
            for (int i = 2 * p; i < N; i += p)
                is_prime[i] = 0;
        }
    }
}

// smallest prime factor
int spf[N];
void Sieve()
{
    for (int p = 2; p < N; p++)
    {
        if (spf[p] == 0)
        {
            for (int i = p; i < N; i += p)
                spf[i] = p;
        }
    }
}