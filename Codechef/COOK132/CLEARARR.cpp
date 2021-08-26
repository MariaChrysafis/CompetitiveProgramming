#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

#define ll long long
using namespace std;
#define P(x, y) make_pair(x,y)
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
long long solve(){
    long long N, K, X;
    cin >> N >> K >> X;
    vector<long long> A(N);
    long long cur = 0;
    for(int i = 0; i < N; i++){
        cin >> A[i];
        cur += A[i];
    }
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());
    //cout << cur << " ";
    long long myMin = cur;
    for(int i = 0; i < K; i++){
        cur -= A[2 * i] + A[2 * i + 1];
        cur += X;
        myMin = min(myMin, cur);
    }
    return myMin;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        long long x = solve();
        cout << x << '\n';
    }
}
