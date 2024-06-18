#include <bits/stdc++.h>

using namespace std;

void remove(int i) {}

void add(int i) {}

long long get_answer() {}

const int block_size;

struct Query
{
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

vector<long long> mo_s_algorithm(vector<Query> queries)
{
    vector<long long> answers(queries.size());
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries)
    {
        while (cur_l > q.l)
        {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r)
        {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l)
        {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r)
        {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}