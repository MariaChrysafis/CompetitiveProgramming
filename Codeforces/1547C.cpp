#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;
//long long
string yesNo(bool b){
    if(b) return "Yes";
    else return "No";
}
pair<int,int> read(){
    int a, b;
    cin >> a >> b;
    return {a, b};
}
vector<int> merge(vector<int> a, vector<int> b){
    vector<int> v;
    for(int i = 0; i < a.size(); i++){
        v.push_back(a[i]);
    }
    for(int i= 0; i < b.size(); i++){
        v.push_back(b[i]);
    }
    return v;
}
vector<vector<int>> convert(vector<int> v){
    int cur;
    if(v[0] == 0) cur = 0;
    else cur = 1;
    vector<vector<int>> ans;
    vector<int> soFar;
    for(int i = 0; i < v.size(); i++){
        if((v[i] != 0) == cur){
            soFar.push_back(v[i]);
        }else{
            ans.push_back(soFar);
            soFar.clear();
            soFar.push_back(v[i]);
            cur = (v[i] != 0);
        }
    }
    if(soFar.size() != 0) ans.push_back(soFar);
    vector<vector<int>> ans1;
    for(int i = 0; i < ans.size() - 1; i += 2){
        ans1.push_back(merge(ans[i], ans[i + 1]));
    }
    if(ans.size() % 2 == 1){
        ans1.push_back(ans[ans.size() - 1]);
    }
    return ans1;
}
void solve(){
    int k, n, m;
    cin >> k >> n >> m;
    vector<int> vec[2];
    vec[0].resize(n);
    vec[1].resize(m);
    for(int i = 0; i < n; i++) cin >> vec[0][i];
    for(int i = 0; i < m; i++) cin >> vec[1][i];
    /*
    vector<vector<int>> v[2];
    v[0] = convert(vec1);
    v[1] = convert(vec2);
    vector<int> cost[2];
    cost[0].resize(v[0].size());
    cost[1].resize(v[1].size());
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < v[i].size(); j++){
            int cntr = 0;
            for(int k = 0; k < v[i][j].size(); k++){
                if(v[i][j][k] == 0) cntr++;
            }
            cost[i][j] = cntr;
        }
    }
     */
    int ind[2];
    vector<int> ans;
    ind[0] = 0, ind[1] = 0;
    while(ind[0] < n || ind[1] < m){
        if(ind[0] >= n){
            ans.push_back(vec[1][ind[1]]);
            ind[1]++;
        }else if(ind[1] >= m) {
            ans.push_back(vec[0][ind[0]]);
            ind[0]++;
        }else{
            if(vec[1][ind[1]] < vec[0][ind[0]]){
                ans.push_back(vec[1][ind[1]]);
                ind[1]++;
            }else{
                ans.push_back(vec[0][ind[0]]);
                ind[0]++;
            }
        }
    }
    for(int i: ans){
        //cout << i << " ";
        if(i == 0) k++;
        else if(i > k){
            cout << -1 << endl;
            return;
        }
    }
    for(int i: ans){
        cout << i << " ";
    }
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
