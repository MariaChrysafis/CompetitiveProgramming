#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
#include <queue>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N); for (int i = 0; i < N; i++) cin >> v[i];
    sort(v.begin(), v.end());
    deque<int> d;
    for (int i: v) {
        d.push_back(i);
    }
    int64_t ans = 0;
    while (!d.empty()) {
        if (d.size() <= 2) {
            while (!d.empty()) {
                ans += d.back(), d.pop_back();
            }
            break;
        }
        ans += d.back();
        d.pop_back();
        ans += d.back();
        d.pop_back();
        d.pop_back();
    }
    cout << ans;
}
