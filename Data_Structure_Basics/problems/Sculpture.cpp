/*
 * 某雕塑由n(n≤50)个边平行于坐标轴的长方体组成。
 * 每个长方体用6个整数xo，yo，2o,x,y,z表示(均为1~500的整数)，
 * 其中xo为长方体的顶点中x坐标的最小值，x表示长方体在x方向的总长度。其他4个值类似定义。
 * 你的任务是统计这个雕像的体积和表面积。
 * 注意，雕塑内部可能会有密闭的空间，其体积应计算在总体积中，
 * 但从“外部”看不见的面不应计入表面积。雕塑可能会由多个连通块组成。
*/
#include <bits/stdc++.h>
using namespace std;

struct Box {
    int x0, x1;
    int y0, y1;
    int z0, z1;
};

// 离散化坐标，并加入外围空气层
void normalize(vector<int>& v) {
    if (v.empty()) {
        v.push_back(0);
        v.push_back(1);
        return;
    }

    int mn = *min_element(v.begin(), v.end());
    int mx = *max_element(v.begin(), v.end());

    // 外面包一层空气
    v.push_back(mn - 1);
    v.push_back(mx + 1);

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << "0 0\n";
        return 0;
    }

    vector<Box> boxes;
    vector<int> xs, ys, zs;

    boxes.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x0, y0, z0, lx, ly, lz;
        cin >> x0 >> y0 >> z0 >> lx >> ly >> lz;

        int x1 = x0 + lx;
        int y1 = y0 + ly;
        int z1 = z0 + lz;

        boxes.push_back({x0, x1, y0, y1, z0, z1});

        xs.push_back(x0);
        xs.push_back(x1);

        ys.push_back(y0);
        ys.push_back(y1);

        zs.push_back(z0);
        zs.push_back(z1);
    }

    // 离散化
    normalize(xs);
    normalize(ys);
    normalize(zs);

    int nx = (int)xs.size() - 1;
    int ny = (int)ys.size() - 1;
    int nz = (int)zs.size() - 1;

    // 每个压缩格子在三个方向上的实际长度
    vector<int> dx(nx), dy(ny), dz(nz);

    for (int i = 0; i < nx; ++i) dx[i] = xs[i + 1] - xs[i];
    for (int j = 0; j < ny; ++j) dy[j] = ys[j + 1] - ys[j];
    for (int k = 0; k < nz; ++k) dz[k] = zs[k + 1] - zs[k];

    auto id = [&](int i, int j, int k) {
        return (i * ny + j) * nz + k;
    };

    int total = nx * ny * nz;

    // solid[i][j][k] 是否为固体
    vector<unsigned char> solid(total, 0);

    // 标记固体
    for (const Box& b : boxes) {
        int ix0 = lower_bound(xs.begin(), xs.end(), b.x0) - xs.begin();
        int ix1 = lower_bound(xs.begin(), xs.end(), b.x1) - xs.begin();

        int iy0 = lower_bound(ys.begin(), ys.end(), b.y0) - ys.begin();
        int iy1 = lower_bound(ys.begin(), ys.end(), b.y1) - ys.begin();

        int iz0 = lower_bound(zs.begin(), zs.end(), b.z0) - zs.begin();
        int iz1 = lower_bound(zs.begin(), zs.end(), b.z1) - zs.begin();

        for (int i = ix0; i < ix1; ++i) {
            for (int j = iy0; j < iy1; ++j) {
                for (int k = iz0; k < iz1; ++k) {
                    solid[id(i, j, k)] = 1;
                }
            }
        }
    }

    // ext 表示该空气格子是否能从外部到达
    vector<unsigned char> ext(total, 0);
    queue<int> q;

    // 把所有边界上的空气格子作为外部空气起点
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                if (i == 0 || i == nx - 1 ||
                    j == 0 || j == ny - 1 ||
                    k == 0 || k == nz - 1) {

                    int idx = id(i, j, k);
                    if (!solid[idx] && !ext[idx]) {
                        ext[idx] = 1;
                        q.push(idx);
                    }
                }
            }
        }
    }

    long long area = 0;

    const int di[6] = {1, -1, 0, 0, 0, 0};
    const int dj[6] = {0, 0, 1, -1, 0, 0};
    const int dk[6] = {0, 0, 0, 0, 1, -1};

    int yz = ny * nz;

    // 外部空气 BFS
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int i = cur / yz;
        int rem = cur % yz;
        int j = rem / nz;
        int k = rem % nz;

        for (int d = 0; d < 6; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];
            int nk = k + dk[d];

            if (ni < 0 || ni >= nx ||
                nj < 0 || nj >= ny ||
                nk < 0 || nk >= nz) {
                continue;
            }

            int nid = id(ni, nj, nk);

            if (solid[nid]) {
                // 当前是外部空气，邻居是固体，说明遇到一个外表面
                if (di[d] != 0) {
                    area += 1LL * dy[j] * dz[k];
                } else if (dj[d] != 0) {
                    area += 1LL * dx[i] * dz[k];
                } else {
                    area += 1LL * dx[i] * dy[j];
                }
            } else if (!ext[nid]) {
                ext[nid] = 1;
                q.push(nid);
            }
        }
    }

    // 统计体积：固体 + 内部密闭空气
    long long volume = 0;

    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                int idx = id(i, j, k);

                // 不是外部空气，就说明属于雕塑外壳包围的部分
                if (!ext[idx]) {
                    volume += 1LL * dx[i] * dy[j] * dz[k];
                }
            }
        }
    }

    cout << volume << ' ' << area << '\n';

    return 0;
}
