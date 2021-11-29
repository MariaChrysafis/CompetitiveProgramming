#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <list>
#include <set>
#define ll long long
using namespace std;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    set<pair<int,int>> mySet;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
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
            cout << "NO\n";
            exit(0);
        }
        mySet.insert({x, y});
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int,int>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    sort(vec.begin(), vec.end());
    int ans = 0;
    set<pair<int,int>> s;
    dsu d;
    d.n = n;
    d.fill();
    for (int i = 0; i < vec.size(); i++) {
        auto it = s.upper_bound({vec[i].first, -1});
        for (auto itr = it; itr != s.end(); itr++) {
            if ((*itr).first <= vec[i].second) {
                d.join((*itr).second, i);
            } else {
                break;
            }
        }
        s.insert({vec[i].second, i});
    }
    if (d.compSize[d.find_head(0)] == n) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}
