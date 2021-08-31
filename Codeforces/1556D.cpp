#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
//vector<int> v = {1, 2, 5, 4, 5, 7};
pair<int,int> query1(int i, int j){
    //return make_pair(v[i] & v[j], v[i] | v[j]);
    cout << "and " << i + 1 << " " << j + 1<< endl;
    int x;
    cin >> x;
    cout << "or " << i + 1<< " " << j + 1 << endl;
    int y;
    cin >> y;
    return {x, y};
}
int convert(vector<bool> v){
    int ans = 0;
    for(int i = 0; i < v.size(); i++){
        ans += v[i] * pow(2, i);
    }
    return ans;
}
int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    int k;
    cin >> k;
    map<pair<int,int>, pair<int,int>> myMap;
    vector<vector<bool>> vec(n);
    vector<vector<bool>> fixed(n);
    for(int i = 0; i < n; i++){
        vec[i].resize(31);
        fixed[i].resize(vec[i].size());
        for(int j = 0; j < vec[i].size(); j++){
            fixed[i][j] = false;
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = i + 1; j < 3; j++){
            myMap[{i, j}] = myMap[{j, i}] = query1(i, j);
        }
    }
    vector<int> ans(n);
    int t= 2;
    while(t--){
    for(int i = 0; i < 3; i++){
        for(int j = i + 1; j < 3; j++){
            pair<int,int> p = myMap[{i, j}];
            for(int k = 0; k < vec[0].size(); k++){
                pair<bool,bool> q = make_pair(p.first & (1 << k), p.second & (1 << k));
                if((p.first & (1 << k)) == (p.second & (1 << k))){
                    vec[i][k] = vec[j][k] = q.first;
                    fixed[i][k] = fixed[j][k] = true;
                }
                if(fixed[i][k]){
                    if(vec[i][k]) vec[j][k] = q.first;
                    else vec[j][k] = q.second;
                    fixed[j][k] = true;
                }
                if(fixed[j][k]){
                    if(vec[j][k]) vec[i][k] = q.first;
                    else vec[i][k] = q.second;
                    fixed[i][k] = true;
                }
            }
        }
    }
    }
    ans[0] = convert(vec[0]);
    for(int i = 3; i < n; i++){
        pair<int,int> p = query1(i, 0);
        for(int k = 0; k < vec[i].size(); k++){
            pair<bool,bool> q = make_pair(p.first & (1 << k), p.second & (1 << k));
            if(ans[0] & (1 << k)){
                vec[i][k] = q.first;
                fixed[i][k] = true;
            }else{
                vec[i][k] = q.second;
                fixed[i][k] = true;
            }
        }
    }
    //cout << endl;
    for(int i = 0; i < n; i++){
        /*
        for(int j = 0; j < vec[i].size(); j++){
//            cout << vec[i][j] << " ";
        }
         */
//        cout << endl;
        ans[i] = convert(vec[i]);
        //cout << ans[i] << " ";
    }
    sort(ans.begin(), ans.end());
    cout << "finish " << ans[k - 1] << endl;
}
