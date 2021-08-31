#include <iostream>
#include <vector>
#define ll long long
using namespace std;
ll solver(ll x, vector<ll> v){
    //first x, then !x
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    ll ans = 0;
    for(int i = 0; i < v.size(); i++){
        int desPos;
        if(v[i] == x){
            desPos = cnt[v[i]] * 2;
            cnt[v[i]]++;
        }else{
            desPos = cnt[v[i]] * 2 + 1;
            cnt[v[i]]++;
        }
        ans += abs(desPos - i);
    }
    return ans;
}
ll solve(int n){
    vector<ll> v(n);
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        v[i] %= 2;
        cnt[v[i]]++;
    }
    if(abs(cnt[0] - cnt[1]) > 1){
        return -1;
    }
    ll myMin = 1e12;
    if(cnt[0] >= cnt[1]) myMin = min(myMin, solver(0, v));
    if(cnt[1] >= cnt[0]) myMin = min(myMin, solver(1, v));
    return myMin/2;
}
int main(int argc, const char * argv[]) {
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int x = solve(n);
        cout << x << endl;
    }
}
