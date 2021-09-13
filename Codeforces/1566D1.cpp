#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iomanip>
#include <string>
#include <array>
#include <cassert>
#include <algorithm>
using namespace std;
bool comp(pair<int,int> p1, pair<int,int> p2){
    if(p1.first < p2.first) return true;
    else if(p1.first > p2.first) return false;
    return (p1.second > p2.second);
}
void solve(){
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<pair<int,int>> v(m);
    for(int i = 0; i < m; i++){
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end(), comp);
    vector<int> ans;
    map<int,int> oc;
    for(int i = 0; i < m; i++){
        ans.push_back(v[i].second);
        oc[v[i].second] = i;
        //cout << v[i].second << " ";
    }
    int cntr = 0;
    for(int i = 0; i < ans.size(); i++){
        for(int j = 0; j < ans.size(); j++){
            if (j < i && ans[j] < ans[i]){
                cntr++;
            }
        }
    }
    cout << cntr << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
