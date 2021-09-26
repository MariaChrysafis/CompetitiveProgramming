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
    for(int i = 0; i < n; i++) cin >> v1[i];
    for(int i = 0; i < m; i++) cin >> v2[i];
    int p1 = 0;
    int p2 = 0;
    vector<int> vec;
    while(p1 != n || p2 != m) {
        if(p1 == n) {
            vec.push_back(v2[p2]);
            p2++;
        } else if (p2 == m) {
            vec.push_back(v1[p1]);
            p1++;
        } else if (v1[p1] < v2[p2]) {
            vec.push_back(v1[p1]);
            p1++;
        } else {
            vec.push_back(v2[p2]);
            p2++;
        }
    }
    for (int i: vec) {
        cout << i << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
