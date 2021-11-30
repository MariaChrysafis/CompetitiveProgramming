#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <functional>
#include <queue>
#include <list>
#include <set>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

#define ll long long
using namespace __gnu_pbds;
using namespace std;

typedef
tree<
        int,
        null_type,
        less<int>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        ordered_set;

set<pair<int, int>> generate_edges(vector<int> v, int n, int m) {
    set<pair<int, int>> s;
    for (int i = 0; i < v.size(); i++) {
        if (i - 1 >= 0 && (i - 1) % m != (m -1 ) % m) s.insert({v[i], v[i - 1]});
        if (i + 1 < v.size() && (i + 1) % m != 0) s.insert({v[i], v[i + 1]});
        if (i - m >= 0) s.insert({v[i], v[i - m]});
        if (i + m < v.size()) s.insert({v[i], v[i + m]});
    }
    return s;
}

bool valid(vector<int> v, int n, int m) {
    assert(v.size() == n * m);
    vector<int> dum;
    for (int i = 0; i < n * m; i++) {
        dum.push_back(i);
    }
    set<pair<int, int>> s1 = generate_edges(dum, n, m);
    set<pair<int, int>> s2 = generate_edges(v, n, m);
    vector<pair<int, int>> vec;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(vec));
    return vec.empty();
}

vector<int> f(int n, int m) {
    vector<int> ans;
    int sz = n * m;
    ordered_set s;
    vector<int> dum;
    for (int i = 0; i < n * m; i++) {
        dum.push_back(i);
    }
    set<pair<int, int>> s1 = generate_edges(dum, n, m);
    for (int i = 0; i < n * m; i++) {
        s.insert(i);
    }
    while (sz--) {
        int t = 20;
        while (t--) {
            int r = rand() % (s.size());
            int x = *s.find_by_order(r);
            bool valid = true;
            ans.push_back(x);
            if (ans.size() >= 2 && (ans.size() - 2) % m != (m - 1) % m && s1.count({ans.back(), ans[ans.size() - 2]})) {
                valid = false;
            }
            if (ans.size() >= m + 1 && s1.count({ans.back(), ans[ans.size() - m - 1]})) {
                valid = false;
            }
            if (!valid) {
                ans.pop_back();
            } else {
                s.erase(s.find_by_order(r));
                break;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int t = 100;
    while(t--) {
        vector<int> v = f(n, m);
        if (v.size() == n * m) {
            cout << "YES\n";
            for (int i = 0; i < v.size(); i++) {
                cout << v[i] + 1 << ' ';
                if ((i + 1) % m == 0) {
                    cout << '\n';
                }
            }
            return 0;
        }
    }
    cout << "NO\n";


}
