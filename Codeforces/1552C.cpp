#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
 
int distance(int i, int j, int n){
    return min(abs(i - j), 2 * n - abs(i - j));
}
 
bool intersects(pair<int,int> p1, pair<int,int> p2){
    if(p1.first == p2.first) return false;
    map<int,int> myMap;
    myMap[p1.first] = myMap[p1.second] = 1;
    myMap[p2.first] = myMap[p2.second] = 2;
    vector<int> v;
    v.push_back(p1.first), v.push_back(p1.second), v.push_back(p2.first), v.push_back(p2.second);
    sort(v.begin(), v.end());
    return (myMap[v[0]] != myMap[v[1]] && myMap[v[1]] == myMap[v[3]]);
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> v;
    bool marked[2 * n];
    for(int i = 0; i < 2 * n; i++) marked[i] = false;
    for(int i = 0; i < k; i++){
        int x, y;
        cin >> x >> y;
        x--, y--;
        v.push_back({x, y});
        marked[x] = marked[y] = true;
    }
    vector<int> todo;
    for(int i = 0; i < 2 * n; i++){
        if(!marked[i]){
            todo.push_back(i);
        }
    }
    sort(todo.begin(), todo.end());
    for(int i = 0; i < n - k; i++){
        v.push_back({todo[i], todo[i + n - k]});
    }
    //cout << intersects({0, 2}, {1, 3}) << endl;
    int ans = 0;
    for(pair<int,int> p: v){
        //cout << p.first << " " << p.second << endl;
        //continue;
        for(pair<int,int> q: v){
            ans += intersects(p, q);
        }
    }
    cout << ans/2 << endl;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
