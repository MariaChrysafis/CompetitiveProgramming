#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
using namespace std;

typedef int64_t ll;

void solve() {
    int n;
    cin >> n;
    int arr[n];
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (!s.count(arr[i])) {
            s.insert(arr[i]);
        } else if (!s.count(-arr[i])) {
            s.insert(-arr[i]);
        }
    }
    cout << s.size() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
