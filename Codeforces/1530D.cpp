#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
 
int slv2(vector<int> arr, int n) {
    vector<int> v;
    for (int i = 0; i < n; i++) v.push_back(i + 1);
    sort(v.begin(), v.end());
    int myMax = 0;
    do {
        bool valid = true;
        for (int i = 0; i < n; i++) {
            if (v[i] == i + 1) {
                valid = false;
            }
        }
        if (valid) {
            int cntr = 0;
            for (int i = 0; i < n; i++) {
                if (arr[i] == v[i]) {
                    cntr++;
                }
            }
            myMax = max(myMax, cntr);
        }
    } while (next_permutation(v.begin(), v.end()));
    return myMax;
}
void print(vector<int> v){
    for(int i: v){
        cout << i << ' ';
    }
    cout << endl;
}
int cost(vector<int> a, vector<int> b) {
    int cntr = 0;
    set<int> s;
    map<int,int> cnt;
    for (int i = 0; i < a.size(); i++) {
        cnt[a[i]]++;
        if(b[i] == i + 1){
            return -1;
        }
        if (a[i] == b[i]) {
            cntr++;
        }
        s.insert(a[i]);
    }
    return cntr;
}
 
int slv1(vector<int> arr, int n) {
    bool df = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] != i + 1){
            df = 1;
        }
    }
    if(df == 0){
        cout << 0 << endl;
        for(int i = 0; i < n; i++){
            cout << arr[(i + 1) % n] << " ";
        }
        cout << endl;
        return 0;
    }
    map<int, int> oc;
    for (int i = 0; i < n; i++) {
        if (arr[i] != i + 1) {
            oc[arr[i]] = i + 1;
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = 0;
    }
    set<int> s;
    for (int i = 1; i <= n; i++) {
        if (oc[i] != 0) {
            ans[oc[i] - 1] = i;
            s.insert(i);
        }
    }
    vector<int> needy;
    for (int i = 0; i < n; i++) {
        if (s.count(i + 1) == 0) {
            needy.push_back(i + 1);
        }
    }
    reverse(needy.begin(), needy.end());
    //if(needy.size() == 1){
    map<int, int> cnt;
    for (int i: arr) cnt[i]++;
    vector<int> indices;
    vector<int> choices;
    vector<int> dum_ans = ans;
    for (int i = 1; i <= n; i++) {
        dum_ans[i - 1] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 1) {
            dum_ans[oc[i] - 1] = i;
        }
    }
    for(int i = 0; i < n; i++){
        if(dum_ans[i] == 0){
            indices.push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i] != 1) {
            choices.push_back(i);
        }
    }
    if (choices.size() == 2 && indices.size() == 2) {
        vector<int> ans1 = dum_ans;
        vector<int> ans2 = dum_ans;
        ans1[indices[0]] = choices[0], ans1[indices[1]] = choices[1];
        ans2[indices[1]] = choices[0], ans2[indices[0]] = choices[1];
        //print(ans1);
        //print(ans2);
        //cout << "YES" << endl;
        //cout << cost(arr, ans1) << " " << cost(arr, ans2) << endl;
        if (cost(arr, ans1) > cost(arr, ans2)) {
            cout << cost(arr, ans1) << endl;
            print(ans1);
            return cost(arr, ans1);
        } else {
            cout << cost(arr, ans2) << endl;
            print(ans2);
            return cost(arr, ans2);
        }
    }
 
    //}
    int ind = 0;
    //print(ans);
    for (int i = 0; i < n; i++) {
        if (ans[i] == 0) {
            ans[i] = needy[ind];
            ind++;
        }
    }
    //print(ans);
    ind = -1;
    for (int i = 0; i < n; i++) {
        if (ans[i] == i + 1) {
            ind = i;
        }
    }
    if (ind != -1) {
        int cntr = 0;
        for (int i = 0; i < n; i++) {
            if (ans[i] == arr[i]) {
                cntr++;
            }
        }
        int x = 0;
        while ((x == ind || ans[x] == arr[x]) && x < n) x++;
        if (x == n) {
            x = (ind + 1) % n;
        }
        //cout << x << " " << ind << endl;
        swap(ans[x], ans[ind]);
    }
    //print(ans);
    int sz = cost(arr, ans);
    cout << sz << endl;
    print(ans);
    return sz;
}
 
void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int x = slv1(arr, n);
    //int y = slv2(arr, n);
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
 
/*
 * Notes to self:
 * before implementing THINK
 * Long Long vs Int?
 */
