#include <iostream>
#include <vector>
#define ll long long
using namespace std;
ll max(ll a, ll b){
    if(a > b) return a;
    return b;
}
ll slv1(vector<ll> capacities, vector<ll> cnt, vector<ll> weight, int i){
    int ans = 0;
    if(i * weight[0] > capacities[0]){
        return -1;
    }
    cnt[0] -= i;
    capacities[0] -= i * weight[0];
    //give the first person some war axes
    ll wa1 = min(cnt[1], capacities[0]/weight[1]);
    cnt[1] -= wa1;
    capacities[0] -= weight[1] * wa1;
    //give the second person some shields
    ll wa2 = min(cnt[0], capacities[1]/weight[0]);
    cnt[0] -= wa2;
    capacities[1] -= wa2 * weight[0];
    //give the second person some war axes
    ll wa3 = min(cnt[1], capacities[1]/weight[1]);
    cnt[1] -= wa3;
    capacities[1] -= wa3 * weight[1];
    //cout << wa1 << " " << wa2 << " " << wa3 << " " << i << endl;
    ans = wa1 + wa2 + wa3 + i;
    return ans;
}
ll res(vector<ll> capacities, vector<ll> cnt, vector<ll> weight){
    ll ans = 0;
    for(int i = 0; i <= cnt[0]; i++){
        //give the first person i shields
        ans = max(ans, slv1(capacities, cnt, weight, i));
        //cout << cnt[0] << endl;
    }
    return ans;
}
int solve(){
    vector<ll> capacities(2);
    vector<ll> cnt(2);
    vector<ll> weight(2);
    cin >> capacities[0] >> capacities[1];
    cin >> cnt[0] >> cnt[1];
    cin >> weight[0] >> weight[1];
    if(weight[0] > weight[1]){
        swap(weight[0], weight[1]);
        swap(cnt[0], cnt[1]);
    }
    ll ans1 = res(capacities, cnt, weight);
    swap(capacities[0], capacities[1]);
    ll ans2 = res(capacities, cnt, weight);
    return max(ans1, ans2);
}
int main(){
    int t;
    cin >> t;
    while(t--){
        ll x = solve();
        cout << x << endl;
    }
}
