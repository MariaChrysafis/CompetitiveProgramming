#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#define ll int
using namespace std;
int india = 0;
int england = 0;
void solve(int x) {
    if (x == 0) india++, england++;
    else if (x == 1) india++;
    else england++;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        india = england = 0;
        vector<int> v(5);
        for (int i = 0; i < 5; i++) {
            int x;
            cin >> x;
            solve(x);
        }
        if (india == england) {
            cout << "DRAW\n";
        } else if (india > england) {
            cout << "INDIA\n";
        } else {
            cout << "ENGLAND\n";
        }
    }
}
