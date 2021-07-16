#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int pref[200][200000];
int n;
int binSearchPref(int l, int r, int x, int ch){
    int m = (l + r)/2;
    if(l == r){
        return r;
    }
    if(pref[ch][m] >= x){
        return binSearchPref(l, m, x, ch);
    }else{
        return binSearchPref(m + 1, r, x, ch);
    }
}
int binSearchSuf(int l, int r, int x, int ch){
    int m = (l + r + 1)/2;
    if(l == r){
        return r;
    }
    if(pref[ch][n - 1] - pref[ch][m - 1] >= x){
        return binSearchSuf(m, r, x, ch);
    }else{
        return binSearchSuf(l, m - 1, x, ch);
    }
}
void solve() {
    cin >> n;
    vector<int> arr(n);
    int best = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
    }
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                pref[i][j] = (arr[j] == i);
            } else {
                pref[i][j] = pref[i][j - 1] + (arr[j] == i);
            }
        }
        best = max(best, pref[i][n - 1]);
    }
    reverse(arr.begin(), arr.end());
    for(int i = 0; i < 200; i++){
        for(int x = 1; x <= pref[i][n- 1]; x++){
            int l = binSearchPref(0, n - 1, x, i);
            int r = binSearchSuf(0, n - 1, x, i);
            l++, r--;
            if(l > r) continue;
            int myMax = 0;
            for(int j = 0; j < 200; j++){
                int cur = pref[j][r] - pref[j][l - 1];
                myMax = max(myMax, cur);
            }
            //cout << 2 * x << " " << myMax << endl;
            best = max(best, 2 * x + myMax);
        }
    }
    cout << best << '\n';
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
