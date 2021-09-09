#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int main() {
    long long N, A, R, M;
    cin >> N >> A >> R >> M;
    vector<long long> v(N);
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        sum += v[i];
    }
    sort(v.begin(), v.end());
    vector<long long> pref(N + 1);
    vector<long long> suf(N + 1);
    pref[0] = 0;
    suf[suf.size() - 1] = 0;
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + v[i];
    }
    for (int i = N - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + v[i];
    }
    //if it is best to never swap bricks
    long long myMin = LLONG_MAX;
    for (int i = 0; i < N; i++) {
        long long left = pref[i];
        left = v[i] * i - left;
        long long right = suf[i] - v[i];
        right = right - v[i] * (N - i - 1);
        myMin = min(myMin, left * A + right * R);
    }
    for (int i = 0; i < N; i++) {
        long long left = pref[i];
        left = v[i] * i - left;
        long long right = suf[i] - v[i];
        right = right - v[i] * (N - i - 1);
        long long a = min(left, right);
        left -= a;
        right -= a;
        myMin = min(myMin, left * A + right * R + a * M);
    }
    long long left = 0;
    long long right = 0;
    for(int i = 0; i < N; i++){
        if(v[i] < sum/N){
            left += sum/N - v[i];
        }else{
            right += v[i] - sum/N;
        }
    }
    long long a = min(left, right);
    left -= a;
    right -= a;
    myMin = min(myMin, left * A + right * R + a * M);
    a = 0; left = 0; right = 0;
    for(int i = 0; i < N; i++){
        if(v[i] < sum/N + 1){
            left += sum/N + 1 - v[i];
        }else{
            right += v[i] - sum/N - 1;
        }
    }
    a = min(left, right);
    left -= a;
    right -= a;
    myMin = min(myMin, left * A + right * R + a * M);
    cout << myMin << endl;
}
