#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, X;
    cin >> N >> X;
    X--;
    int a[N];
    bool know_secret[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        a[i]--;
        know_secret[i] = false;
    }
    vector<int> q;
    q.push_back(X);
    int cntr = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop_back();
        if (know_secret[cur]) {
            continue;
        }
        know_secret[cur] = true;
        cntr++;
        q.push_back(a[cur]);
    }
    cout << cntr;


}
