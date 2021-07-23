#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <algorithm>
 
using namespace std;
 
void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
 
void print(vector<long long> v) {
    for (long long x: v) {
        cout << x << " ";
    }
    cout << endl;
}
 
void print(vector<char> v){
    for(char c: v) {
        cout << c << " ";
    }
    cout << endl;
}
 
void print(vector<vector<int>> v){
    for(vector<int> vec: v){
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<long long>> v){
    for(vector<long long> vec: v){
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<char>> v){
    for(vector<char> vec: v){
        print(vec);
    }
    cout << endl;
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> arr(n); //value followed by index
    for(int i = 0; i < n; i++){
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr.begin(), arr.end());
    map<int,vector<int>> oc;
    for(pair<int,int> p: arr) oc[p.first].push_back(p.second);
    vector<int> v;
    for(pair<int,vector<int>> p: oc){
        //value is p.first
        //p.first occurs at index
        for(int i = 0; i < min(k, (int)p.second.size()); i++){
            v.push_back(p.second[i]);
        }
        for(int i = 0; i < (int)p.second.size() - min(k, (int)p.second.size()); i++){
            v.push_back(-1);
        }
    }
    //print(v);
    vector<int> ans(v.size());
    for(int i = 0; i < v.size(); i++) ans[i] = 0;
    map<int,int> oc1;
    int cntr = 1;
    for(int i = 0; i < v.size(); i++){
        if(v[i] == -1) continue;
        ans[v[i]] = cntr;
        cntr %= k;
        cntr++;
    }
    for(int i: ans){
        oc1[i]++;
    }
    int myMin = 1e9;
    //print(ans);
    for(int i = 1; i <= k; i++){
        myMin = min(myMin, oc1[i]);
    }
    //cout << myMin << endl;
    for(int i = 0; i < v.size(); i++){
        if(ans[i] == 0) continue;
        if(oc1[ans[i]] > myMin){
            oc1[ans[i]]--;
            ans[i] = 0;
        }
    }
    print(ans);
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
