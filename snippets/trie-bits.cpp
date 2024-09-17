#include <bits/stdc++.h>
using namespace std;

class Node {
    Node* links[2];

public:
    int frq[2];

    Node() {
        links[0] = links[1] = nullptr;
        frq[0] = frq[1] = 0;
    }

    bool containsLink(int b) { return links[b]; }

    void createLink(int b) { links[b] = new Node(); }

    Node* goToLink(int b) { return links[b]; }
};

class Trie {
    Node* root;

public:
    Trie() { root = new Node(); }

    void insert(int x) {
        Node* t = root;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!t->containsLink(b)) t->createLink(b);
            t->frq[b]++;
            t = t->goToLink(b);
        }
    }

    void remove(int x) {
        Node* t = root;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            t->frq[b]--;
            t = t->goToLink(b);
        }
    }

    int getMaximumXOR(int y) {
        Node* t = root;
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            int by = (y >> i) & 1, w = 1 - by;
            if (t->frq[w]) {
                res = res | (1 << i);
                t = t->goToLink(w);
            } else {
                t = t->goToLink(by);
            }
        }
        return res;
    }
};

struct Trie {
    vector<array<int, 2>> trie = { {} };

    void insert(int v) {
        int at = 0;
        for (int i = 29; i >= 0; --i) {
            int to = v >> i & 1;
            if (!trie[at][to]) {
                trie[at][to] = trie.size();
                trie.push_back({});
            }
            at = trie[at][to];
        }
    }

    int query(int v) {
        int at = 0;
        int ans = 0;
        for (int i = 29; i >= 0; --i) {
            int to = v >> i & 1;
            if (!trie[at][to]) {
                to = !to;
                ans += 1 << i;
            }
            at = trie[at][to];
        }
        return ans;
    }
};