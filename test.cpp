#include <vector>
#include <chrono>
#include <iostream>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,fma")

using namespace std;
using namespace std::chrono;

struct cntBitsCmp {
    bool operator()(vector<int> a, vector<int> b) {
        //return cntBits(a) < cntBits(b);
        for (int i = 0; i < a.size(); i++) {
            if (a[i] < b[i]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map<vector<int>, int> myMap;
    vector<vector<bool>> temp(32);
    for (int i = 0; i < 32; i++) {
        temp[i].resize(5);
        for (int k = 0; k < 5; k++) {
            if (i & (1 << k)) {
                temp[i][k] = ((i & (1 << k)) > 0);
            }
        }
    }
    long long n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        vector<int> vec(5);
        for (int j = 0; j < 5; j++) {
            cin >> vec[j];
        }
        sort(vec.begin(), vec.end());
        for (int j = 1; j < 32; j++) {
            vector<int> sub;
            for (int k = 0; k < 5; k++) {
                if (temp[j][k]) {
                    sub.push_back(vec[k]);
                }
            }
            myMap[sub]++;
        }
    }
    long long ans = 0;
        for (auto p: myMap) {
            if (p.first.size() % 2 == 1) {
                ans -= p.second * (p.second - 1) / 2;
            } else {
                ans += p.second * (p.second - 1) / 2;
            }
        }
    cout << n * (n - 1)/ 2 + ans;
}
