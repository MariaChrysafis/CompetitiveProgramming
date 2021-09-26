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
    for(int x: vec) {
        if(x >= s) {
            cout << 1;
            return;
        }
    }
    int l, r;
    l = r = 0;
    long long sum = vec[0];
    int myMin = 1e9;
    while (r != n) {
        assert(l <= r);
        if(sum < s) {
            sum += vec[r + 1];
            r++;
        } else {
            myMin = min(myMin, r - l + 1);
            sum -= vec[l];
            l++;
        }
    }
    if(myMin == 1e9) cout << -1;
    else cout << myMin;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
