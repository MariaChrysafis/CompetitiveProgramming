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
    vector<pair<int,int>> v(m * n);
    map<int,vector<int>> myMap;
    for(int i = 0; i < m * n; i++){
        cin >> v[i].first;
        myMap[v[i].first].push_back(i);
        v[i].second = i;
    }

    for(pair<int,vector<int>> p: myMap){
        reverse(myMap[p.first].begin(), myMap[p.first].end());
    }

    sort(v.begin(), v.end(), comp);
    int x = 0;
    int y = 0;
    int arr[n][m];
    for(int i = 0; i < v.size(); i++){
        arr[x][y] = v[i].first;
        y++;
        if(y == m){
            y = 0;
            x++;
        }
    }
    bool taken[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            taken[i][j] = false;
        }
    }
    map<int,int> firstRowSeen;
    for(pair<int,int> p: v) firstRowSeen[p.first] = -1;
    for(int i = 0; i < n; i++){
        set<int> s;
        for(int j = 0; j < m; j++){
            s.insert(arr[i][j]);
        }
        if(s.size() != 1){
            for(int j = m - 1; j >= 0; j--){
                if(firstRowSeen[arr[i][j]] == -1){
                    int x = arr[i][j];
                    arr[i][j] = myMap[arr[i][j]].back();
                    myMap[x].pop_back();
                    taken[i][j] = true;
                }
            }
        }
        for(int x: s){
            firstRowSeen[x] = i;
        }
    }
    firstRowSeen.clear();
    for(pair<int,vector<int>> p: myMap){
        reverse(myMap[p.first].begin(), myMap[p.first].end());
    }
    for(int i = 0; i < n; i++){
        set<int> s;
        for(int j = 0; j < m; j++){
            s.insert(arr[i][j]);
        }
        if(s.size() != 1){
            for(int j = 0; j < m; j++){
                if(!taken[i][j] && firstRowSeen[arr[i][j]] != -1){
                    int x = arr[i][j];
                    arr[i][j] = myMap[arr[i][j]].back();
                    myMap[x].pop_back();
                    taken[i][j] = true;
                }
            }
        }
        for(int x: s){
            firstRowSeen[x] = i;
        }
    }
    for(pair<int,vector<int>> p: myMap){
        reverse(myMap[p.first].begin(), myMap[p.first].end());
    }
    for(int j = m - 1; j >= 0; j--){
        for(int i = 0; i < n; i++){
            if(taken[i][j]) continue;
            int x = arr[i][j];
            arr[i][j] = myMap[x].back();
            myMap[x].pop_back();
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        vector<int> v;
        for(int j = 0; j < m; j++){
            v.push_back(arr[i][j]);
        }
        for(int j = 0; j < v.size(); j++){
            for(int k = 0; k < v.size(); k++){
                if(j < k && v[j] < v[k]){
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
