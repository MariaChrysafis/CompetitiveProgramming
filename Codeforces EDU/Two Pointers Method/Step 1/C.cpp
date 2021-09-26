#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve () {
    int n, m;
    cin >> n >> m;
    vector<int> v1(n), v2(m);
    map<int,long long> m1, m2;
    for(int i = 0; i < n; i++) cin >> v1[i], m1[v1[i]]++;
    for(int i = 0; i < m; i++) cin >> v2[i], m2[v2[i]]++;
    long long ans = 0;
    for(pair<int,int> p: m1) {
        ans += p.second * m2[p.first];
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
