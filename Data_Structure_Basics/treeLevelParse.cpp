/*
 * enter a tree like this:
 * (3,L) (4,R) ()
 * print the tree from up to down and from left to right
 */
#include <cstddef>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct Node {  
    bool have_value;
    int v; // node value
    Node *left, *right;
    Node():have_value(false), left(NULL), right(NULL) {} // constructor
};

Node* root;
bool failed;

Node* newnode() {return new Node();}

void addnode(int v, char* s) {
    int n = strlen(s);
    Node* u = root;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'L') {
            if(u->left == NULL) u->left = newnode();
            u = u->left;
        } else if(s[i] == 'R') {
            if(u->right == NULL) u->right = newnode();
            u = u->right;
        } // ignore other situations including redundant ')'
        if(u->have_value) failed = true;
        u->v = v;
        u->have_value = true;
    }
}

/* parse the tree */
bool bfs(vector<int>& ans) {
    queue<Node*> q;
    ans.clear();
    q.push(root);
    while(!q.empty()) {
        Node* u = q.front(); q.pop();
        if(!u->have_value) return false;
        ans.push_back(u->v);
        if(u->left != NULL) q.push(u->left);
        if(u->right != NULL) q.push(u->right);
    }
    return true;
}

/* release a tree */
void remove_tree(Node* u) {
    if(u == NULL) return;
    remove_tree(u->left);
    remove_tree(u->right);
    delete u;
}
