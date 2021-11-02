#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#define ll long long
using namespace std;
struct Solver {
    long N, M;
    long arr[200010];
    multiset<long> up;
    multiset<long> low;

    void ins(long val){ // insert val into sets
        long a = *low.rbegin(); // current median
        if(a < val){
            up.insert(val);
            if(up.size() > M/2){
                low.insert(*up.begin());
                up.erase(up.find(*up.begin()));
            }
        }
        else{
            low.insert(val);
            if(low.size() > (M + 1)/2){
                up.insert(*low.rbegin());
                low.erase(low.find(*low.rbegin()));
            }
        }
    }

    void er(long val){ // erase from sets
        if(up.find(val) != up.end()) up.erase(up.find(val));
        else low.erase(low.find(val));
        if(low.empty()){
            low.insert(*up.begin());
            up.erase(up.find(*up.begin()));
        }
    }
    vector<int> solve (vector<int> v) {
        for (int i = 0; i < v.size(); i++) {
            arr[i] = v[i];
        }
        low.insert(arr[0]); for(int i = 1; i < M; i++) ins(arr[i]);
        vector<int> ans;
        //cout << *low.rbegin() << " ";
        ans.push_back(*low.rbegin());
        for(long i = M; i < N; i++){
            if(M == 1){
                ins(arr[i]);
                er(arr[i - M]);
            }
            else{
                er(arr[i - M]);
                ins(arr[i]);
            }
            //cout << *low.rbegin() << " ";
            ans.push_back(*low.rbegin());
        }
        //cout << endl;
        return ans;
    }
};
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return query(dum, tl, mid, l, r) + query(dum + 1, mid + 1, tr, l, r);
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] += y;
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }
};
int main() {
    //freopen("shortcut.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Solver slv;
    slv.N = n, slv.M = k;
    vector<int> medians = slv.solve(arr);
    map<int,int> myMap;
    int rev[2 * n + 3];
    set<int> s;
    for (int i: arr) {
        s.insert(i);
    }
    for (int i: medians) {
        s.insert(i);
    }
    int cntr = 0;
    for (int i: s) {
        cntr++;
        myMap[i] = cntr;
        rev[cntr] = i;
    }
    segmentTree st;
    segmentTree st1;
    st.resz(2 * n + 3), st1.resz(2 * n + 3);
    for (int i = 0; i < k; i++) {
        st.update(myMap[arr[i]], 1);
        st1.update(myMap[arr[i]], arr[i]);
    }
    for (int i = 0; i < n; i++) {
        if (i + k == n + 1) {
            break;
        }
        long long med = myMap[medians[i]];
        cout << st.query(0, med) * rev[med] - st1.query(0, med) + st1.query(med + 1, n + 1) - st.query(med + 1, 2 * n + 1) * rev[med]  << " ";
        if (i + k != n) {
            int a = myMap[arr[i + k]];
            st.update(a, 1);
            st1.update(a, arr[i + k]);
        }
        int a = myMap[arr[i]];
        st.update(a, -1);
        st1.update(a, -arr[i]);
    }
}
