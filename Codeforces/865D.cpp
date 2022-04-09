#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>


using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    multiset<int64_t> s;
    int64_t ans= 0;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        if (!s.empty() && *s.begin() < x) ans += (x - (*s.begin())),s.erase(s.begin()),s.insert(x),s.insert(x);
        else s.insert(x);
    }
    cout << ans;
}
