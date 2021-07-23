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
    string s;
    cin >> s;
    map<char,int> oc;
    for(char c: s) oc[c]++;
    int red = 0;
    int green = 0;
    for(pair<char,int> p: oc){
        if(p.second >= 2){
            red++, green++;
        }else if(p.second == 1){
            if(red >= green) green++;
            else red++;
        }
    }
    cout << red << endl;
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
