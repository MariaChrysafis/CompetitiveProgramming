#include <bits/stdc++.h>

using namespace std;

vector<int> factors(int x) {
    set<int> s;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            s.insert(i), s.insert(x / i);
        }
    }
    vector<int> v;
    for (int i: s) {
        v.push_back(i);
    }
    return v;
}

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    map<int, int> myMap;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        myMap[v[i]]++;
    }
    for (auto p: myMap) {
        if (p.second * 2 >= n) {
            cout << "-1\n";
            return;
        }
    }
    int ans = 0;
    int cnt = 1000;
    while (cnt--) {
        int a = rand() % n;
        int b = rand() % n;
        if (a == b) {
            continue;
        }
        vector<int> vec = factors(abs(v[a] - v[b]));
        for (int i: vec) {
            map<int, int> oc;
            for (int j = 0; j < v.size(); j++) {
                if (v[j] >= 0) oc[v[j] % i]++;
                else oc[(i - (-v[j]) % i) % i]++;
            }
            bool fine = false;
            for (auto p: oc) {
                if (p.second * 2 >= n) {
                    fine = true;
                    break;
                }
            }
            if (fine) {
                ans = max(ans, i);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
