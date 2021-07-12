#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <set>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void print(vector<bool> v){
    for(bool i: v){
        cout << i << " ";
    }
    cout << endl;
}
string yesNo(bool b){
    if(b) return "YES";
    return "NO";
}
void solve(){
    vector<long long> v1, v2;
    long long n;
    cin >> n;
    v1.resize(n);
    v2.resize(n);
    for(long long i = 0; i < n; i++){
        cin >> v1[i];
        v1[i] *= ((n - i) * (i + 1));
    }
    for(int i = 0; i < n; i++){
        cin >> v2[i];
    }
    sort(v1.begin(), v1.end());
    reverse(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    long long cntr = 0;
    for(int i = 0; i < n; i++){
        cntr += (((v1[i]) % 998244353) * v2[i]) % 998244353;
        cntr %= 998244353;
    }
    cout << cntr << endl;
}
int main() {
    int t = 1;
    while(t--){
        solve();
    }
}
