#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;

struct dsu{
    vector<int> parent;
    vector<int> compSize;
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
            return;
        }
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
    int n, d;
    cin >> n >> d;
    dsu myDsu;
    myDsu.n = n;
    myDsu.fill();
    int extra = 0;
    int myMax = 1;
    while(d--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (myDsu.comp(u, v)) {
            extra++;
        } else {
            myDsu.join(u, v);
            myMax = max(myMax, myDsu.compSize[myDsu.find_head(u)]);
        }
        vector<int> components;
        for (int i = 0; i < n; i++) {
            if (myDsu.find_head(i) == i) {
                components.push_back(myDsu.compSize[i]);
            }
        }
        sort(components.begin(), components.end());
        reverse(components.begin(), components.end());
        int ans = 0;
        for (int i = 0; i <= min(extra, (int)components.size() - 1); i++) {
            ans += components[i];
        }
        cout << ans - 1 << '\n';
    }
}
