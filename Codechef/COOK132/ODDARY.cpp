#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

#define ll long long
using namespace std;
#define P(x, y) make_pair(x,y)
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
vector<vector<int>> pos;
void solve(){
    int n;
    cin >> n;
    vector<int> best;
    for(vector<int> v: pos){
        if(v.size() >= n){
            best = v;
            break;
        }
    }
    for(int i = 0; i < n; i++) cout << best[i] << " ";
    cout << endl;
}
int main() {
    vector<int> cur = {1};
    while(pos.size() == 0 || pos.back().size() <= 1000){
        pos.push_back(cur);
        vector<int> new_cur;
        for(int i = 0; i < cur.size(); i++){
            new_cur.push_back(cur[i]);
        }
        new_cur.push_back(pos.size() + 1);
        for(int i = 0; i < cur.size(); i++){
            new_cur.push_back(cur[i]);
        }
        cur = new_cur;
        //print(cur);
    }
    int t;
    cin >> t;
    while(t--) solve();
}
