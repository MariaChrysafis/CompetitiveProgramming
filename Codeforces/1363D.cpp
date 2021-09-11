#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;
vector<int> inRange(int l, int r){
    vector<int> v;
    for(int i = l; i <= r; i++){
        v.push_back(i);
    }
    return v;
}
int queriesSoFar = 0;
map<vector<int>, int> myMap;
int query(vector<int> indices){
    if(myMap[indices] != 0){
        return myMap[indices];
    }
    queriesSoFar++;
    cout << "? " << indices.size() << ' ';
    for(int i: indices) cout << i + 1 << " ";
    cout << '\n';
    cout.flush();
    int x;
    cin >> x;
    myMap[indices] = x;
    return x;
}

int indexOfMaximum(int l, int r, int rangeMax){
    if(l == r){
        return l;
    }
    int m = (l + r)/2;
    int a = query(inRange(m + 1, r));
    if (a == rangeMax) {
        return indexOfMaximum(m + 1, r, rangeMax);
    }
    return indexOfMaximum(l, m, rangeMax);
}

vector<int> setMinus(vector<int> v, vector<int> u){
    vector<int> ans;
    for(int i = 0; i < v.size(); i++){
        bool found = false;
        for(int j = 0; j < u.size(); j++){
            if(u[j] == v[i]){
                found = true;
            }
        }
        if(!found){
            ans.push_back(v[i]);
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<vector<int>> v;
    for(int i = 0; i < k; i++){
        int sz;
        cin >> sz;
        v.push_back({});
        for(int j = 0; j < sz; j++){
            int x;
            cin >> x;
            v.back().push_back(x - 1);
        }
    }
    int l1 = query(inRange(0, (n - 1)/2));
    int r2 = query(inRange((n + 1)/2, n - 1));
    int rngMax = max(l1, r2);
    int ind = indexOfMaximum(0, n - 1, rngMax);
    int P[k];
    for(int i = 0; i < k; i++){
        P[i] = rngMax;
    }
    for(int i = 0; i < k; i++){
        for(int j: v[i]){
            if(j == ind){
                P[i] = query(setMinus(inRange(0, n - 1), v[i]));
            }
        }
    }
    cout << "! ";
    for(int i: P){
        cout << i << " ";
    }
    cout << endl;
    string s;
    cin >> s;
    assert(s == "Correct");
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        queriesSoFar = 0;
        solve();
        myMap.clear();
    }

}
