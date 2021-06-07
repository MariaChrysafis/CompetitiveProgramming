#include <iostream>
#include <vector>
using namespace std;
void print(bool b){
    if(b) cout << "YES" << endl;
    else cout << "NO" << endl;
}
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
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    dsu g;
    g.n = n;
    g.fill();
    while(q--){
        string s;
        int u, v;
        cin >> s >> u >> v;
        u--, v--;
        if(s == "union"){
            g.join(u, v);
        }else{
            print(g.comp(u, v));
        }
    }
}
