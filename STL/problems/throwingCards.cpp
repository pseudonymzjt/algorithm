#include <iostream>
#include <deque>
using namespace std;

deque<int> cards;

int main() {
    int n; cin >> n;

    int i = 0;
    while(++i <= n) cards.push_back(i);
    
    while(cards.size() >= 2) {
        cout << cards.back() << '\n'; 
        cards.pop_back(); 
        cards.push_front(cards.back());
        cards.pop_back();
    }
    cout << cards.back() << '\n';
    return 0;
}