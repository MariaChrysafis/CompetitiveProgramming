#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
 
using namespace std;
 
struct portal{
    int x;
    int y;
    bool b;
};
 
vector<portal> v;
 
int binSearch(int l, int r, int cur){
    if(l == r){
        return l;
    }
    int mid = (l + r)/2;
    if(v[mid].x > v[cur].y){
        return binSearch(l, mid, cur);
    }else{
        return binSearch(mid + 1, r, cur);
    }
}
 
const int MOD = 998244353;
 
void solve() {
    int n;
    cin >> n;
    //vector<portal> v(n);
    v.resize(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].x >> v[i].y >> v[i].b;
    }
    vector<long long> pref;
    pref.push_back(0);
    vector<long long> q;
    for(int i = 0; i < n; i++){
        long long prev = v[i].x - v[i].y;
        long long start = binSearch(0, n - 1, i);
        if(start <= i - 1){
            prev += (pref[i] - pref[start] + MOD) % MOD;
            if(prev >= MOD){
                prev -= MOD;
            }
        }
        q.push_back(prev);
        pref.push_back(pref.back() + prev);
        //cout << q.back() << " " << pref.back() << endl;
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(v[i].b){
            ans += q[i];
            if(ans >= MOD) ans -= MOD;
        }
    }
    cout << (ans + v[n - 1].x + 1) % MOD << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
