/*
 * Given the middle and latter parsing of a tree.
 * Print the minimal leave that has a minimal path value to the root.
 * Input:
 * 3 2 1 4 5 7 6
 * 3 1 2 5 6 7 4
 * Output:
 * 1
 */
/*
 * Analysis:
 * the root is easy to find in postOrder Parsing. 
 * so we find the root in inOrderParsing and recursively construct the left and right tree.
 */
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// Since the value of each node differs and is all integer, using it as id.
const int maxv = 10000 + 10;
int in_order[maxv], post_order[maxv], lch[maxv], rch[maxv];
int n;

bool read_list(int* a) {
    string line;
    if(!getline(cin, line)) return false;
    stringstream ss(line);
    n = 0;
    int x;
    while(ss >> x) a[n++] = x;
    return n > 0;
}

// construct in_order[L1..R1] and post_order[L2..R2] as a binary tree and return its root
int build(int L1, int R1, int L2, int R2) {
    if(L1 > R1) return 0; // empty tree
    int root = post_order[R2];
    int p = L1;
    while(in_order[p] != root) p++;
    int cnt = p - L1; // the node count of the left subtree
    lch[root] = build(L1, p - 1, L2, L2 + cnt - 1); // take out the left subtree part
    rch[root] = build(p + 1, R1, L2 + cnt, R2 - 1);
    return root;
}

int best, best_sum; // define the best solution up-to-now

void dfs(int u, int sum) {
    sum += u;
    if(!lch[u] && !rch[u]) { // a leaf
        if(sum < best_sum || (sum == best_sum && u < best)) {best = u; best_sum = sum;}
    }
    if(lch[u]) dfs(lch[u], sum);
    if(rch[u]) dfs(rch[u], sum);
}

int main() {
    while(read_list(in_order)) {
        read_list(post_order);
        build(0, n - 1, 0, n - 1);
        best_sum = 1000000000;
        dfs(post_order[n - 1], 0);
        cout << best << '\n';
    }
    return 0;
}
