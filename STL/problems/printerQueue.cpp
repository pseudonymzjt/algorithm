#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <algorithm>
#include <limits>
using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (N--) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        deque<int> printer;
        int p;
        while (ss >> p) printer.push_back(p);

        int n, time = 0;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (!printer.empty()) {
            int task = printer.front();
            int Max = *max_element(printer.begin(), printer.end());

            if (task == Max) {
                printer.pop_front();
                time++;
                if (n == 0) break;
                n--;
            } else {
                printer.pop_front();
                printer.push_back(task);
                if (n == 0) n = (int)printer.size() - 1;
                else n--;
            }
        }
        cout << time << "\n";
    }
    return 0;
}
