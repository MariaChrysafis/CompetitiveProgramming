#include <bits/stdc++.h>
using namespace std;
template<class T>
class SegmentTree {
public:

    SegmentTree() {

    }

    void resz (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};

struct Query {
    int l, r, k, ind;
    int res;
};

bool compIndex (Query q1, Query q2) {
    return (q1.ind < q2.ind);
}

bool compValue (Query q1, Query q2) {
    return (q1.k > q2.k);
}

class Queries {
public:
    vector<int> v;
    SegmentTree<int> st;

    Queries (vector<int> v) {
        this->v = v;
        st.resz(v.size());
    }

    void respond (vector<Query> &queries) {
        sort(queries.begin(), queries.end(), compValue);
        vector<pair<int,int> > tot;
        for (int i = 0; i < v.size(); i++) {
            tot.push_back(make_pair(v[i], i));
        }
        sort(tot.begin(), tot.end()), reverse(tot.begin(), tot.end());
        int prev = -1;
        vector< pair<int,int> > ans;
        for (auto& q: queries) {
            while (prev + 1 < v.size() && tot[prev + 1].first > q.k) {
                st.update(tot[++prev].second, 1);
            }
            q.res = st.query(q.l, q.r);
        }
        sort(queries.begin(), queries.end(), compIndex);
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int q;
    cin >> q;
    vector<Query> queries;
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--;
        Query qr;
        qr.l = l, qr.r = r, qr.k = k, qr.ind = i;
        queries.push_back(qr);
    }
    Queries qr(v);
    qr.respond(queries);
    for (auto& q: queries) {
        cout << q.res << '\n';
    }
}
