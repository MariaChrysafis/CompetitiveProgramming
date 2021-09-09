#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
 
using namespace std;
vector<ll> v;
vector<ll> mountain, valley;
ll mountain_sum = 0;
ll valley_sum = 0;
template <typename T>
void print(vector<T> v){
    for(T x: v){
        cout << x << " ";
    }
    cout << endl;
}
void update(ll x, ll y){
    //update x to have value y
    bool prevM = mountain[x];
    bool prevV = valley[x];
    v[x] = y;
    for(ll i = max(x - 1, 0ll); i <= min(x + 1, (ll)v.size() - 1); i++){
        bool isNowMountain;
        if(i >= 1 && i <= v.size() - 2) isNowMountain = (v[i] > v[i - 1] && v[i] > v[i + 1]);
        else if(i == 0) isNowMountain = (v[0] > v[1]);
        else if (i == v.size() - 1) isNowMountain = (v.back() > v[v.size() - 2]);
        if(isNowMountain && !mountain[i]){
            mountain[i] = v[i], mountain_sum += v[i];
        }
        if(!isNowMountain && mountain[i]){
            mountain_sum -= mountain[i], mountain[i] = 0;
        }
        bool isNowValley = false;
        if(i >= 1 && i <= v.size() - 2) isNowValley = (v[i] < v[i - 1] && v[i] < v[i + 1]);
        if(isNowValley && !valley[i]){
            valley[i] = v[i], valley_sum += v[i];
        }
        if(!isNowValley && valley[i]){
            valley_sum -= valley[i], valley[i] = 0;
        }
    }
    if(prevV && valley[x]){
        valley_sum += v[x] - valley[x], valley[x] = v[x];
    }
    if(prevM && mountain[x]){
        mountain_sum += v[x] - mountain[x], mountain[x] = v[x];
    }
}
void solve(){
    mountain_sum = valley_sum = 0;
    mountain.clear(), valley.clear(), v.clear();
    long long N, Q;
    cin >> N >> Q;
    v.resize(N), mountain.resize(N), valley.resize(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
        mountain[i] = false;
        valley[i] = false;
    }
    for(int i = 0; i < N; i++){
        update(i, v[i]);
    }
    if(N == 1){
        cout << v[0] << endl;
        while(Q--){
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << v[l] << endl;
        }
        return;
    }
    cout << mountain_sum - valley_sum << '\n';
    while(Q--){
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int prevL = v[l];
        int prevR = v[r];
        update(l, prevR);
        update(r, prevL);
        cout << mountain_sum - valley_sum << '\n';
    }
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
