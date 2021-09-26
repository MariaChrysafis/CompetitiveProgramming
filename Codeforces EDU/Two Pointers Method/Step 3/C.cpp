#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve () {
    int n;
    long long s;
    cin >> n >> s;
    vector<long long> vec;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        vec.push_back(x);
    }
    long long r = 0;
    long long l = 0;
    long long atMost[n];
    for(int i = 0; i < n; i++) {
        atMost[i] = n;
    }
    while (r != n - 1) {
        //cout << l << " " << r << endl;
        if(vec[r + 1] - vec[l] <= s) {
            r++;
        } else {
            atMost[l] = r;
            l++;
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        if(atMost[i] == n) {
            continue;
        }
        ans += n - atMost[i] - 1;
        //cout << i << " " << atMost[i] << endl;
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
