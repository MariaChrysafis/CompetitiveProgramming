#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> v;
    v.push_back("");
    for(int i = 0; i < n; i++) {
        v.back() += '(';
        v.back() += ')';
    }
    string prev = v.back();
    for(int i = 0; i + 3 < 2 * n; i++) {
        string prev1 = prev;
        prev[i] = prev[i + 1] = '(';
        prev[i + 2] = prev[i + 3] = ')';
        v.push_back(prev);
        prev = prev1;
    }
    for(int i = 0; i < n; i++) {
        cout << v[i] << "\n";
    }
    cout << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
