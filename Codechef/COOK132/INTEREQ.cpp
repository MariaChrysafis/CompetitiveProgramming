#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <set>
#include <queue>

#define ll long long
using namespace std;
using namespace std;

void print(vector<int> v) {
    for (int i: v) cout << i << " ";
}

struct Solver {
    int n;
    vector<int> ans, cur;

    int binSearch(int l, int r, int ind) {
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        vector<int> cur1;
        for (int i = l; i <= m; i++) {
            cur1.push_back(cur[i]);
        }
        cur1.push_back(ind);
        if (query(cur1) == 2) {
            return binSearch(l, m, ind);
        } else {
            return binSearch(m + 1, r, ind);
        }
    }

    int binSearch1(int l, int r, int ind) {
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        vector<int> cur1;
        for (int i = l; i <= m; i++) {
            cur1.push_back(cur[i]);
        }
        cur1.push_back(ind);
        if (query1(cur1) == 2) {
            return binSearch1(l, m, ind);
        } else {
            return binSearch1(m + 1, r, ind);
        }
    }

    int query1(vector<int> q) {
        map<int, int> oc;
        for (int i: q) {
            oc[ans[i]]++;
        }
        int myMax = 0;
        for (pair<int, int> p: oc) {
            myMax = max(p.second, myMax);
        }
        return myMax;
    }

    int query(const vector<int> q) {
        cout << "? " << q.size() << " ";
        for (int i: q) {
            cout << i + 1 << " ";
        }
        cout << endl;
        int x;
        cin >> x;
        return x;
    }

    bool isValid() {
        n = ans.size();
        cur.clear();
        vector<int> res;
        for (int i = 0; i < n; i++) {
            vector<int> dum = cur;
            dum.push_back(i);
            if (query1(dum) == 1) {
                cur.push_back(i);
                res.push_back(cur.size());
            } else {
                int x = binSearch1(0, (int) cur.size() - 1, i);
                res.push_back(res[cur[x]]);
            }
        }
        return (res == ans);
    }
    void read(){
        cin >> n;
        int q;
        cin >> q;
        cur.clear();
        vector<int> res;
        for (int i = 0; i < n; i++) {
            vector<int> dum = cur;
            dum.push_back(i);
            if (query(dum) == 1) {
                cur.push_back(i);
                res.push_back(cur.size());
            } else {
                int x = binSearch(0, (int) cur.size() - 1, i);
                res.push_back(res[cur[x]]);
            }
        }
        cout << "! ";
        print(res);
        cout << endl;
        int is_correct;
        cin >> is_correct;
        assert(is_correct == 1);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        Solver s;
        s.read();
    }
}
