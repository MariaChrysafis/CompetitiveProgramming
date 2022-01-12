#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve () {
    int N;
    cin >> N;
    map<int, vector<int>> myMap;
    int arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        myMap[arr[i]].push_back(i);
    }
    int dist = 1e9;
    for (auto& p: myMap) {
        for (int j = 1; j < p.second.size(); j++) {
            dist = min(dist, p.second[j] - p.second[j - 1]);
        }
    }
    if (dist == 1e9) {
        cout << "-1\n";
        return;
    }
    cout << N - dist << '\n';
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
