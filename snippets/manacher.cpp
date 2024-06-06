#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct manacher
{
    int n;
    vector<int> lp;

    vector<int> initialise(string s)
    {
        n = s.size();
        s = "$" + s + "^";
        vector<int> p(n + 2);

        int l = 1, r = 1;
        for (int i = 1; i <= n; i++)
        {
            p[i] = max(0, min(r - i, p[l + (r - i)]));

            while (s[i - p[i]] == s[i + p[i]])
                p[i]++;

            if (i + p[i] > r)
            {
                l = i - p[i];
                r = i + p[i];
            }
        }

        return vector<int>(p.begin() + 1, p.end() - 1);
    }

    void build(string s)
    {
        string t = "#";
        for (auto &i : s)
        {
            t.push_back(i);
            t.push_back('#');
        }
        lp = initialise(t);
    }

    ll count()
    {
        ll cnt = 0;
        for (int i = 1; i <= n; i++)
            cnt += lp[i] / 2;
        return cnt;
    }

    int longest(int center, bool odd)
    {
        return lp[2 * center + 1 + !odd] - 1;
    }

    bool check(int l, int r)
    {
        return ((r - l + 1) <= longest((l + r) / 2, l % 2 == r % 2));
    }
};