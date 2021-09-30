#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;
void print(vector<int> v) {
    for(int i: v) cout << i << " ";
    cout << endl;
}

bool possible(long long n, long long m, long long k) {
    if(n == 1 && m == 0 && k == 0) return true;
    if(k <= 0) return false;
    if(n * (n - 1)/2 < m) return false;
    if(m + 1 < n) return false;
    if(k == 1) {
        return (n * (n - 1)/2 == m);
    }
    return true;
}

void solve() {
    long long n, m, k;
    cin >> n >> m >> k;
    bool b = possible(n, m, k - 2);
    if(b) cout << "YES\n";
    else cout << "NO\n";
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
