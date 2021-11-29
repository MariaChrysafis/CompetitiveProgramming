#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <set>
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, x;
    cin >> n >> x;
    set<int> valid;
    for (int i = 1; i < (1 << n); i++) {
        valid.insert(i);
    }
    valid.erase(x);
    vector<int> ans = {0};
    while (!valid.empty()) {
        auto it = valid.begin();
        int val = *it;
        ans.push_back(val);
        valid.erase(it);
        valid.erase(val ^ x);
    }
    vector<int> res;
    for (int i = 0; i < ans.size() - 1; i++) {
        res.push_back(ans[i] ^ ans[i + 1]);
    }
    cout << res.size() << '\n';
    for (int i: res) {
        cout << i << ' ';
    }
    cout << '\n';
}
