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

vector<long long> read(long long K, long long N){
    vector<long long> v(N);
    for(int i = 0; i < K; i++){
        cin >> v[i];
    }
    long long A, B, C, D;
    cin >> A >> B >> C >> D;
    for(int i = K; i < N; i++){
        v[i] = (v[i - 2] * A + v[i - 1] * B + C) % D;
    }
    return v;
}

void solve() {
    long long N, K;
    cin >> N >> K;
    vector<long long> v = read(K, N);
    vector<long long> x = read(K, N);
    vector<long long> y = read(K, N);
    //printVector(x);
    //printVector(y);
    //printVector(v);
    long long minTot = 0;
    long long maxTot = 0;
    long long tot = 0;
    for(int i = 0; i < N; i++){
        tot += v[i];
        minTot += x[i], maxTot += x[i] + y[i];
    }
    if(tot > maxTot || tot < minTot){
        cout << -1;
        return;
    }
    long long plus = 0;
    long long minus = 0;
    for(int i = 0; i < N; i++){
        plus += max(0ll, x[i] - v[i]);
        minus += max(0ll, v[i] - (x[i] + y[i]));
    }
    cout << max(plus, minus);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        cout << "Case #" << i + 1 << ": ";
        solve();
        cout << '\n';

    }
}
