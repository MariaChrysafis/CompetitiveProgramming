#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;
vector<bool> isPrime;
void print(vector<ll> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
ll cl(ll x){
    ll pwr = 1;
    while(pwr < x){
        pwr *= 2;
    }
    return pwr;
}
pair<int,int> merge(pair<int,int> p1, pair<int,int> p2){
    return make_pair(p1.first,p2.second);
}
struct segmentTree{
    vector<pair<ll,ll>> vec;
    vector<ll> v;
    vector<ll> arr;
    ll INF;
    ll build(int ind){
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
    void update(ll k, ll u){
        ll ind = (v.size() - 1) + k;
        arr[ind] = u;
        while(ind != 0){
            int parent = (ind - 1)/2;
            arr[parent] = max(arr[parent * 2 + 1],arr[parent * 2 + 2]);
            ind = parent;
        }
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
    st.INF = -LLONG_MAX;
    return st;
}
vector<ll> identity(int n){
    vector<ll> v;
    for(int i = 0; i < n; i++){
        v.push_back(-LLONG_MAX);
    }
    return v;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> v = identity(n);
    vector<ll> dp(n);
    vector<ll> height(n), beauty(n);
    for(int i = 0; i < height.size(); i++){
        cin >> height[i];
    }
    for(int i = 0; i < beauty.size(); i++){
        cin >> beauty[i];
    }
    segmentTree st = generate(identity(n));
    stack<int> s;
    s.push(0);
    dp[0] = beauty[0];
    st.update(0, dp[0]);
    for(int i = 1; i < n; i++){
        while(!s.empty() && height[s.top()] >= height[i]){
            s.pop();
        }
        if(s.empty()){
            dp[i] = max(st.interval(0, 0, i - 1), 0ll) + beauty[i];
        }else{
            dp[i] = max(dp[s.top()], st.interval(0, s.top(), i - 1) + beauty[i]);
        }
        s.push(i);
        st.update(i, dp[i]);
    }
    cout << dp.back() << endl;
}
