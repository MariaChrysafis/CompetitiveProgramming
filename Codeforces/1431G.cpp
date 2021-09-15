#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

template<typename T>
T readVal() {
    T n;
    cin >> n;
    return n;
}

template<typename T>
vector<T> readVector(T n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

const int INF = 1e9;

vector<vector<int>> dp1;
vector<vector<int>> dp2;
vector<int> arr;

int memoize(int pref, int K){
    if(K == 0){
        return (dp2[pref][K] = 0);
    }
    if(pref + 1 == K * 2){
        return (dp2[pref][K] = dp1[0][pref]);
    }
    if(pref + 1 < K * 2){
        return (dp2[pref][K] = -INF);
    }
    if(dp2[pref][K] != -1){
        return dp2[pref][K];
    }
    long long ans = memoize(pref - 1, K);
    //ans = max(ans, memoize(pref - 2, K - 1) + arr[pref] - arr[pref - 1]);
    for(int i = 0; i < pref; i ++){
        if(i % 2 == pref % 2) {
            long long val = dp1[i + 1][pref];
            long long len = (pref - (i + 1) + 1);
            if(len < 0 || K - len/2 < 0) continue;
            val += memoize(i, K - len / 2);
            ans = max(ans, val);
        }
    }
    return (dp2[pref][K] = ans);
}

void solve() {
    int N = readVal<int>();
    int K = readVal<int>();
    arr = readVector<int>(N);
    sort(arr.begin(), arr.end());
    dp1.resize(N);
    for (int i = 0; i < N; i++) {
        dp1[i].resize(N);
        for (int j = 0; j < N; j++) {
            dp1[i][j] = -1;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j += 2) {
            int ans = 0;
            for(int k = i; k <= j; k++){
                if(k > i + j - k) {
                    ans += arr[k] - arr[i + j - k];
                }
            }
            dp1[i][j] = ans;
        }
    }
    dp2.resize(N);
    for(int i = 0; i < N; i++){
        dp2[i].resize(N);
        for(int j = 0; j < N; j++){
            dp2[i][j] = -1;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= K; j++){
            memoize(i, j);
        }
    }
    cout << dp2[N - 1][K] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
