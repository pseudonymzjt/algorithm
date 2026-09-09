/*
* 交换问题。
* 输入整数 n 表示需要交换的学生数
* 然后输入整数对表示一个学生想要从A交换到B
* 若能两两配对输出 YES，否则输出 NO
*/
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

map<vector<int>, int> students;

int main() {
    int n; scanf_s("%d", &n);
    int start, end;
    while(n--) {
        scanf_s("%d%d", &start, &end);
        
        auto it = students.find({end, start});
        if(it == students.end()) students[{start, end}]++;
        else if(--it->second == 0) students.erase(it);
    }
    if(students.size() > 0) printf("NO\n");
    else printf("YES\n");
    return 0;
}