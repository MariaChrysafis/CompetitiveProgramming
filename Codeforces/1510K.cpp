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
vector<vector<int>> fill(int n, int m, int val){
    vector<vector<int>> v;
    v.resize(n);
    for(int i = 0; i < n; i++){
        v[i].resize(m);
        for(int j = 0; j < m; j++){
            v[i][j] = val;
        }
    }
    return v;
}
 
vector<int> move1(vector<int> v){
    for(int i = 0; i < v.size()/2; i++){
        swap(v[2 * i], v[2 * i + 1]);
    }
    return v;
}
 
vector<int> move2(vector<int> v){
    for(int i = 0; i < v.size()/2; i++){
        swap(v[i], v[i + v.size()/2]);
    }
    return v;
}
 
bool isIdentity(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        if(v[i] != i + 1){
            return false;
        }
    }
    return true;
}
 
const int INF = 1e9;
 
int ans(vector<int> v, int init){
    if(isIdentity(v)){
        return 0;
    }
    for(int i = 0; i < v.size(); i++){
        if(i % 2 == init){
            v = move1(v);
        }else{
            v = move2(v);
        }
        if(isIdentity(v)){
            return i + 1;
        }
    }
    return INF;
}
 
int main() {
    int n;
    cin >> n;
    vector<int> v(2 * n);
    for(int i = 0; i < 2 * n; i++){
        cin >> v[i];
    }
 
    int x = min(ans(v, 1), ans(v, 0));
    if(x == INF){
        cout << "-1\n";
    }else{
        cout << x << endl;
    }
}
