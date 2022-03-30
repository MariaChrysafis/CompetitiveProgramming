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
int main () {
    int N;
    cin >> N;
    vector<pair<int64_t,int64_t>> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    sort(vec.begin(), vec.end());
    vector<int64_t> pref(N + 1); pref[0] = 0; for (int i = 1; i <= N; i++) pref[i] = pref[i - 1] + vec[i - 1].second;
    vector<int64_t> p(N + 1); p[0] = -pref[0] + vec[0].first; for (int i = 1; i <= N; i++) p[i] = max(p[i - 1], vec[i].first - pref[i]);
    int64_t myMax = 0;
    for (int j = 0; j < N; j++) {
        myMax = max(myMax, pref[j + 1] - vec[j].first + p[j]);
    }
    cout << myMax;
}
