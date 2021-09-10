#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
 
using namespace std;
template<class T> struct segMin { // comb(ID,b) = b
    const T ID = 1e9; T comb(T a, T b) { return min(a,b); }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
 
struct Query{
    int left;
    int right;
    int isVal;
    int ind;
};
 
bool comp(Query p1, Query p2){
    if(p1.right == p2.right){
        return (p1.left < p2.left);
    }
    return (p1.right < p2.right);
}
 
vector<bool> answer_queries(vector<int> v, vector<Query> queries){
    vector<bool> ans(queries.size());
    sort(queries.begin(), queries.end(), comp);
    segMin<int> st;
    st.init(v.size() + 3);
    for(int i = 1; i <= v.size(); i++){
        st.upd(i, -1);
    }
    int prev = -1;
    for(int i = 0; i < queries.size(); i++){
        for(int j = prev + 1; j <= queries[i].right; j++){
            st.upd(v[j], j);
        }
        prev = queries[i].right;
        int x = st.query(1, queries[i].isVal);
        if(x < queries[i].left){
            ans[queries[i].ind] = false;
        }else{
            ans[queries[i].ind] = true;
        }
    }
    return ans;
}
 
int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    vector<Query> queries;
    set<int> map_oc[(int)1e5 + 2];
    for(int i = 0; i < n; i++){
        cin >> v[i];
        map_oc[v[i]].insert(i);
    }
    int myMap[(int)1e5 + 2];
    for(int i = 1; i <= n; i++){
        myMap[i] = -1;
    }
    for(int i = 0; i < n; i++){
        myMap[v[i]] = i;
        int left;
        if(myMap[v[i] + 1] == -1){
            left = 0;
        }else{
            left = myMap[v[i] + 1];
        }
        int right;
        if(map_oc[v[i] + 1].lower_bound(i) == map_oc[v[i] + 1].end()){
            right = n - 1;
        }else{
            right = *map_oc[v[i] + 1].lower_bound(i);
        }
        queries.push_back({left, right, v[i], i});
    }
    vector<bool> ans = answer_queries(v, queries);
    map<int,bool> canAchieve;
    for(int i = 0; i < v.size(); i++) {
        if(ans[i]) {
            canAchieve[v[i] + 1] = ans[i];
        }
        if(v[i] != 1){
            canAchieve[1] = true;
        }
    }
    for(int i = 1; i <= v.size() + 2; i++){
        if(!canAchieve[i]){
            cout << i << endl;
            return 0;
        }
    }
}
