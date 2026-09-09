#include <iostream>
#include <set>
using namespace std;

typedef struct Point {
    int x;
    int y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
    bool operator < (const Point& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
}P;

set<P> points;
float symLine;

int main() {
    int N, n;
    cin >> N;
    while(N--) {
        cin >> n;
        if(--n == 0) {cout << "YES" << '\n'; continue;}
        int x1, y1, x2, y2;
        cin >> x1 >> y1;
        points.insert(Point(x1, y1));
        cin >> x2 >> y2;
        points.insert(Point(x2, y2));
        --n;
        if(y1 == y2) {
            if(n == 0) {cout << "YES" << '\n'; continue;}
            else {symLine = (x1 + x2) / 2.; points.clear();}
        }
        while(n--) {
            cin >> x2 >> y2;
            points.insert(Point(x2, y2));
            auto it = points.find(Point((int)(2 * symLine - x2), y2));
            if(it != points.end()) {points.erase(it); points.erase(Point(x2, y2));}
        }
        if(points.size() == 0) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}