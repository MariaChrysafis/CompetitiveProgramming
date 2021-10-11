#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
int main() {
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N, T;
    cin >> N >> T;
    vector<pair<long long, long long>> arr(N);
    vector<long long> v;
    for (int i = 0; i < N; i++) {
        cin >> arr[i].first >> arr[i].second;
        v.push_back(T * arr[i].second + arr[i].first);
    }
    reverse(v.begin(), v.end());
    long long cntr = 0;
    long long myMin = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < myMin) {
            cntr++;
            myMin = v[i];
        }
    }
    cout << cntr + 1 << endl;
}
