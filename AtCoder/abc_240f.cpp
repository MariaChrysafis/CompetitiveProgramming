#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<pair<int64_t,int64_t>> vec(N);
        for (int i = 0; i < N; i++) {
            cin >> vec[i].first >> vec[i].second;
            assert(vec[i].second >= 0);
        }
        int64_t pref_sum = 0; //sum of elements
        int64_t ans = 0;
        int64_t myMax = -LLONG_MAX;
        for (int i = 0; i < N; i++) {
            //int64_t prev = 0;
            //ans += pref_sum * vec[i].second;
            //pref_sum += vec[i].second * vec[i].first;
            //ans += vec[i].second * (vec[i].second + 1)/2 * vec[i].first;
            if (vec[i].first != 0) {
                int64_t c1 = -pref_sum/vec[i].first;
                for (int64_t c = c1 - 10; c <= c1 + 10; c++) {
                    if (c <= vec[i].second && c >= 0) {
                        int64_t d1 = pref_sum * c + vec[i].first * (c + 1) * c / 2;
                        if (c != 0) myMax = max(myMax, ans + d1);
                    }
                }
            }
            ans += pref_sum * vec[i].second;
            pref_sum += vec[i].second * vec[i].first;
            ans += vec[i].second * (vec[i].second + 1)/2 * vec[i].first;
            myMax = max(ans, myMax);
            //cout << myMax << '\n';
        }
        cout << myMax << '\n';
    }
}
