#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
int Ceil(int a, int b) { return ceil((1.0 * a) / (1.0 * b)); }
void solve() {
    // cout << Ceil(5,2) << endl;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v;
    // v.resize(m);
    int oc[n];
    for (int i = 0; i < n; i++) {
        oc[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        vector<int> v1;
        int x;
        cin >> x;
        for (int j = 0; j < x; j++) {
            int a;
            cin >> a;
            a--;
            v1.push_back(a);
        }
        v.push_back(v1);
        if (v1.size() == 1) {
            oc[v1[0]]++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (oc[i] > Ceil(m, 2)) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
    for (int i = 0; i < n; i++) {
        oc[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        for (int j : v[i]) {
            oc[j]++;
        }
    }
    vector<int> stuff;
    for (int i = 0; i < n; i++) {
        if (oc[i] >= Ceil(m, 2)) {
            stuff.push_back(i);
        }
    }
    if (stuff.size() == 0) {
        for (int i = 0; i < m; i++) {
            cout << v[i][0] + 1 << " ";
        }
        cout << endl;
        return;
    }
    int x = stuff[0];
    vector<int> take(m);
    for (int i = 0; i < take.size(); i++) {
        take[i] = -1;
    }
    int cntr = 0;
    for (int i = 0; i < m; i++) {
        if (v[i].size() == 1 && v[i][0] == x) {
            take[i] = x;
            cntr++;
        }
    }
    for (int i = 0; i < m; i++) {
        if (v[i].size() == 1) continue;
        if(cntr == Ceil(m, 2)){
            break;
        }
        for (int j : v[i]) {
            if (j == x) {
                take[i] = x;
                if(cntr < Ceil(m, 2)) cntr++;
            }
        }
    }
    if(cntr >= Ceil(m, 2)){
        //cout << "B";
        //cout << 
        /*
        for(int i = 0; i < m; i++){
            for(int j: v[i]){
                cout << j << " ";
            }
            cout << endl;
        }
        */
    }
    for (int i = 0; i < m; i++) {
        if (take[i] != -1) {
            cout << x + 1 << " ";
            continue;
        } else {
            if (v[i][0] == x) {
                cout << v[i][1] + 1 << " ";
            } else {
                cout << v[i][0] + 1 << " ";
            }
        }
    }
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
