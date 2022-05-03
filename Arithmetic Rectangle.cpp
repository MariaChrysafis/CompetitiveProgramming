#include <bits/stdc++.h>
using namespace std;
vector<int> solver1 (vector<int> v) { //find first smaller one to left
    stack<int> st;
    vector<int> val(v.size());
    for (int i = 0; i < v.size(); i++) {
        while (!st.empty() && v[st.top()] >= v[i]) {
            st.pop();
        }
        if (st.empty()) {
            val[i] = -1;
        } else {
            val[i] = st.top();
        }
        st.push(i);
    }
    return val;
}

vector<int> solver2 (vector<int> v) { //find first smaller one to right
    stack<int> st;
    vector<int> val(v.size());
    for (int i = v.size() - 1; i >= 0; i--) {
        while (!st.empty() && v[st.top()] >= v[i]) {
            st.pop();
        }
        if (st.empty()) {
            val[i] = v.size();
        } else {
            val[i] = st.top();
        }
        st.push(i);
    }
    return val;
}

int getter (vector<int> v) {
    if (v.size() <= 2) return v.size();
    vector<int> a;
    for (int i = 1; i < v.size(); i++) {
        a.push_back(v[i] - v[i - 1]);
    }
    int myMax = 2;
    int cur = 2;
    for (int i = 1; i < a.size(); i++) {
        if (a[i] == a[i - 1]) cur++, myMax = max(myMax, cur);
        else cur = 2;
    }
    return myMax;
}

int get_grid (vector<vector<int> >& arr, int i, int j) {
    return (int64_t)arr[i][j] + (int64_t)arr[i + 1][j + 1] - (int64_t)arr[i + 1][j] - (int64_t)arr[i][j + 1];
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > arr(n);
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        arr[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        vector<int> v;
        for (int j = 0; j < m; j++) {
            v.push_back(arr[i][j]);
        }
        myMax = max(myMax, getter(v));
    }
    for (int j = 0; j < m; j++) {
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(arr[i][j]);
        }
        myMax = max(myMax, getter(v));
    }
    vector<vector<int> > d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        d[i].resize(m - 1);
    }
    for (int i = (int)d.size() - 1; i >= 0; i--) {
        for (int j = 0; j < (int)d[i].size(); j++) {
            if (i == (int)d.size() - 1 || get_grid(arr, i + 1, j) != get_grid(arr, i, j)) {
                d[i][j] = 1;
            } else {
                d[i][j] = d[i + 1][j] + 1;
            }
        }
    }
    for (int i = 0; i < d.size(); i++) {
        vector<int> v1 = solver1(d[i]);
        vector<int> v2 = solver2(d[i]);
        vector<int> right(d[0].size());
        int prev = -1; 
        for (int j = (int)d[0].size() - 1; j >= 0; j--) {
            if (j == (int)d[0].size() - 1) prev = j;
            else if (get_grid(arr, i, j) != get_grid(arr, i, j + 1)) prev = j;
            right[j] = prev;
        }
        prev = -1;
        for (int j = 0; j < d[0].size(); j++) {
            if (j == 0) prev = 0;
            else if (get_grid(arr, i, j) != get_grid(arr, i, j - 1)) prev = j;
            int res = (min(right[j], v2[j] - 1) - max(prev, v1[j] + 1) + 2) * ((int)d[i][j] + 1);
            myMax = max(myMax, res);
        }
    }
    cout << myMax << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
