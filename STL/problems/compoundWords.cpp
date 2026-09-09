/*
* 输出若干行按字典序排列的单词，每行均为一个由小写字母组成的单词
* 输出所有的复合词（指恰由两个单词拼成的单词），按字典序排列
*/
#include <set>
#include <string>
#include <iostream>
using namespace std;

int main() {
    set<string> dict;
    string word;
    while(cin >> word) {
        dict.insert(word);
    }
    for(const auto &w : dict) {
        for(size_t i = 1; i < w.size(); ++i) {
            if(dict.count(w.substr(0, i)) && dict.count(w.substr(i))) {
                cout << w << '\n';
                break;
            }
        }
    }
    return 0;
}