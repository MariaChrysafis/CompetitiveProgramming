#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>

#define ll long long

using namespace std;
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
    int INF = 0;
    int build(int ind){
        if(ind >= v.size() - 1){
            arr[ind] = v[ind - (v.size() - 1)];
            return arr[ind];
        }
        arr[ind] = max(build(2 * ind + 1),build(2 * ind + 2));
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
        return max(a,b);
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
    return st;
}
vector<pair<ll,ll>> v;
ll firstOc(ll l, ll r, ll cost){
    if(l == r){
        if(v[l].first > cost){
            return -1;
        }
        return l;
    }
    ll m = (l + r + 1)/2;
    if(v[m].first <= cost){
        return firstOc(m, r, cost);
    }else{
        return firstOc(l, m - 1, cost);
    }
}
void solve(){
    vector<ll> cost, sweetness;
    ll n, d;
    cin >> n >> d;
    v.resize(n);
    map<ll,ll> oc;
    vector<ll> a;
    ll myMax = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i].first;
    }
    for(int i = 0; i < n; i++){
        cin >> v[i].second;
        if(v[i].first <= d){
            myMax = max(myMax, v[i].second);
        }
    }
    sort(v.begin(), v.end()); //sort by cost
    for(int i = 0; i < v.size(); i++){
        a.push_back(v[i].second);
    }
    segmentTree st = generate(a);
    for(int i = 0; i < n; i++){
        ll y = firstOc(0, v.size() - 1, d - v[i].first);
        if(y == -1) continue;
        ll ans;
        if(i < y) ans = max(st.interval(0, 0, i - 1), st.interval(0, i + 1, y)); //i < y
        else if(i == y) ans =  st.interval(0, 0, i - 1); //i = y
        else ans = st.interval(0, 0, y); // i > y
        myMax = max(ans + v[i].second, myMax);
    }
    cout << myMax << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
