#include <iostream>
#include <set>
#include <vector>
using namespace std;
int GCD(int a, int b){
    if(min(a,b) == -1) return -1;
    if(min(a,b) == 0) return max(a,b);
    return GCD(max(a,b) % min(a,b), min(a,b));
}
void solve(){
    int n;
    cin >> n;
    int v[n];
    int nxt[n];
    set<pair<int,int>> s;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        nxt[i] = (i + 1) % n;
    }
    for(int i = 0; i < n; i++){
        if(GCD(v[i], v[(i + 1) % n]) == 1){
            s.insert({i, (i + 1) % n});
        }
    }
    vector<int> ans;
    for(int i = 0; i < n; i++){
        bool change = false;
        vector<std::set<pair<int,int>>::iterator>vec;
        vector<pair<int,int>> vec1;
        for(auto it = s.begin(); it != s.end(); it++){
            auto x = *it;
            if(nxt[x.first] == -1 || nxt[x.second] == -1){
                vec.push_back(it);
                continue;
            }
            nxt[x.first] = nxt[x.second];
            if(GCD(v[x.first],v[nxt[x.second]]) == 1){
                change = true;
                vec1.push_back({x.first,nxt[x.second]});
            }
            nxt[x.second] = -1, ans.push_back(x.second);
            vec.push_back(it);
        }
        if(!change) break;
        for(auto it: vec) s.erase(*it);
        for(auto it: vec1) s.insert(it);
    }
    cout << ans.size() << " ";
    for(int i: ans){
        cout << i + 1 << " ";
    }
    cout << endl;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
