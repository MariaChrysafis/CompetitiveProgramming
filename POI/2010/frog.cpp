#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
const int MOD = 1e9 + 9;
vector<int64_t> arr;
int K;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t N, M;
    cin >> N >> K >> M;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    vector<int> cur(N);
    int l = 0;
    int r = K;
    for (int i = 0; i < N; i++) {
        while (r + 1 < N && arr[r + 1] - arr[i] < arr[i] - arr[l]) {
            l++, r++;
        }
        if (arr[i] - arr[l] >= arr[r] - arr[i]) {
            cur[i] = l;
        } else {
            cur[i] = r;
        }
    }
    vector<int64_t> powr = {1};
    while (powr.size() != 64) {
        powr.push_back(powr.back() * 2);
    }
    int ans[N];
    for (int i = 0; i < N; i++) {
        ans[i] = i;
    }
    for (int j = 0; j < 64; j++) {
        if (M & powr[j]) {
            for (int i = 0; i < N; i++) {
                ans[i] = cur[ans[i]];
            }
        }
        vector<int> nc(N);
        for (int i = 0; i < N; i++) {
            nc[i] = cur[cur[i]];
        }
        cur = nc;
    }
    for (int i: ans) {
        cout << i + 1 << ' ';
    }
}
