#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
 
vector<int> read(int n) {
    vector<int> v;
    v.push_back(0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    return v;
}
 
void print(vector<int> vec){
    for(int i: vec){
        cout << i << " ";
    }
    cout << endl;
}
 
int findBlocks(vector<int> v) {
    vector<vector<int>> blocks;
    vector<int> cur;
    int prev = 0;
    for (int i = 0; i < v.size(); i++) {
        int x = v[i];
        if (x == prev || i == 0) {
            cur.push_back(x);
            prev = x;
        } else {
            blocks.push_back(cur);
            cur.clear();
            cur.push_back(x);
            prev = x;
        }
    }
    if (cur.size() != 0) {
        blocks.push_back(cur);
    }
    return blocks.size();
}
 
void solve(int n) {
    vector<int> v = read(n);
    //print(v);
    vector<int> left, right;
    map<int,vector<int>> myMap;
    map<int,int> nxt;
    map<int,int> pos;
    for(int i = 0; i < v.size(); i++){
        myMap[v[i]].push_back(i);
    }
    for(int i = 0; i <= n; i++){
        pos[i] = n + 1;
    }
    for(int i = n; i >= 0; i--){
        nxt[i] = pos[v[i]];
        pos[v[i]] = i;
    }
    int li = 0;
    int ri = 0;
    for (int i = 1; i < v.size(); i++) {
        if (v[i] == v[ri]) {
            right.push_back(v[i]);
            ri = i;
        } else if (v[i] == v[li]) {
            left.push_back(v[i]);
            li = i;
        } else {
            if(nxt[li] <= nxt[ri]){
                right.push_back(v[i]);
                ri = i;
            }else{
                left.push_back(v[i]);
                li = i;
            }
        }
    }
    //print(left), print(right);
    cout << findBlocks(left) + findBlocks(right) << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    solve(n);
}
