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
    vector<vector<int>> v;
    map<vector<int>, bool> myMap;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        v[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> v[i][j];
        }
    }
    int k;
    cin >> k;
    vector<vector<int>> forbidden(k);
    for (int i = 0; i < k; i++) {
        forbidden[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> forbidden[i][j];
            forbidden[i][j]--;
        }
        myMap[forbidden[i]] = true;
    }

    priority_queue<pair<int, vector<int>>> q;
    vector<int> dum;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        dum.push_back(v[i].size() - 1);
        sum += v[i].back();
    }
    q.push({sum, dum});
    map<vector<int>, bool> hv;
    while (!q.empty()) {
        int orig_sum;
        orig_sum = sum = q.top().first;
        vector<int> vec = q.top().second;
        hv[vec] = true;
        q.pop();
        if (!myMap[vec]) {
            for (int i: vec) {
                cout << i + 1 << " ";
            }
            cout << endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            if (vec[i] != 0) {
                vec[i]--;
                if (hv[vec]) {
                    vec[i]++;
                    continue;
                }
                sum += v[i][vec[i]];
                sum -= v[i][vec[i] + 1];
                q.push(make_pair(sum, vec));
                hv[vec] = true;
                vec[i]++;
                sum = orig_sum;
            }
        }
    }


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
