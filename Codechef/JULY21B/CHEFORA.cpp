#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <stack>
#define ll long long
using namespace std;
const ll MOD = 1e9 + 7;
vector<ll> ans;
ll cl(ll x){
    ll pwr = 1;
    while(pwr < x){
        pwr *= 2;
    }
    return pwr;
}
pair<ll,ll> merge(pair<ll,ll> p1, pair<ll,ll> p2){
    return make_pair(p1.first,p2.second);
}
struct segmentTree{
    vector<pair<ll,ll>> vec;
    vector<ll> v;
    vector<ll> arr;
    ll INF;
    ll build(ll ind){
        if(ind >= v.size() - 1){
            arr[ind] = v[ind - (v.size() - 1)];
            return arr[ind];
        }
        arr[ind] = (build(2 * ind + 1) + build(2 * ind + 2));
        return arr[ind];
    }
    pair<ll,ll> build2(ll ind){
        if(ind >= v.size() - 1){
            int x = ind - (v.size() - 1);
            vec[ind] = make_pair(x,x);
            return vec[ind];
        }
        vec[ind] = merge(build2(2 * ind + 1),build2(2 * ind + 2));
        return vec[ind];
    }
    ll interval(ll i, ll L, ll R){
        if(vec[i].first > R || vec[i].second < L){
            return INF;
        }
        if(vec[i].first >= L && vec[i].second <= R){
            return arr[i];
        }
        ll a = interval(2 * i + 1,L,R);
        ll b = interval(2 * i + 2,L,R);
        return (a + b);
    }
};
segmentTree generate(vector<ll> v){
    segmentTree st;
    st.v = v;
    vector<ll> arr(2 * cl(v.size()));
    vector<pair<ll,ll>> vec(2 * cl(v.size()));
    st.arr = arr, st.vec = vec;
    vector<ll> v1;
    v1.resize(cl(v.size()));
    for(int i = 0; i < v.size(); i++){
        v1[i] = v[i];
    }
    st.v = v1;
    st.build(0);
    st.build2(0);
    st.INF = 0;
    return st;
}
ll binPow(ll a, ll b){
    ll ansr = 1;
    ll res = a;
    while(b > 0){
        if(b & 1){
            ansr = (ansr * res) % MOD;
        }
        b /= 2;
        res = (res * res) % MOD;
    }
    return ansr;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(ll i = 1; i <= 9; i++){
        ans.push_back(i);
    }
    for(ll i = 1; i <= 9; i++){
        for(int j = 0; j <= 9; j++){
            ans.push_back(100ll * i + 10ll * j + i);
        }
    }
    for(ll i = 1; i <= 9; i++){
        for(ll j = 0; j <= 9; j++){
            for(ll k = 0; k <= 9; k++){
                ans.push_back(10000ll * i + 1000ll * j + 100ll * k + 10ll * j + i);
            }
        }
    }
    for(ll i = 1; i <= 9; i++){
        for(ll j = 0; j <= 9; j++){
            for(ll k = 0; k <= 9; k++){
                for(ll l = 0; l <= 9; l++) {
                    ans.push_back(1000000ll * i + 100000ll * j + 10000ll * k + 1000ll * l +
                                  100ll * k + 10ll * j + i);
                }
            }
        }
    }
    for(ll i = 1; i <= 9; i++){
        for(ll j = 0; j <= 9; j++){
            for(ll k = 0; k <= 9; k++){
                for(ll l = 0; l <= 9; l++) {
                    for(ll m = 0; m <= 9; m++) {
                        ans.push_back(100000000ll * i + 10000000ll * j + 1000000ll * k + 100000ll * l
                                      + 10000ll * m + 1000ll * l + 100ll * k + 10ll * j + i);
                    }
                }
            }
        }
    }
    for(ll i = 1; i <= 9; i++){
        for(ll j = 0; j <= 9; j++){
            for(ll k = 0; k <= 9; k++){
                for(ll l = 0; l <= 9; l++) {
                    for(ll m = 0; m <= 9; m++) {
                        for(ll q = 0; q <= 9; q++) {
                            ans.push_back(
                                    10000000000ll * i + 1000000000ll * j + 100000000ll * k + 10000000ll * l + 1000000ll * m + 100000ll * q +
                                    10000ll * m + 1000ll * l + 100ll * k + 10ll * j + i);
                        }
                    }
                }
            }
        }
    }
    segmentTree st = generate(ans);
    ll q;
    cin >> q;
    while(q--){
        ll l, r;
        cin >> l >> r;
        r--;
        //cout << ans[l - 1] << " " << st.interval(0, l, r) << endl;
        cout << binPow(ans[l - 1], st.interval(0, l, r) )<< endl;
    }
}
