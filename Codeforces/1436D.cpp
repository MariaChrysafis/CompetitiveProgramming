#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
#define ll long long
 
using namespace std;
void print(vector<long long> v){
    for(long long i: v) cout << i << ' ';
    cout << endl;
}
struct tree{
    vector<vector<long long>> adj;
    vector<long long> val;
    vector<long long> rng; // how many leaf nodes in subtree
    vector<long long> sm; // how much change we have
    long long n;
    long long des;
    void init_rng(){
        rng.resize(n);
        for(int i = 0; i < n; i++){
            rng[i] = -1;
        }
    }
    void init_sum(){
        sm.resize(n);
        for(int i = 0; i < n; i++){
            sm[i] = -1;
        }
    }
    long long dfs_for_rng(long long cur, long long prev){
        if(rng[cur] != -1) return rng[cur];
        if(adj[cur].size() == 1 && cur != 0) return rng[cur] = 1;
        long long ans = 0;
        for(int i: adj[cur]){
            if(i != prev) ans += dfs_for_rng(i, cur);
        }
        return rng[cur] = ans;
    }
    long long dfs_for_sm(long long cur, long long prev){
        if(sm[cur] != -1) return sm[cur];
        if(adj[cur].size() == 1 && cur != 0) return sm[cur] = val[cur];
        long long ans = val[cur];
        for(int i: adj[cur]){
            if(i != prev) ans += dfs_for_sm(i, cur);
        }
        return sm[cur] = ans;
    }
    bool pos(long long x){
        des = x;
        for(int i = 0; i < val.size(); i++){
            if(val[i] > des && adj[i].size() == 1){
                return false;
            }
        }
        for(int i = 0; i < n; i++){
            long long neededChange = des * rng[i] - sm[i] < 0;
            if(des == 0 && sm[i] == 0) continue;
            if((des == 0) || (sm[i] - 1)/des >= rng[i]){
                return false;
            }
        }
        return true;
    }
};
tree t;
long long binSearch(long long l, long long r){
    long long m = (l + r)/2;
    if(l == r){
        return l;
    }
    if(t.pos(m)){
        return binSearch(l, m);
    }else{
        return binSearch(m + 1, r);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t.n;
    t.adj.resize(t.n), t.val.resize(t.n);
    for(int i = 1; i < t.n; i++){
        long long x;
        cin >> x;
        x--;
        t.adj[i].push_back(x);
        t.adj[x].push_back(i);
    }
    for(int i = 0; i < t.n; i++){
        cin >> t.val[i];
    }
    t.init_rng();
    t.init_sum();
    t.dfs_for_rng(0, -1);
    t.dfs_for_sm(0, -1);
    cout << binSearch(0, 3e14);
}
