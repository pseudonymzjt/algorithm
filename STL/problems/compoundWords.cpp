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