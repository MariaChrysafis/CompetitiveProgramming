#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <map>
#define coord pair<ll,ll>
#define ll long long
#define x first
#define y second
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast")//Comment optimisations for interactive problems (use endl)
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
bool valid(vector<int> v, int x){
    int sum = 0;
    for(int i: v){
        sum += i;
        if(sum == x) return false;
    }
    return true;
}
vector<int> strt(vector<int> arr, int n, int x, int sp){
    vector<int> ans;
    ans.push_back(arr[sp]);
    bool marked[n];
    int sum = 0;
    sum += arr[sp];
    for(int i = 0; i < n; i++){
        marked[i] = false;
        marked[sp] = true;
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n; j++){
            if(marked[j]) continue;
            if(sum + arr[j] != x){
                sum += arr[j];
                marked[j] = true;
                ans.push_back(arr[j]);
                break;
            }
        }
    }
    return ans;
}
bool pq(ll x){
    ll sq = sqrt(x);
    return (sq * sq == x);
}
void solve(){
    ll n, m, x;
    cin >> n >> m >> x;
    vector<int> arr(n);
    multiset<pair<int,int>> s;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int ind[n];
    for(int i = 0; i < n; i++){
        if(s.size() < m){
            s.insert({arr[i],i});
            //cout << arr[i] << endl;
            ind[i] = i;
            continue;
        }
        auto prev = *std::min_element(s.begin(), s.begin());
        s.erase(s.find(prev));
        s.insert({prev.first + arr[i], prev.second});
        ind[i] = prev.second;
    }
    vector<int> v;
    int myMax = -pow(10,9);
    int myMin = pow(10,9);
    while(!s.empty()){
        pair<int,int> p = *s.begin();
        v.push_back(p.second);
        s.erase(s.find(*s.begin()));
        myMax = max(p.first,myMax);
        myMin = min(p.first, myMin);
    }
    //cout << myMax << " " << myMin << endl;
    if(myMax - myMin > x){
        cout << "NO" << endl;
        return;
    }
    map<int,vector<int>> myMap;
    for(int i = 0; i < n; i++){
        myMap[ind[i]].push_back(arr[i]);
    }
    cout << "YES" << endl;
    for(int i = 0; i < n; i++){
        cout << ind[i] + 1 << " ";
    }
    cout << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    //solve();
}
