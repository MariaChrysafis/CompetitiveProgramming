#include <bits/stdc++.h>
using namespace std;
int res (vector<int> a) {
    int cur = -1;
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) {
        if (cur == -1) {
            cur = a[i], cnt = 1;
        } else if (cur == a[i]) {
            cnt++;
        } else {
            cnt--;
            if (!cnt) {
                cur = -1;
            }
        }
    }
    return cnt;
}
vector<int> canDo (vector<int> v) {
    priority_queue<pair<int,int> > pq;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != 0) {
            pq.push(make_pair(v[i], i));
        }
    }
    vector<int> a;
    while (!pq.empty()) {
        pair<int,int> p = pq.top();
        pq.pop();
        a.push_back(p.second);
        if (p.first != 1) {
            pq.push(make_pair(p.first - 1, p.second));
        }
    }
    return a;
}
vector<int> place;
void solve (vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        assert(v[i] >= 0);
        if (v[i] == 0) continue;
        vector<int> ans;
        place.push_back(i);
        for (int x: place) {
            ans.push_back(x);
        }
        v[i]--;
        for (int x: canDo(v)) {
            ans.push_back(x);
        }
        if (res(ans) != 0) {
            place.pop_back();
            v[i]++;
        } else {
            solve(v);
            return;
        }
    }
}
int main() {
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<int> arr(m);
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
    }
    for (int j = arr[0]; j >= 1; j--) {
        arr[0] -= j;
        if (res(canDo(arr)) == 0) {
            cout << "YES\n";
            cout << j<< '\n';
            solve(arr);
            for (int x: place) {
                cout << x + 1 << '\n';
            }
            int x = j;
            while (j--) {
                cout << 1 << '\n';
            }
            exit(0);
        }
        arr[0] += j;
    }
    cout << "NO\n";
}
