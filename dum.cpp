#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

#define ll long long
using namespace std;
#define P(x, y) make_pair(x,y)
using namespace std;
template<class T> struct SegMin { // comb(ID,b) = b
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
template<class T> struct SegSum { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return a + b; }
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
bool comp(pair<int,int> p1, pair<int,int> p2){
    if(p1.second == p2.second){
        return (p1.first < p2.first);
    }
    return (p1.second < p2.second);
}
vector<int> response(vector<int> v, vector<pair<int,int>> queries){
    SegSum<int> st;
    st.init(v.size() + 1);
    map<int,int> oc;
    for(int i = 0; i < v.size(); i++) oc[v[i]] = -1;
    int last = -1;
    vector<int> dist;
    for(int i = 0; i < queries.size(); i++){
        for(int j = last + 1; j <= queries[i].second; j++){
            if(oc[v[j]] != -1){
                st.upd(oc[v[j]], 0);
            }
            st.upd(j, 1);
            oc[v[j]] = j;
        }
        last = queries[i].second;
        dist.push_back(st.query(queries[i].first, queries[i].second));
    }
    return dist;
}
int main() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    map<int,int> myMap, cur_oc;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        v[i]--;
        myMap[i] = cur_oc[i] = -1;
    }
    SegMin<int> st;
    st.init(n + 2);
    for(int i = 0; i < n; i++){
        st.upd(i, v[i]);
    }
    SegSum<int> oc;
    oc.init(n + 2);
    vector<pair<int,int>> queries;
    while(q--){
        int u1, u2;
        cin >> u1 >> u2;
        queries.push_back(make_pair(u1 - 1, u2 - 1));
    }
    vector<pair<int,int>> bad_intervals;
    for(int i = 0; i < n; i++){
        if(cur_oc[v[i]] != -1){
            int x=  cur_oc[v[i]];
            int myMin = st.query(x + 1, i - 1);
            if(myMin < v[i]){
                bad_intervals.push_back({x, i});
            }
        }
        cur_oc[v[i]] = i;
    }
    map<pair<int,int>, int> f;
    for(int i = 0; i < queries.size(); i++){
        f[queries[i]] = i;
    }
    vector<pair<int,int>> orig = queries;
    sort(queries.begin(), queries.end(), comp);
    vector<int> dist = response(v, queries);
    //for(int i: dist) cout << i << " ";
    //cout << endl;
    int pr[queries.size()];
    for(int i = 0; i < queries.size(); i++) pr[i] = 0;
    int ind = 0;
    for(pair<int,int> p: queries){
        int ans = dist[ind];
        for(pair<int,int> q: bad_intervals){
            if(p.first <= q.first && p.second >= q.second){
                ans++;
            }
            if(p.second < q.second) break;
        }
        f[p] = ans;
        ind++;
    }
    for(pair<int,int> p: orig){
        cout << f[p] << "\n";
    }
}
