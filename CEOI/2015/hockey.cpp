#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
using namespace std;
vector<int64_t> construct (vector<int64_t> a) {
    vector<int64_t> v1;
    for (int i = 0; i < (1 << (int)a.size()); i++) {
        int64_t x = 0;
        for (int j = 0; j < a.size(); j++) {
            if (i & (1 << j)) {
                x += a[j];
            }
        }
        v1.push_back(x);
    }
    sort(v1.begin(), v1.end());
    return v1;
}
int main () {
    int64_t n, m;
    cin >> n >> m;
    vector<int64_t> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int64_t> a, b;
    for (int i = 0; i < n/2; i++) {
        a.push_back(arr[i]);
    }
    for (int i = n/2; i < n; i++) {
        b.push_back(arr[i]);
    }
    vector<int64_t> v1 = construct(a), v2 = construct(b);
    int a1 = -1;
    int a2 = v2.size() - 1;
    int64_t ans = 0;
    while (true) {
        a1++;
        if (a1 == v1.size() || v1[a1] + v2[0] > m) {
            break;
        }
        while (v1[a1] + v2[a2] > m) {
            a2--;
        }
        ans += a2 + 1;
        //cout << a1 << " " << a2 << '\n';
    }
    cout << ans;
}
