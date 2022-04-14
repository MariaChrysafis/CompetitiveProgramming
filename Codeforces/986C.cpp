#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
vector<bool> hasVisited;
int M, N;
vector<int> arr;
int myMap[(1 << 22)];
void dfs (int curNode) {
    if (hasVisited[curNode]) return;
    hasVisited[curNode] = true;
    if (curNode >= M) {
        curNode -= M;
        for (int j = 0; j < N; j++) {
            if ((curNode & (1 << j)) == 0) {
                dfs (M + (curNode ^ (1 << j)));
            }
        }
        if (myMap[((1 << N) - 1) ^ curNode] != -1) {
            dfs (myMap[((1 << N) - 1) ^ curNode]);
        }
        curNode += M;
    }
    if (curNode < M) {
        dfs (M + arr[curNode]);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < (1 << 22); i++) {
        myMap[i] = -1;
    }
    cin >> N >> M;
    hasVisited.assign(M + (1 << N), false);
    arr.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> arr[i];
        myMap[arr[i]] = i;
    }
    int cntr = 0;
    for (int i = 0; i < M; i++) {
        if (!hasVisited[i]) {
            dfs (i);
            cntr++;
        }
    }
    cout << cntr;
    return 0;
}
