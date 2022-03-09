#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
vector<int> state;
set<int> s;
map<int,int> myMap;
vector<int> a;
vector<int> v;
void update (int x, bool b) {
    if (state[x] == -1) {
        state[x] = b;
    } else if (state[x] != b) {
        cout << "NO\n";
        exit(0);
    } else {
        return;
    }
    update(myMap[v[b] - a[x]], b);
    if (myMap.count(v[!b] - a[x])) {
        update(myMap[v[!b] - a[x]], b);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    v.resize(2);
    cin >> N >> v[0] >> v[1];
    a.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        s.insert(a[i]);
        myMap[a[i]] = i;
    }
    state.assign(N, -1);
    for (int i = 0; i < N; i++) {
        if (!s.count(v[1] - a[i])) {
            update(myMap[a[i]], false);
        }
        if (!s.count(v[0] - a[i])) {
            update(myMap[a[i]], true);
        }
    }
    cout << "YES\n";
    for (int i: state) {
        cout << max(i, 0) << ' ';
    }
}
