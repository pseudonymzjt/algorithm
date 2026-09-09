/*
 * Input a tree (preOrder: empty subtree uses -1) and
 * output the value sum of nodes on the same vertical line from left to right.
 */
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 1000 + 10;
int sum[maxn];

// input and analyze a subtree, the horizontal position of the root is at p
void build(int p) {
    int v; cin >> v;
    if(v == -1) return;
    sum[p] += v;
    build(p - 1); build(p + 1);
}

// read and analyze
bool init() {
    int v; cin >> v;
    if(v == -1) return false;
    memset(sum, 0, sizeof(sum));
    int pos = maxn / 2;
    sum[pos] = v;
    build(pos - 1);
    build(pos + 1);
    return true;
}

int main() {
    int kase = 0;
    while(init()) {
        int p = 0;
        while(sum[p] == 0) p++;
        cout << "Case " << ++kase << ":\n" << sum[p++];
        while(sum[p] != 0) cout << " " << sum[p++];
        cout << "\n\n";
    }
    return 0;
}
