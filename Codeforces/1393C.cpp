#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;
vector<int> arr;
int n;
map<int,int> oc;
bool valid(int x){
    set<pair<int,int>> s;
    for(pair<int,int> p: oc){
        s.insert({p.second, p.first});
    }
    vector<vector<pair<int,int>>> v(3 * n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < v[i].size(); j++){
            if(v[i][j].first > 0) s.insert({v[i][j].first, v[i][j].second});
        }
        if(s.empty()){
            return false;
        }
        pair<int,int> p = *s.rbegin();
        v[i + x + 1].push_back({p.first - 1, p.second});
        s.erase(p);
    }
    return true;
}
int binSearch(int l, int r){
    int m = (l + r)/2;
    if(l == r){
        return l;
    }
    if(!valid(m)){
        return binSearch(l, m);
    }else{
        return binSearch(m + 1, r);
    }
}
void solve(){
    cin >> n;
    arr.resize(n);
    oc.clear();
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        oc[arr[i]]++;
    }
    cout << binSearch(0, n + 1) - 1 << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
