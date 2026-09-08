/* 
* 输入若干行代码，要求各列单词的左边界对齐且尽量靠左，单词之间至少要空一格
* 每个单词不超过 80 个字符，每行不超过 180 个字符，一共最多 1000 行
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const int maxcol = 180;
const int maxn = 1000 + 10;
vector<vector<string>> words;
vector<size_t> longest;

// 输出字符串，不足length时末尾补extra
void print(const string &s, int len, char extra) {
    cout << s;
    for(int i = 0; i < len - s.length(); i++) {
        cout << extra;
    }
}

int main() {
    string s, buf;
    for(int i = 0; getline(cin, s); i++) {
        stringstream ss(s);
        vector<string> line;
        while(ss >> buf) {
            line.push_back(buf);
            if(longest.size() < line.size()) longest.push_back(0);
            longest[line.size() - 1] = max(longest[line.size() - 1], buf.length());
        }
        words.push_back(line);
    }

    for(int i = 0; i < words.size(); i++) {
        for(int j = 0; j < words[i].size(); j++) {
            print(words[i][j], longest[j] + 1, ' ');
        }
        cout << '\n';
    }

    return 0;
}