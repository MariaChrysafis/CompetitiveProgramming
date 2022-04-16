#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <set>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> q;
    map<int64_t,int64_t> myMap;
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int64_t k, v; cin >> k >> v;
            myMap[k] = v;
        } else {
            int64_t x; cin >> x;
            if (!myMap.count(x)) cout << 0 << '\n';
            else cout << myMap[x] << '\n';
        }
    }
}
