#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve () {
    set<int> v[4];
    for(int i = 0; i < 4; i++) {
        int n;
        cin >> n;
        for(int j = 0; j < n; j++) {
            int x;
            cin >> x;
            v[i].insert(x);
        }
    }
    vector<pair<int,vector<int>>> vec;
    for(int k = 0; k < 4; k++) {
        for (int i: v[k]) {
            bool valid = true;
            int cntr = 0;
            vector<int> soFar(4);
            soFar[k] = i;
            for (int j = 0; j < 4; j++) {
                if (j == k) continue;
                auto it = v[j].lower_bound(i);
                if(it == v[j].end()) {
                    valid = false;
                    break;
                } else {
                    cntr = max(cntr, *it);
                    soFar[j] = *it;
                }
            }
            if(valid) {
                vec.emplace_back(cntr - i, soFar);
            }
        }
    }
    sort(vec.begin(), vec.end());
    vector<int> ans = vec[0].second;
    for(int i: ans) {
        cout << i << ' ';
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
