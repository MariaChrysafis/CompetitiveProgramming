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
#include <limits.h>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    K--;
    vector<int> arr(N);
    vector<int> dif;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        if (i != 0) {
            dif.push_back(arr[i] - arr[i - 1] - 1);
        }
    }
    sort(dif.begin(), dif.end());
    int64_t ans = N;
    while (!dif.empty() && K--) {
        dif.pop_back();
    }
    while (!dif.empty()) {
        ans += dif.back();
        dif.pop_back();
    }
    cout << ans;
}
