#include <iostream>
#include <vector>
#include <cmath>
using ll = long long;
using namespace std;
vector<ll> squares;
const ll MAX = 300000;
void solve(){
    int n;
    cin >> n;
    vector<ll> arr(n);
    vector<ll> cnt(MAX);
    for(int i = 0; i < MAX; i++){
        cnt[i] = 0;
    }
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        cnt[arr[i]]++;
        sum += arr[i];
    }
    ll ans = 0;
    ll pref = 0;
    ll cntr = 0;
    for(ll i = 0; i < MAX; i++){
        pref += cnt[i] * i;
        if(cnt[i] != 0){
            cntr += cnt[i];
            ans += (6 * cntr * i - 4 * pref + 4 * cntr) * cnt[i];
        }
    }
    for(ll a = 0; a < MAX; a++){
        if(cnt[a] == 0) continue;
        for(ll d: squares){
            ll b = (4 * a + 1 - d)/4;
            if(b < 0) break;
            if(cnt[b]){
                ll x = cnt[a] * cnt[b];
                ll delta = (2 * a + sqrt(d) + 1)/2 + 1;
                delta -= (6 * a - 4 * b + 4);
                ans += delta * x;
            }
        }
    }
    cout << ans << endl;
}
int main(){
    for(ll i = 1; i < MAX; i += 2){
        squares.push_back(i * i);
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
