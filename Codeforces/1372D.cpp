#include <iostream>
#include <vector>

using namespace std;

template<class T>
struct Seg { // comb(ID,b) = b
    const T ID = 0;

    T comb(T a, T b) { return a + b; }

    int n;
    vector<T> seg;

    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }

    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }

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
    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<long long> ans;
    for (int i = 0; i < n / 2; i++) {
        ans.push_back(v[2 * i + 1]);
    }
    for (int i = 0; i <= n / 2; i++) {
        ans.push_back(v[2 * i]);
    }
    for (int i = 0; i < n; i++) {
        ans.push_back(ans[i]);
    }
    //cout << ans.size() << endl;
    Seg<long long> seg;
    seg.init(ans.size());
    for (int i = 0; i < ans.size(); i++) {
        //cout << i << " " << ans[i] << endl;
        seg.upd(i, ans[i]);
    }
    long long myMax = 0;
    for (int i = 0; i < n; i++) {
        myMax = max(seg.query(i, i + n / 2), myMax);
    }
    cout << myMax << endl;
}
