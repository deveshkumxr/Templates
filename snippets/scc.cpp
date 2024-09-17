#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int V = 0, tour;
    vector<vector<int>> adj, components;
    vector<int> tour_index, low_link, stack, in_stack, which_component;

    SCC(int v = 0) {
        init(v);
    }

    SCC(const vector<vector<int>>& _adj) {
        init(_adj);
    }

    void init(int v) {
        V = v;
        adj.assign(V, {});
    }

    void init(const vector<vector<int>>& _adj) {
        adj = _adj;
        V = (int)adj.size();
    }

    void add_edge(int a, int b) {
        adj[a].push_back(b);
    }

    void dfs(int node) {
        tour_index[node] = tour++;
        low_link[node] = tour_index[node];
        stack.push_back(node);
        in_stack[node] = true;
        for (int to : adj[node])
            if (tour_index[to] < 0) {
                dfs(to);
                low_link[node] = min(low_link[node], low_link[to]);
            } else if (in_stack[to]) 
                low_link[node] = min(low_link[node], tour_index[to]);
            if (low_link[node] == tour_index[node]) {
                components.emplace_back();
                vector<int>& component = components.back();
                int x;
                do {
                    assert(!stack.empty());
                    x = stack.back();
                    stack.pop_back();
                    in_stack[x] = false;
                    which_component[x] = (int)components.size() - 1;
                    component.push_back(x);
                } while (x != node);
            }
    }

    void build() {
        tour_index.assign(V, -1);
        low_link.resize(V);
        which_component.assign(V, -1);
        stack.clear();
        stack.reserve(V);
        in_stack.assign(V, 0);
        tour = 0;
        components = {};
        for (int i = 0; i < V; i++)
            if (tour_index[i] < 0) dfs(i);
    }
};