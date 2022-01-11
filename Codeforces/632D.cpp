#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

const ll MOD = 1e9 + 7;

using namespace std;

const int MAX = 1e6 + 5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> factors(MAX);
    for (int i = 1; i < factors.size(); i++) {
        for (int j = i; j < factors.size(); j += i) {
            factors[j].push_back(i);
        }
    }
    vector<int> oc;
    oc.assign(MAX, 0);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] <= m) {
            oc[arr[i]]++;
        }
    }
    int bind = 0;
    int myMax = -1;
    for (int lcm = 1; lcm <= m; lcm++) {
        int ans = 0;
        for (int j: factors[lcm]) {
            ans += oc[j];
        }
        if (ans > myMax) {
            myMax = ans;
            bind = lcm;
        }
    }
    vector<int> indices;
    for (int i = 0; i < n; i++) {
        if (bind % arr[i] == 0) {
            indices.push_back(i);
        }
    }
    sort(indices.begin(), indices.end());
    cout << bind << " " << indices.size() << '\n';
    for (int i: indices) {
        cout << i + 1 << ' ';
    }
}
