#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << ' ';
    }
    cout << '\n';
}
set<int> convertToSet(vector<int> v){
    set<int> s;
    for(int i: v){
        s.insert(i);
    }
    return s;
}
const int INF = 2e9;
int solver(vector<int> cur, vector<int> des){
    des.push_back(INF);
    cur.push_back(INF);
    set<int> set_cur = convertToSet(cur);
    set<int> set_des = convertToSet(des);
    vector<int> suf(des.size());
    map<int,int> oc_cur;
    map<int,int> oc_des;
    for(int i = 0; i < cur.size(); i++){
        oc_cur[cur[i]] = i + 1;
    }
    for(int i = 0; i < des.size(); i++){
        oc_des[des[i]] = i + 1;
    }
    suf[des.size() - 1] = 0;
    int myMax = 0;
    for(int i = des.size() - 2; i >= 0; i--){
        suf[i] = suf[i + 1];
        suf[i] += set_cur.count(des[i]);
        myMax = max(myMax, suf[i]);
    }
    vector<int> boxes_before(des.size()); //how many boxes in cur occur before des[i]
    int ind = 0;
    for(int i = 0; i < des.size(); i++){
        int cntr = 0;
        for(int j = 0; j < cur.size(); j++){
            if(cur[j] < des[i]){
                cntr++;
            }
        }
        //cout << cntr << " ";
        boxes_before[i] = oc_cur[*set_cur.lower_bound(des[i])] - 1;
        //cout << boxes_before[i] << endl;
    }
    int curBoxes = 0;
    set<int> common;
    map<int,int> common_oc;
    for(int i: cur){
        if(oc_des[i]){
            common.insert(i);
        }
    }
    int sf = 1;
    for(auto it = common.begin(); it != common.end(); it++){
        common_oc[*it] = sf;
        sf++;
    }
    for(int i = 0; i < des.size() - 1; i++){
        curBoxes = boxes_before[i];
        curBoxes--;
        if(curBoxes < 0) continue;
        int l = des[i] - curBoxes;
        if(l < 0) l = 0;
        int r = des[i];
        int ans = oc_des[*set_des.upper_bound(r)] - oc_des[*set_des.upper_bound(l - 1)];
        int suffix = 0;
        if(common.upper_bound(r) == common.end()){
            suffix = 0;
        }else{
            suffix = common.size() - common_oc[*common.upper_bound(r)];
        }
        //cout << l << " " << r << " " << ans << " " << suffix << endl;
        myMax = max(myMax, ans + suffix);
    }
    return myMax;
}
void solve(){
    vector<int> pos_cur, neg_cur;
    vector<int> pos_des, neg_des;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        if(x > 0){
            pos_cur.push_back(x);
        }
        else{
            neg_cur.push_back(x);
        }
    }
    for(int i = 0; i < m; i++){
        int x;
        cin >> x;
        if(x > 0){
            pos_des.push_back(x);
        }else{
            neg_des.push_back(x);
        }
    }
    int ans = 0;
    for(int i = 0; i < neg_des.size(); i++) neg_des[i] = abs(neg_des[i]);
    for(int i = 0; i < neg_cur.size(); i++) neg_cur[i] = abs(neg_cur[i]);
    sort(neg_des.begin(), neg_des.end());
    sort(neg_cur.begin(), neg_cur.end());
    ans += solver(pos_cur, pos_des);
    ans += solver(neg_cur, neg_des);
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
 
}
