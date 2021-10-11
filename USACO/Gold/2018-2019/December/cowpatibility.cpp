#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

struct Vector {
    int arr[5] = {0, 0, 0, 0, 0};

    int sz() {
        for (int i = 0; i < 5; i++) {
            if (arr[i] == 0) {
                return i;
            }
        }
        return 5;
    }
};

bool operator<(const Vector &a, const Vector &b) {
    for (int j = 0; j < 5; j++) {
        if (a.arr[j] < b.arr[j]) return true;
        if (a.arr[j] > b.arr[j]) return false;
    }
    return false;
}

int main() {
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map<Vector, long long> myMap;
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
        for (int j = 0; j < 32; j++) {
            Vector sub;
            int cntr = 0;
            for (int k = 0; k < 5; k++) {
                if (temp[j][k]) {
                    sub.arr[cntr] = vec[k];
                    cntr++;
                }
            }
            myMap[sub]++;
        }
    }
    long long ans = 0;
    for (pair<Vector, long long> p: myMap) {
        if (p.first.sz() % 2 == 1) {
            ans -= p.second * (p.second - 1) / 2;
        } else {
            ans += p.second * (p.second - 1) / 2;
        }
    }
    cout << ans;
}
