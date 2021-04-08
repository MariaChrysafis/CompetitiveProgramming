#include <iostream>
#include <vector>
#include <algorithm>

#define ll int64_t

using namespace std;

vector<int> v;

ll max(ll a, ll b) {
    if (a > b) {
        return a;
    }
    return b;
}

bool valid(ll f, ll a, ll b) {
    if(f >= abs(a - b)){
        return false;
    }
    for(int i = f - 1; i >= 0; i--){
        if(v[i] > abs(a - b) - f + i + a){
            return false;
        }
    }
    return true;
}

int binSearch(ll l, ll r, ll a, ll b) {
    if(l == r){
        return l;
    }
    int m = (r + l + 1) / 2;
    if (valid(m, a, b)) {
        return binSearch(m, r, a, b);
    } else {
        return binSearch(0, m - 1, a, b);
    }
}


void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--;
    b--;
    if (a > b) {
        a = (n - a - 1);
        b = (n - b - 1);
    }
    v.clear();
    for (int i = 0; i < m; i++) {
        int d;
        cin >> d;
        v.push_back(d);
    }
    sort(v.begin(), v.end());
    ll x = binSearch(0, m, a,b);
    cout << x << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
