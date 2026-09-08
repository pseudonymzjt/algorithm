/*
* Ducci序列是一个n元组序列，后一项是由前一项以如下方式生成的：
* Ducci[k + 1][i] = |Ducci[k][(i + 1) % n] - Ducci[k][i]|
* 求Ducci序列是否会在若干步之后变为全0组或循环
*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> ducci;
const int max_recur = 1000;

int main() {
    int n, num;
    cin >> n;
    vector<int> ori;
    while(n--) {cin >> num; ori.push_back(num);}
    int len = ori.size();
    ducci.push_back(ori);
    int i = 0;
    for(; i < max_recur; i++) {
        vector<int> newTuple;
        bool end = true;
        for(int p = 0; p < len; p++) {
            int val = max(ducci[i][p], ducci[i][(p + 1) % len]) - min(ducci[i][p], ducci[i][(p + 1) % len]);
            newTuple.push_back(val);
            if(val != 0) end = false;
        }
        cout << "==" << i + 1 << "==" << endl;
        for(int k = 0; k < len; k++) cout << newTuple[k] << "  ";
        cout << endl; 
        ducci.push_back(newTuple);
        if(end) break;
    }
    cout << i + 1 << endl;
    return 0;
}