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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    vector<pair<string,int>> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i].first; arr[i].second = i;
    }
    random_shuffle(arr.begin(), arr.end());
    vector<pair<int,int>> blocks;
    int sq = 400;
    for (int i = 0; i < N/sq; i++) {
        blocks.push_back({i * sq, i * sq + sq - 1});
    }
    if (blocks.empty()) blocks.push_back({0, N - 1});
    else blocks.back().second = N - 1;
    int id[N];
    int myMap[256];
    myMap['A'] = 0, myMap['C'] = 1, myMap['G'] = 2, myMap['T'] = 3;
    int oc[blocks.size()][M][4];
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 4; k++) {
                oc[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = blocks[i].first; j <= blocks[i].second; j++) {
            id[j] = i;
            for (int k = 0; k < M; k++) {
                oc[i][k][myMap[arr[j].first[k]]]++;
            }
        }
    }
    vector<bool> pos(N);
    for (int i = 0; i < N; i++) {
        pos[i] = true;
    }
    for (int i = 0; i < N; i++) {
        for (int index = 0; index < blocks.size(); index++) {
            int tot = 0;
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < 4; k++) {
                    if (k != myMap[arr[i].first[j]]) {
                        tot += oc[index][j][k];
                    }
                }
            }
            if (tot != (blocks[index].second - blocks[index].first + 1 - (index == id[i])) * K) {
                pos[i] = false;
                break;
            }
        }
    }
    for (int j = 0; j < pos.size(); j++) {
        if (!pos[j]) continue;
        bool fine = true;
        for (int i = 0; i < N; i++) {
            if (i == j) continue;
            int cntr = 0;
            for (int k = 0; k < M; k++) {
                cntr += (arr[j].first[k]!= arr[i].first[k]);
            }
            if (cntr != K) {
                fine = false;
                break;
            }
        }
        if (fine) {
            cout << arr[j].second + 1;
            exit(0);
        }
    }
}
