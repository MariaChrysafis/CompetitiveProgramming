#include <vector>
#include <chrono>
#include <iostream>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

using namespace std;
using namespace std::chrono;

void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
    int n;
    cin >> n;
    vector<long long> v = {0};
    while(v.size() != n + 1) {
        long long x;
        cin >> x;
        v.push_back(x);
    }
    v.push_back(0);
    long long ans = 0;
    for (int i = 1; i < v.size(); i++) {
        ans += abs(v[i] - v[i - 1]);
    }
    cout << ans/2 << endl;
}
