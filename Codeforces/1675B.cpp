#include <bits/stdc++.h>
using namespace std;
int get_max (vector<int> v) {
    int myMax = 0;
    for (int i: v) {
        myMax = max(myMax, i);
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == myMax) {
            return i;
        }
    }
    assert(false);
    return -1;
}
bool increasing (vector<int> v) {
    for (int i = 1; i < v.size(); i++) {
        if (v[i] <= v[i - 1]) {
            return false;
        }
    }
    return true;
}
int solve (vector<int> &v) {
    for (int i = 1; i < (int)v.size(); i++) {
        if (v[i] == v[i - 1] && v[i] == 0) {
            return -INT_MAX;
        }
    }
    if (increasing(v)) return 0;
    if (get_max(v) == (int)v.size() - 1) {
        v.pop_back();
        return solve(v);
    }
    v[get_max(v)] /= 2;
    return solve(v) + 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        int x = solve(v);
        if (x < 0) {
            cout << "-1\n";
        } else {
            cout << x << '\n';
        }
    }
}
