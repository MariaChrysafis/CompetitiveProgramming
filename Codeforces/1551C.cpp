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
 
vector<string> v;
bool comp(pair<int,int> p1, pair<int,int> p2){
    return (p1.first - 2 * p1.second < p2.first - 2 * p2.second);
}
 
void solve() {
    int n;
    cin >> n;
    v.resize(n);
    vector<vector<int>> oc(n);
    for(int i = 0; i < n; i++){
        oc[i].resize(5);
        cin >> v[i];
        for(int j = 0; j < v[i].length(); j++){
            oc[i][v[i][j] - 'a']++;
        }
    }
    int myMax = 0;
    for(char c = 'a'; c <= 'e'; c++){
        bool taken[n];
        for(int i = 0; i < n; i++){
            taken[i] = false;
        }
        vector<pair<int,int>> vec;
        for(int i = 0; i < n; i++){
            vec.push_back({v[i].size(), oc[i][c - 'a']});
        }
        sort(vec.begin(), vec.end(), comp);
        int cntr = 0;
        int len = 0;
        int ans = 0;
        for(int i = 0; i < vec.size(); i++){
            if((cntr + vec[i].second) * 2 <= len + vec[i].first){
                break;
            }
            len += vec[i].first;
            cntr += vec[i].second;
            ans++;
        }
        myMax = max(myMax, ans);
    }
    cout << myMax << endl;
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
