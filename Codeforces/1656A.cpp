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
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<pair<int,int>> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i].first; arr[i].second = i;
        }
        sort(arr.begin(), arr.end());
        cout << arr[0].second + 1 << " " << arr.back().second + 1 << '\n';
    }

}
