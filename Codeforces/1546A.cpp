#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
const int MAX = 2e5 + 7;
void solve(){
    set<pair<int,int>> s;
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) cin >> v[i].first;
    for(int i = 0; i < n; i++) cin >> v[i].second;
    vector<pair<int,int>> v1, v2;
    vector<int> ind1, ind2;
    int x = 0;
    for(int i = 0; i < v.size(); i++){
        pair<int,int> p = v[i];
        if(p.first < p.second){
            v1.push_back(p);
            ind1.push_back(i);
        }else if(p.first > p.second){
            v2.push_back(p);
            ind2.push_back(i);
        }
        x += p.first - p.second;
    }
    if(x != 0){
        cout << -1 << endl;
        return;
    }
    int i1, i2;
    i1 = i2 = 0;
    vector<pair<int,int>> ans;
    while(i1 < v1.size() && i2 < v2.size()){
        if(v1[i1].first == v1[i1].second){
            i1++;
        }
        if(v2[i2].first == v2[i2].second){
            i2++;
        }
        if(i1 < v1.size() && i2 < v2.size()) {
            v1[i1].first++;
            v2[i2].first--;
            ans.push_back({ind1[i1], ind2[i2]});
        }
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].second + 1 << " " << ans[i].first + 1 << endl;
    }
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
