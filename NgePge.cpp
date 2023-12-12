#include <bits/stdc++.h>
using namespace std;


void nge(vector<int> &a, vector<int> &ng)
{
    int n = a.size();
    stack<int> s;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!s.empty() && a[i] >= a[s.top()])
            s.pop();
        if (!s.empty())
            ng[i] = s.top();
        s.push(i);
    }
}

void pge(vector<int> &a, vector<int> &pg)
{
    int n = a.size();
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && a[i] > a[s.top()])
            s.pop();
        if (!s.empty())
            pg[i] = s.top();
        s.push(i);
    }
}