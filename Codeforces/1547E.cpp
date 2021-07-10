#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;
const long long INF = 2e9;
void solve(){
    long long n, k;
    cin >> n >> k;
    map<long long,long long> oc;
    long long pos[k];
    long long cool[k];
    for(int i = 0; i < k; i++){
        cin >> pos[i];
        pos[i]--;
    }
    for(int i = 0; i < n; i++){
        oc[i] = -1;
    }
    for(int i = 0; i < k; i++){
        cin >> cool[i];
        oc[pos[i]] = i;
    }
    long long pref[n];
    pref[0] = INF;
    if(oc[0] != -1){
        pref[0] = cool[oc[0]];
    }
    for(int i = 1; i < n; i++){
        if(oc[i] != -1){
            pref[i] = min(pref[i - 1] + 1, cool[oc[i]]);
        }else{
            pref[i] = pref[i - 1] + 1;
        }
    }
    long long suf[n];
    suf[n - 1] = INF;
    if(oc[n - 1] != -1){
        suf[n - 1] = cool[oc[n - 1]];
    }
    for(int i = n - 2; i >= 0; i--){
        if(oc[i] != -1){
            suf[i] = min(suf[i + 1] + 1, cool[oc[i]]);
        }else{
            suf[i] = suf[i + 1] + 1;
        }
    }
    for(int i = 0; i < n; i++){
        cout << min(suf[i], pref[i]) << " ";
    }
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
