#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

string sorted(string s) {
    sort(s.begin(), s.end());
    return s;
}

void print (vector<pair<int,int>> vec) {
    cout << vec.size() << '\n';
    for (pair<int,int> p: vec) {
        cout << p.first + 1 << " " << p.second + 1 << '\n';
    }
    cout << '\n';
}

struct triple {
    int x, y, z;
};

void solve () {
    int n;
    cin >> n;
    vector<int> sorted(n);
    for (int i = 0; i < n; i++) {
        cin >> sorted[i];
    }
    vector<int> orig = sorted;
    sort(sorted.begin(), sorted.end());
    vector<triple> ans;
    for (int i = 0; i < n; i++) {
        if (orig[i] == sorted[i]) {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (orig[j] == sorted[i]) {
                ans.push_back({i, j, j - i});
                vector<int> new_vec;
                for(int k = i; k <= j; k++) {
                    if(k == i) new_vec.push_back(orig[j]);
                    else new_vec.push_back(orig[k - 1]);
                }
                int cntr = i;
                for(int k: new_vec) {
                    orig[cntr] = k;
                    cntr++;
                }
                break;
            }
        }
    }
    assert(orig == sorted);
    cout << ans.size() << endl;
    for(triple t: ans) {
        cout << t.x + 1 << " " << t.y + 1 << " " << t.z << '\n';
    }
    cout << '\n';
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
