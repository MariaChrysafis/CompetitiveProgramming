#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

template<typename T>
T readVal() {
    T n;
    cin >> n;
    return n;
}

template<typename T>
vector<T> readVector(T n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

void solve() {
    float a, b;
    cin >> a >> b;
    a *= 2;
    b *= 2;
    cout << setprecision(32) << floor(max((a - 1) * floor(b/sqrt(3)), (b - 1) * floor(a/sqrt(3)))) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
