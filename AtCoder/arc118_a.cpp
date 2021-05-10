#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
#include <map>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long ll;
ll init = 0;
vector<ll> conv(vector<ll> v){
    ll myMax = v[v.size() - 1];
    ll x = 0;
    vector<ll> vec;
    for(ll i = 0; i < v.size(); i++){
        if(v[i] != x){
            if(init == 0) init =x;
            //cout << x << endl;
            vec.push_back(x);
            x++;
        }
        x++;
    }
    vector<ll> vec1;
    for(ll i = 0; i < vec.size() - 1; i++){
        vec1.push_back(vec[i + 1] - vec[i]);
    }
    //print(vec1);
    return vec1;
}
vector<ll> solve(ll t){
    vector<ll> v;
    for(ll A = 0; A < 100000; A++){
        v.push_back(A + A * t /100);
    }
    //print(v);
    vector<ll> v1 = conv(v);
    return v1;
}
vector<ll> rsz(ll sz, vector<ll> v){
    vector<ll> vec;
    for(ll i = 0; i < sz; i++){
        vec.push_back(v[i]);
    }
    return vec;
}
ll sm(vector<ll> v, ll x){
    ll sum = 0;
    for(ll i = 0; i < x; i++){
        sum += v[i];
    }
    return sum;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t, N;
    cin >> t >> N;
    vector<ll> v = rsz(t,solve(t));
    N--;
    ll ans = sm(v,v.size()) * floor(N/t) + sm(v,N % t) + init;
    cout << ans << endl;

}
