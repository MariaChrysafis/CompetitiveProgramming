#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
#include <random>
#include <array>
#include <chrono>

using namespace std;

typedef int64_t ll;

int find_max (vector<int>& v) {
    int myMax = 0;
    for (int i: v) {
        myMax = max(myMax, i);
    }
    return myMax;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> a(N), b(N);
        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < N; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < N; i++) {
            if (a[i] > b[i]) {
                swap(a[i], b[i]);
            }
        }
        cout << find_max(a) * find_max(b) << '\n';
    }
}
