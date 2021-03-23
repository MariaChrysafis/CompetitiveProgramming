#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int solve(){
    int N;
    cin >> N;
    int M;
    cin >> M;
    vector<int> v(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    long long cur = 0;
    int cntr = 0;
    for(int i: v){
        cntr++;
        cur += i;
        if(cur > M){
            return cntr;
        }
    }
    return N + 1;
}
int main(){
    int T;
    cin >> T;
    int orig = T;
    while(T--){
      cout << "Case #" << orig - T << ": ";
        int x = solve();
        cout << x - 1 << endl;
    }
}
