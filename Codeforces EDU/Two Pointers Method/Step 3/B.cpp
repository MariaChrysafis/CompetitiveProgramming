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
    long long sum = vec[0];
    long long ans = 0;
    for (long long i = 0; i < vec.size(); i++) {
        if (sum > s ) {
            sum -= vec[i];
            continue;
        }
        while (r + 1 != vec.size() && sum + vec[r + 1] <= s) {
            sum += vec[r + 1];
            r++;
        }
        ans += (r - i + 1) * (r - i + 2)/2;
        sum -= vec[i];
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
