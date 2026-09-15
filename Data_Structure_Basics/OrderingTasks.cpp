#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000 + 10;

int n;
bool G[maxn][maxn];
int c[maxn];
int topo[maxn], t;

bool dfs(int u) {
    c[u] = -1; // 访问标志：正在访问
    for (int v = 0; v < n; v++) {
        if (G[u][v]) {
            if (c[v] < 0) return false;          // 存在环
            else if (!c[v] && !dfs(v)) return false;
        }
    }
    c[u] = 1;          // 访问完成
    topo[--t] = u;     // 逆序存入拓扑序列
    return true;
}

bool toposort() {
    t = n;
    memset(c, 0, sizeof(c));

    for (int u = 0; u < n; u++) {
        if (!c[u] && !dfs(u)) return false;
    }
    return true;
}

int main() {
    int m;

    while (scanf("%d%d", &n, &m) == 2) {
        memset(G, 0, sizeof(G));

        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u][v] = true;
        }

        if (toposort()) {
            for (int i = 0; i < n; i++) {
                if (i) printf(" ");
                printf("%d", topo[i]);
            }
            printf("\n");
        } else {
            printf("No solution\n");
        }
    }

    return 0;
}
