#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
 
using namespace std;
 
struct solve {
    int n;
    vector<int> arr;
    int gcd(int a, int b) {
        if (min(a, b) == 0) return max(a, b);
        return gcd(max(a, b) % min(a, b), min(a, b));
    }
 
    int *st;
 
    int findGcd(int ss, int se, int qs, int qe, int si) {
        if (ss > qe || se < qs)
            return 0;
        if (qs <= ss && qe >= se)
            return st[si];
        int mid = ss + (se - ss) / 2;
        return gcd(findGcd(ss, mid, qs, qe, si * 2 + 1),
                   findGcd(mid + 1, se, qs, qe, si * 2 + 2));
    }
 
    int findRangeGcd(int ss, int se, int n) {
        if (ss < 0 || se > n - 1 || ss > se) {
            cout << "Invalid Arguments" << "\n";
            return -1;
        }
        return findGcd(0, n - 1, ss, se, 0);
    }
 
    int constructST(int ss, int se, int si) {
        if (ss == se) {
            st[si] = arr[ss];
            return st[si];
        }
        int mid = ss + (se - ss) / 2;
        st[si] = gcd(constructST(ss, mid, si * 2 + 1),
                     constructST(mid + 1, se, si * 2 + 2));
        return st[si];
    }
 
    int *constructSegmentTree(int n) {
        int height = (int) (ceil(log2(n)));
        int size = 2 * (int) pow(2, height) - 1;
        st = new int[size];
        constructST(0, n - 1, 0);
        return st;
    }
 
    bool valid(int x){
        set<int> s;
        for(int i = 0; i < n; i++){
            int l = i;
            int r = i + x;
            s.insert(findRangeGcd(l, r, arr.size()));
        }
        return (s.size() == 1);
    }
 
    int binSearch(int l, int r){
        //cout << l << " " << r << endl;
        int m = (l + r + 1)/2;
        if(l == r){
            return l;
        }
        if(!valid(m)){
            return binSearch(m, r);
        }else{
            return binSearch(l, m - 1);
        }
    }
    void read() {
        cin >> n;
        arr.resize(n);
        int GCD = 0;
        set<int> s;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            GCD = gcd(arr[i], GCD);
            s.insert(arr[i]);
        }
        if(s.size() == 1){
            cout << 0 << endl;
            return;
        }
        for(int i = 0; i < n; i++){
            arr.push_back(arr[i]);
        }
        constructSegmentTree(arr.size());
        cout << binSearch(0, n - 1) + 1 << endl;
    }
};
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve s;
        s.read();
    }
}
