#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int cc;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        cc = n;
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        cc--;
    }
};
int dist (pair<int,int> p1, pair<int,int> p2) {
    return abs(p1.first - p2.first) * abs(p1.first - p2.first) + abs(p1.second - p2.second) * abs(p1.second - p2.second);
}
int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    dsu d;
    int N;
    cin >> N;
    d.n = N;
    d.fill();
    vector<pair<int,int>> vec(N);
    vector<vector<pair<int,int>>> v;
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    set<int> s;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            s.insert(dist(vec[i], vec[j]));
        }
    }
    int cntr = 0;
    map<int,int> myMap;
    vector<int> rev;
    for (int i: s) {
        myMap[i] = cntr++;
        rev.push_back(i);
    }
    v.resize(cntr);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            v[myMap[dist(vec[i], vec[j])]].push_back({i, j});
        }
    }
    for (int i = 0; i < v.size(); i++) {
        for (pair<int,int> pr: v[i]) {
            d.join(pr.first, pr.second);
        }
        if (d.cc == 1) {
            cout << rev[i] << '\n';
            return 0;
        }
    }
}
