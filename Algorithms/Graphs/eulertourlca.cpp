#include <iostream>
#include <queue>
using namespace std;
int cl(int x){
  int pwr = 1;
  while(pwr < x){
    pwr *= 2;
  }
  return pwr;
}
pair<int,int> merge(pair<int,int> p1, pair<int,int> p2){
  return make_pair(p1.first,p2.second);
}
struct segmentTree{
  vector<pair<int,int>> vec;
  vector<int> v;
  vector<int> arr;
  int INF;
  int build(int ind){
    if(ind >= v.size() - 1){
      arr[ind] = v[ind - (v.size() - 1)];
      return arr[ind];
    }
    arr[ind] = min(build(2 * ind + 1),build(2 * ind + 2));
    return arr[ind];
  }
  pair<int,int> build2(int ind){
    if(ind >= v.size() - 1){
      int x = ind - (v.size() - 1);
      vec[ind] = make_pair(x,x);
      return vec[ind];
    }
    vec[ind] = merge(build2(2 * ind + 1),build2(2 * ind + 2));
    return vec[ind];
  }
  int interval(int i, int L, int R){
    if(vec[i].first > R || vec[i].second < L){
      return INF;
    }
    if(vec[i].first >= L && vec[i].second <= R){
      return arr[i];
    }
    int a = interval(2 * i + 1,L,R);
    int b = interval(2 * i + 2,L,R);
    return min(a,b);
  }
  void update(int k, int u){
    int ind = (v.size() - 1) + k;
    arr[ind] = u;
    while(ind != 0){
      int parent = (ind - 1)/2;
      arr[parent] = min(arr[parent * 2 + 1],arr[parent * 2 + 2]);
      ind = parent;
    }
  }
};
struct tree{
    vector<vector<int>> adj;
    vector<int> euler, first;
    int counter = 0;
    segmentTree st;
    void pre_euler(){
        //euler.resize(adj.size());
        first.resize(adj.size());
        dfs(0, -1, 0);
        int n = euler.size();
        st.arr.resize(2 * cl(n));
        st.vec.resize(2 * cl(n));
        st.v.resize(cl(n));
        for(int i = 0;i < n; i++) st.v[i] = euler[i];
        st.build(0);
        st.build2(0);
        st.INF = 1e9;
        //cout << st.interval(0,2,3) << endl;
     }
    void dfs(int node, int parent, int h){
        euler.push_back(node);
        first[node] = euler.size();
        euler.push_back(node);
        for(int i: adj[node]){
            if(i != parent){
                dfs(i, node, h + 1);
                euler.push_back(node);
            }
        }
    }
    int lca(int u, int v){
        int left = first[u];
        int right = first[v];
        if(left > right) swap(left, right);
        return st.interval(0,left,right);
    }
};
int main(){
    tree t;
    int n;
    cin >> n;
    int q;
    cin >> q;
    t.adj.resize(n);
    for(int i = 1; i < n; i++){
        int u;
        cin >> u;
        t.adj[i].push_back(u);
        t.adj[u].push_back(i);
    }
    t.pre_euler();
    while(q--){
        int u, v;
        cin >> u >> v;
        cout << t.lca(u,v) << endl;
    }
}
