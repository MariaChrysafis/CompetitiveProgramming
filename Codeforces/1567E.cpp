#include <iostream>
#include <cmath>
#include <vector>
#define ll long long
using namespace std;
struct Node {
    ll suf;
    ll pref;
    ll num;
    ll first;
    ll last;
    bool allUp;
    void print(){
        cout << "suf: " << suf << "    ";
        cout << "pref: " << pref << "    ";
        cout << "num: " << num << "    ";
        cout << "first: " << first << "    ";
        cout << "last: " << last << "    ";
        cout << "allUp: " << allUp << "    ";
        cout << endl;
    }
};
 
ll c2(ll a) {
    return (a * (a + 1)) / 2;
}
 
template<class T>
struct Seg { // comb(ID,b) = b
    const T ID = {0, 0, 0, -1, -1, true};
 
    T comb(T a, T b) {
        if(a.first == ID.first) return b;
        if(b.first == ID.first) return a;
        T c;
        c.last = b.last;
        c.first = a.first;
        if (a.last <= b.first) {
            c.allUp = (a.allUp && b.allUp);
            c.suf = b.suf + a.suf * b.allUp;
            c.pref = a.pref + b.pref * a.allUp;
            if (!a.allUp && !b.allUp) {
                c.num = a.num + b.num + c2(a.suf + b.pref);
            } else if (a.allUp && b.allUp) {
                c.num = 0;
            } else if (!a.allUp && b.allUp) {
                c.num = a.num;
            } else {
                c.num = b.num;
            }
        } else {
            c.allUp = false;
            c.pref = a.pref;
            c.suf = b.suf;
            if (!a.allUp && !b.allUp) {
                c.num = a.num + b.num + c2(a.suf) + c2(b.pref);
            } else if (a.allUp && b.allUp) {
                c.num = 0;
            } else if (!a.allUp && b.allUp) {
                c.num = a.num + c2(a.suf);
            } else {
                c.num = b.num + c2(b.pref);
            }
        }
        return c;
    }
 
    int n;
    vector<T> seg;
 
    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }
 
    void pull(int p) {
        seg[p] = comb(seg[2 * p], seg[2 * p + 1]);
    }
 
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }
 
    T query(int l, int r) {    // min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = comb(ra, seg[l++]);
            if (r & 1) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};
 
int main() {
    ll n, q;
    cin >> n >> q;
    ll arr[n];
    Seg<Node> st;
    st.init(n + 2);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        st.upd(i, {1, 1, 0, arr[i], arr[i], true});
    }
    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll x, y;
            cin >> x >> y;
            x--;
            st.upd(x, {1, 1, 0, y, y, true});
        } else {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            Node myNode = st.query(l, r);
            if(myNode.allUp){
                cout << c2(r - l + 1) << endl;
            }else {
                cout << c2(myNode.pref) + c2(myNode.suf) + myNode.num << endl;
            }
        }
 
    }
}
