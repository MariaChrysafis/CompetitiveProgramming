#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
int X;
vector<int> baseK (int x, int k) {
    vector<int> v;
    int pwr = 1;
    for (int i = 0; i <= X; i++) {
        v.push_back(x/pwr % k);
        pwr *= k;
    }
    return v;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    X = ceil(log(N)/log(K));
    cout << X << '\n';
    for (int i = 0; i < N; i++) {
        vector<int> v1 = baseK(i, K);
        for (int j = i + 1; j < N; j++) {
            vector<int> v2 = baseK(j, K);
            for (int ind = v1.size() - 1; ind >= 0; ind--) {
                if (v1[ind] != v2[ind]) {
                    cout << ind + 1 << ' ';
                    break;
                }
            }
        }
    }
}
