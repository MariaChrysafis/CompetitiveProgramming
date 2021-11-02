#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#define ll unsigned long long
using namespace std;
int dist (pair<int,int> p1, pair<int,int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<int> a, b;
    if ((n * (n + 1)) % 4 == 0){
        ll sum = n * (n + 1)/4;
        for (int i = n ; i >= 1; i--) {
            if (i <= sum) {
                sum -= i;
                a.push_back(i);
            } else {
                b.push_back(i);
            }
        }
    }
    if (a.empty() && b.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        cout << a.size() << '\n';
        for (int i: a) {
            cout << i << ' ';
        }
        cout << '\n' << b.size() << '\n';
        for (int i: b) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
