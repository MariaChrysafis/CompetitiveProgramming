#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <climits>
#include <cmath>
#include <set>
using namespace std;
int64_t x;
vector<int64_t> create (vector<int64_t> v) {
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<int64_t> ans;
    for (int i = 0; i < (1 << (int)v.size()); i++) {
        int64_t sum = 0;
        bool f = true;
        for (int j = 0; j < v.size(); j++) {
            if (i & (1 << j)) {
                sum += v[j];
                if (sum > x) {
                    f = false;
                    break;
                }
            }
        }
        if (f) {
            ans.push_back(sum);
        }
    }
    return ans;
}
int main() {
    int n;
    cin >> n >> x;
    vector<int64_t> a(n/2), b(n - n/2);
    for (int i = 0; i < n/2; i++)
        cin >> a[i];
    for (int i = n/2; i < n; i++)
        cin >> b[i - n/2];
    vector<int64_t> ma = create(a), mb = create(b);
    map<int64_t,int> cnt; for (int64_t v: mb) cnt[v]++;
    int64_t ans = 0;
    for (int64_t v: ma) {
        if (cnt.count(x - v)) {
            ans += cnt[x - v];
        }
    }
    cout << ans;
 
}
