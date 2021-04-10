#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
vector<int> cnt;
vector<int> d;
int n = pow(10,7) + 2;
void sieve(){
    for(int i = 0; i < d.size(); i++){
        d[i] = 0;
        cnt[i] = -1;
    }
    for(int i = 1; i < n; i++){
        for(int j = i; j < n; j += i){
            d[j] += i;
        }
    }
    for(int i = 0; i < d.size(); i++){
        if(d[i] < n && cnt[d[i]] == -1){
            cnt[d[i]] = i;
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cnt.resize(n);
    d.resize(n);
    sieve();
    int t;
    cin >> t;
    while(t--){
        int a;
        cin >> a;
        cout << cnt[a] << '\n';
    }
}
