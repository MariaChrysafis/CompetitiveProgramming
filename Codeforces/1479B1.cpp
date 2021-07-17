#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
vector<int> read(int n){
    vector<int> v;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }
    return v;
}
int findBlocks(vector<int> v){
    vector<vector<int>> blocks;
    vector<int> cur;
    int prev = 0;
    for(int i = 0; i < v.size(); i++){
        int x = v[i];
        if(x == prev || i == 0){
            cur.push_back(x);
            prev = x;
        }else{
            blocks.push_back(cur);
            cur.clear();
            cur.push_back(x);
            prev = x;
        }
    }
    if(cur.size() != 0){
        blocks.push_back(cur);
    }
    return blocks.size();
}
void solve(int n) {
    vector<int> v = read(n);
    vector<int> left, right;
    int l = 0;
    int r = 0;
    for(int i = 0; i < v.size(); i++){
        int nxt;
        if(i == v.size() - 1){
            nxt = -1;
        }else{
            nxt = v[i + 1];
        }
        if(v[i] != l && v[i] == r){
            left.push_back(v[i]);
            l = v[i];
        }else if(v[i] != r && v[i] == l){
            right.push_back(v[i]);
            r = v[i];
        }else{
            if(l == nxt){
                left.push_back(v[i]);
                l = v[i];
            }else if(r == nxt){
                right.push_back(v[i]);
                r = v[i];
            }else{
                right.push_back(v[i]);
                r = v[i];
            }
        }
    }
    cout << findBlocks(left) + findBlocks(right) << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    solve(n);
}
