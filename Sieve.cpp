#include <bits/stdc++.h>
using namespace std;

bool prime[100001];
void Sieve()
{
    memset(prime, true, sizeof(prime));
    prime[1] = prime[0] = false;
    for (int p = 2; p * p <= 100000; p++)
    {
        if (prime[p] == true)
        {
            for (int i = p * p; i <= 100000; i += p)
                prime[i] = false;
        }
    }
}