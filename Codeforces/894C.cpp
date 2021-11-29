#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <set>
#define ll long long
using namespace std;
int gcd (int x, int y) {
    if (!x || !y) return max(x,y);
    return gcd(max(x,y) % min(x,y), min(x,y));
}
bool fine (vector<int> v, vector<int> vec) {
    set<int> s; for (int i: v) s.insert(i);
    set<int> s1;
    for (int i = 0; i < vec.size(); i++) {
        int g = vec[i];
        s1.insert(g);
        for (int j = i + 1; j < vec.size(); j++) {
            g = gcd(g, vec[j]);
            s1.insert(g);
        }
    }
    return (s == s1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    set<int> values;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        values.insert(v[i]);
    }
    vector<int> ans;
    for (int i = 0; i < v.size(); i++) {
        ans.push_back(v[i]);
        int g = 0;
        bool fine = true;
        for (int j = ans.size() - 1; j >= 0; j--) {
            g = gcd(g, ans[j]);
            if (!values.count(g)) {
                fine = false;
            }
        }
        if (!fine) {
            ans.pop_back();
            ans.push_back(v[0]);
            ans.push_back(v[i]);
        }
    }
    if (!fine(v, ans)) {
        cout << "-1\n";
        return 0;
    }
    cout << ans.size() << endl;
    for (int i: ans) {
        cout << i << ' ';
    }
}
