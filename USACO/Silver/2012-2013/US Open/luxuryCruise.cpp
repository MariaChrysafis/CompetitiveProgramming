#include <vector>
#include <chrono>
#include <iostream>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

using namespace std;
using namespace std::chrono;

int main() {
    freopen("cruise.in", "r", stdin);
    freopen("cruise.out", "w", stdout);
    int N, M, K;
    cin >> N >> M >> K;
    int left[N];
    int right[N];
    for (int i = 0; i < N; i++) {
        cin >> left[i] >> right[i];
        left[i]--, right[i]--;
    }
    char path[M];
    for (int i = 0; i < M; i++) {
        cin >> path[i];
    }
    int endUp[N];
    for (int i = 0; i < N; i++) {
        int cur = i;
        for (int j = 0; j < M; j++) {
            if (path[j] == 'L') {
                cur = left[cur];
            } else {
                cur = right[cur];
            }
        }
        endUp[i] = cur;
    }
    vector<int> fin = {0};
    bool hasVisited[N]; for(int i = 0; i < N; i++) hasVisited[i] = false;
    hasVisited[0] = true;
    int cur = endUp[0];
    while (!hasVisited[cur]) {
        hasVisited[cur] = true;
        fin.push_back(cur);
        cur = endUp[cur];
    }
    fin.push_back(cur);
    int oc = -1;
    for (int i = 0; i < fin.size(); i++) {
        if (fin[i] == fin.back() && oc == -1) {
            oc = i;
        }
    }
    vector<int> cycle;
    for (int i = oc; i < fin.size() - 1; i++) {
        cycle.push_back(fin[i]);
    }
    vector<int> pref;
    for (int i = 0; i < oc; i++) {
        pref.push_back(fin[i]);
    }
    if (K < pref.size()) {
        cout << pref[K];
        return 0;
    }
    K -= pref.size();
    K %= cycle.size();
    cout << cycle[K] + 1 << endl;
}
