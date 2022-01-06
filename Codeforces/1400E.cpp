#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
vector<int> arr;
int cost (int l, int r) {
    if (l == r) {
        if (arr[l] == 0) return 0;
        return 1;
    }
    if (l > r) {
        return 0;
    }
    int myMin = 1e9;
    int ind = -1;
    for (int i = l; i <= r; i++) {
        if (arr[i] <= myMin) {
            ind = i;
            myMin = arr[i];
        }
    }
    assert(ind != -1);
    int ans = r - l + 1;
    for (int i = l; i <= r; i++) {
        arr[i] -= myMin;
    }
    ans = min(ans, cost(l, ind - 1) + cost(ind + 1, r) + myMin);
    for (int i = l; i <= r; i++) {
        arr[i] += myMin;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    cout << cost(0, N - 1);
}
