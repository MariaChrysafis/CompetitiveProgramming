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
    int l, r;
    l = r = 0;
    long long sum = vec[0];
    long long ans = 0;
    while (r != n) {
        if(sum < s) {
            sum += vec[r + 1];
            r++;
        } else {
            //ans += n - (r - l + 1);
            ans += (n - r);
            //cout << l << " " << r << " " << n - l + 1 << endl;
            sum -= vec[l];
            l++;
        }
    }
    //if(myMin == 1e9) cout << -1;
    cout <<  ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
