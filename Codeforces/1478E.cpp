#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#define ll long long
 
using namespace std;
const int MaxN = 200005;
int n;
namespace SgTree{
    int v[MaxN<<2], lazy[MaxN<<2];
    void setNode(int o,int l,int r,int qv){
        if(qv == -1) return ;
        v[o] = qv*(r-l+1), lazy[o] = qv;
    }
# define LSON o<<1,l,(l+r)>>1
# define RSON o<<1|1,((l+r)>>1)+1,r
    void pushDown(int o,int l,int r){
        setNode(LSON,lazy[o]);
        setNode(RSON,lazy[o]);
        lazy[o] = -1; // released
    }
    void modify(int ql,int qr,int qv,int o=1,int l=1,int r=n){
        if(qr < l || r < ql) return ;
        if(ql <= l && r <= qr)
            return setNode(o,l,r,qv);
        pushDown(o,l,r);
        modify(ql,qr,qv,LSON);
        modify(ql,qr,qv,RSON);
        v[o] = v[o<<1]+v[o<<1|1];
    }
    int query(int ql,int qr,int o=1,int l=1,int r=n){
        if(qr < l || r < ql) return 0;
        if(ql <= l && r <= qr) return v[o];
        pushDown(o,l,r);
        return query(ql,qr,LSON)+query(ql,qr,RSON);
    }
}
 
struct solver {
    bool read() {
        int q;
        cin >> n >> q;
        string s1, s2;
        cin >> s1 >> s2;
        vector<int> v1(n);
        vector<int> v2(n);
        for (int i = 0; i < n; i++) {
            v1[i] = (s1[i] == '1');
        }
        for (int i = 0; i < n; i++) {
            v2[i] = (s2[i] == '1');
            SgTree::modify(i + 1, i + 1, v2[i]);
        }
        vector<pair<int,int>> queries;
        for(int i = 0; i < q; i++){
            int l, r;
            cin >> l >> r;
            queries.push_back({l, r});
        }
        reverse(queries.begin(), queries.end());
        for(int i = 0; i < q; i++){
            int x = SgTree::query(queries[i].first, queries[i].second);
            int sz = queries[i].second - queries[i].first + 1;
            if(2 * x == sz) return false;
            else if(2 * x < sz){
                SgTree::modify(queries[i].first, queries[i].second, 0);
            }else{
                SgTree::modify(queries[i].first, queries[i].second, 1);
            }
        }
        vector<int> v;
        for(int i = 0; i < n; i++){
            v.push_back(SgTree::query(i + 1, i + 1));
        }
        return (v == v1);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solver s;
        bool b = s.read();
        if (b) cout << "YES\n";
        else cout << "NO\n";
    }
}
