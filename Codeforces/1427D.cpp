#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
vector<int> increasing(vector<int> v){
    int cur = v[0]; int cntr = 0; vector<int> ans;
    for(int i = 0; i < v.size(); i++){
        if(v[i] >= cur) cntr++;
        else ans.push_back(cntr), cntr = 1;
        cur = v[i];
    }
    if(cntr != 0) ans.push_back(cntr);
    return ans;
}
vector<int> decreasing(vector<int> v){
    int cur = v[0]; int cntr = 0; vector<int> ans;
    for(int i = 0; i < v.size(); i++){
        if(v[i] <= cur) cntr++;
        else ans.push_back(cntr), cntr = 1;
        cur = v[i];
    }
    if(cntr != 0) ans.push_back(cntr);
    return ans;
}
vector<int> change(vector<int> v, vector<int> chng){
    vector<vector<int>> blocks;
    int last = 0;
    for(int i = 0; i < chng.size(); i++){
        vector<int> cur;
        for(int j = 0; j < chng[i]; j++){
            cur.push_back(v[last]);
            last++;
        }
        blocks.push_back(cur);
    }
    reverse(blocks.begin(), blocks.end());
    vector<int> ans;
    for(int i = 0; i < blocks.size(); i++){
        for(int j: blocks[i]){
            ans.push_back(j);
        }
    }
    return ans;
}
int main(){
    vector<int> perm = {3,6,1,7,4,5};
    vector<int> v = increasing(perm);
    change(perm, {2,2,2});
    int n;
    cin >> n;
    vector<int> inp(n);
    vector<int> identity(n);
    for(int i = 0; i < n; i++) identity[i] = i + 1;
    for(int i = 0; i < n; i++) cin >> inp[i];
    vector<vector<int>> ans;
    for(int i = 0; i < n; i++){
        if(inp == identity){
            break;
        }
        if(i % 2 == 0){
            vector<int> v1 = increasing(inp);
            ans.push_back({(int)v1.size()});
            ans.push_back(v1);
            inp = change(inp, v1);
        }else{
            vector<int> v1 = decreasing(inp);
            ans.push_back({(int)v1.size()});
            ans.push_back(v1);
            inp = change(inp, v1);
        }
        //print(inp);
    }
    cout << ans.size()/2 << endl;
    for(vector<int> v: ans){
        print(v);
    }
}
