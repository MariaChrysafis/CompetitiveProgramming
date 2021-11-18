#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<long long> solver (int n, int m) {
    if (n == 1) {
        return {m};
    }
    vector<long long> v(n - 1);
    set<long long> s;
    int XOR = 0;
    for (int i = 0; i < n - 1; i++) {
        v[i] = rng();
        v[i] %= 1000000;
        while (s.count(v[i])) {
            v[i] = rng();
            v[i] %= 1000000;
        }
        s.insert(v[i]);
        XOR ^= v[i];
    }
    if (s.count(XOR ^ m)) {
        return {};
    }
    v.push_back(XOR ^ m);
    return v;
}
void print (vector<long long> v) {
    cout << "YES\n";
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    if (n == 2 && m == 0) {
        cout << "NO\n";
        return 0;
    }
    while (true) {
        vector<long long> v = solver(n, m);
        if (!v.empty()) {
            print(v);
            return 0;
        }
    }
}
