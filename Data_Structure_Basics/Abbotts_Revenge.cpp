#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;

// 方向：北、东、南、西
const char* dirs = "NESW";
// 转向：直行、左转、右转
const char* turns = "FLR";

int dir_id(char c)  { return strchr(dirs, c) - dirs; }
int turn_id(char c) { return strchr(turns, c) - turns; }

// 行走：与 dirs 对应
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

const int MAXN = 100;

struct Node {
    int dir;
    int c, r;
    Node(int dir = 0, int c = 0, int r = 0) : dir(dir), c(c), r(r) {}
};

// 全局状态
int d[MAXN][MAXN][4];
Node p[MAXN][MAXN][4];
bool has_edge[MAXN][MAXN][4][4];

int r0, c0, r2, c2;
int r1, c1;
int dir;
char name[100];

bool inside(int r, int c) {
    return r >= 1 && r < MAXN && c >= 1 && c < MAXN;
}

// 从结点 u 按 turn 转向后走一步
Node walk(const Node& u, int turn) {
    int dir = u.dir;
    if (turn == 1) dir = (dir + 3) % 4; // 左转
    if (turn == 2) dir = (dir + 1) % 4; // 右转
    return Node(dir, u.c + dc[dir], u.r + dr[dir]);
}

void print_ans(Node u);

void solve() {
    queue<Node> q;
    memset(d, -1, sizeof(d));

    // 起点先按初始方向走一步，得到初始结点
    if (!inside(r1, c1)) {
        printf("No Solution Possible\n");
        return;
    }

    Node u(dir, c1, r1);
    d[u.r][u.c][u.dir] = 0;
    q.push(u);

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        if (u.r == r2 && u.c == c2) {
            print_ans(u);
            return;
        }

        for (int i = 0; i < 3; i++) {
            Node v = walk(u, i);
            if (has_edge[u.r][u.c][u.dir][i] &&
                inside(v.r, v.c) &&
                d[v.r][v.c][v.dir] < 0) {
                d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
                p[v.r][v.c][v.dir] = u;
                q.push(v);
            }
        }
    }

    printf("No Solution Possible\n");
}

// 递归打印路径，这里用循环逆序追溯
void print_ans(Node u) {
    vector<Node> nodes;

    for (;;) {
        nodes.push_back(u);
        if (d[u.r][u.c][u.dir] == 0) break;
        u = p[u.r][u.c][u.dir];
    }

    // 加入真正的起点
    nodes.push_back(Node(dir, c0, r0));

    int cnt = 0;
    for (int i = nodes.size() - 1; i >= 0; i--) {
        if (cnt % 10 == 0) printf(" ");
        printf(" (%d,%d)", nodes[i].r, nodes[i].c);
        if (++cnt % 10 == 0) printf("\n");
    }
    if (nodes.size() % 10 != 0) printf("\n");
}

// 读取一个测试用例
bool read_case() {
    // 读取迷宫名称，允许名称中有空格
    if (scanf(" %99[^\n]", name) != 1) return false;
    if (strcmp(name, "END") == 0) return false;

    char dirch;
    if (scanf("%d%d %c %d%d", &r0, &c0, &dirch, &r2, &c2) != 5)
        return false;

    dir = dir_id(dirch);
    r1 = r0 + dr[dir];
    c1 = c0 + dc[dir];

    memset(has_edge, 0, sizeof(has_edge));

    int r, c;
    char dch;
    while (scanf("%d", &r) == 1 && r != 0) {
        scanf("%d %c", &c, &dch);
        int di = dir_id(dch);

        char t;
        while (scanf(" %c", &t) == 1 && t != '*') {
            int ti = turn_id(t);
            if (ti >= 0 && ti < 3) {
                has_edge[r][c][di][ti] = true;
            }
        }
    }

    return true;
}

int main() {
    while (read_case()) {
        printf("%s\n", name);
        solve();
    }
    return 0;
}
