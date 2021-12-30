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
    int N, K;
    cin >> N >> K;
    int P[N][3];
    vector<int> min_scores;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> P[i][j];
        }
        min_scores.push_back(P[i][0] + P[i][1] + P[i][2]);
    }
    int more[1501];
    for (int i = 0; i <= 1501; i++) {
        more[i] = 0;
    }
    for (int i: min_scores) {
        for (int j = 0; j < i; j++) {
            more[j]++;
        }
    }
    for (int i: min_scores) {
        int most = more[i + 300] + 1;
        cout << (most <= K ? "Yes" : "No") << '\n';
    }


}
