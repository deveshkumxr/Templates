#include <bits/stdc++.h>
using namespace std;

vector<int> next_greater(vector<int>& a) {
    int n = a.size();
    vector<int> ans(n, n);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && a[i] >= a[s.top()]) s.pop();
        if (!s.empty()) ans[i] = s.top();
        s.push(i);
    }
    return ans;
}

vector<int> previous_greater(vector<int>& a) {
    int n = a.size();
    vector<int> ans(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[i] >= a[s.top()]) s.pop();
        if (!s.empty()) ans[i] = s.top();
        s.push(i);
    }
    return ans;
}

vector<int> next_smaller(vector<int>& a) {
    int n = a.size();
    vector<int> ans(n, n);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && a[i] <= a[s.top()]) s.pop();
        if (!s.empty()) ans[i] = s.top();
        s.push(i);
    }
    return ans;
}

vector<int> previous_smaller(vector<int>& a) {
    int n = a.size();
    vector<int> ans(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() and a[i] <= a[s.top()]) s.pop();
        if (!s.empty()) ans[i] = s.top();
        s.push(i);
    }
    return ans;
}