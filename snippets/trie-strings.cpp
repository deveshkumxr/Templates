#include <bits/stdc++.h>
using namespace std;

class Node
{

    Node *links[26];
    bool flag;

public:
    Node()
    {
        for (int i = 0; i < 26; i++)
            links[i] = NULL;
        flag = false;
    }

    bool containsLink(char c)
    {
        return links[c - 'a'] != NULL;
    }

    void newLink(char c)
    {
        links[c - 'a'] = new Node();
    }

    Node *goToLink(char c)
    {
        return links[c - 'a'];
    }

    void setEnd()
    {
        flag = true;
    }

    bool isEnd()
    {
        return flag;
    }
};

class Trie
{

    Node *root;

public:
    /** Initialization */
    Trie()
    {
        root = new Node();
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        Node *t = root;
        for (char c : word)
        {
            if (!(t->containsLink(c)))
                t->newLink(c);
            t = t->goToLink(c);
        }
        t->setEnd();
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        Node *t = root;
        for (char c : word)
        {
            if (!(t->containsLink(c)))
                return false;
            t = t->goToLink(c);
        }
        return t->isEnd();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        Node *t = root;
        for (char c : prefix)
        {
            if (!(t->containsLink(c)))
                return false;
            t = t->goToLink(c);
        }
        return true;
    }
};