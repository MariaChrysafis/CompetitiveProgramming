#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
 
using namespace std;
 
bool compare(vector<int> v1, vector<int> v2) {
    int cntr = 0;
    for (int i = 0; i < 5; i++) {
        if (v1[i] < v2[i]) {
            cntr++;
        }
    }
    return (cntr >= 3);
}
 
bool comp(vector<int> v1, vector<int> v2) {
    sort(v1.begin(), v1.end()), sort(v2.begin(), v2.end());
    int x = v1[0] + v1[1] + v1[2];
    int y = v2[0] + v2[1] + v2[2];
    return (x < y);
}
 
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> v(n);
    vector<int> myMap(50001);
    for (int i = 0; i < n; i++) {
        v[i].resize(5);
        for (int j = 0; j < 5; j++) {
            cin >> v[i][j];
        }
        myMap[v[i][0]] = i + 1;
    }
    sort(v.begin(), v.end(), comp);
    for (int i = 0; i < n; i++) {
        bool fine = true;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (!compare(v[i], v[j])) {
                fine = false;
                break;
            }
        }
        if (fine) {
            cout << myMap[v[i][0]] << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
