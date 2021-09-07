#include <iostream>
#include <vector>
#include <map>
#define ll long long
using namespace std;
map<pair<ll,ll>, ll> oc;
map<ll,ll> dif;
map<ll,ll> sm;
map<ll,ll> x,y;
ll cost(ll X, ll Y){
    return sm[X + Y] + dif[X - Y] + x[X] + y[Y] - 2 * oc[{X, Y}];
}
void solve(){
    oc.clear();
    dif.clear();
    sm.clear();
    x.clear();
    y.clear();
    ll n;
    cin >> n;
    vector<pair<ll,ll>> coords(n);
    for(int i = 0; i < n; i++){
        cin >> coords[i].first;
        coords[i].first *= 2;
    }
    for(int i = 0; i < n; i++){
        cin >> coords[i].second;
        coords[i].second *= 2;
    }
    for(pair<ll,ll> p: coords){
        dif[p.first - p.second]++;
        sm[p.first + p.second]++;
        x[p.first]++;
        y[p.second]++;
        oc[p]++;
    }
    vector<pair<ll,ll>> v;
    for(pair<ll,ll> d: dif){
        for(pair<ll,ll> s: sm){
            ll X = (d.first + s.first)/2;
            ll Y = (-d.first + s.first)/2;
            v.push_back({X, Y});
        }
        for(pair<ll,ll> px: x){
            ll X = px.first;
            ll Y = px.first - d.first;
            v.push_back({X, Y});
        }
        for(pair<ll,ll> py: y){
            ll X = d.first + py.first;
            ll Y = py.first;
            v.push_back({X, Y});
        }
    }
    for(pair<ll,ll> s: sm){
        for(pair<ll,ll> px: x){
            ll X = px.first;
            ll Y = s.first - X;
            v.push_back({X, Y});
        }
        for(pair<ll,ll> py: y){
            ll X = s.first - py.first;
            ll Y = py.first;
            v.push_back({X, Y});
        }
    }
    for(pair<ll,ll> p1: x){
        for(pair<ll,ll> p2: y){
            v.push_back({p1.first, p2.first});
        }
    }
    ll myMax = 2;
    for(pair<ll,ll> p: v){
        myMax = max(myMax, cost(p.first, p.second));
    }
    cout << 2 * n - myMax << '\n';
}
int main(){
    int T;
    cin >> T;
    while(T--){
        solve();
    }
}
