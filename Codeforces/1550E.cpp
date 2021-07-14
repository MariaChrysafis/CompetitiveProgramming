#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
const int INF = 1e9;
int n, k;
string s;
bool isValid(int x){
    int pref[n + 1][k];
    for(int i = 0; i < k; i++){
        pref[0][i] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < k; j++){
            pref[i][j] = pref[i - 1][j] + ((s[i - 1] == 'a' + j) || (s[i - 1] == '?'));
        }
    }
    int latest[n + 2][k];
    for(int j = 0; j < k; j++){
        latest[n + 1][j] = INF;
    }
    for(int i = n; i >= 0; i--){
        for(int j = 0; j < k; j++){
            latest[i][j] = latest[i + 1][j];
            if(i + x <= n && pref[i + x][j] - pref[i][j] == x){
                latest[i][j] = i;
            }
        }
    }
    int dpMask[(1 << k)];
    dpMask[0] = 0;
    for(int i = 1; i < (1 << k); i++){
        dpMask[i] = INF;
        for(int last = 0; last < k; last++){
            if(i & (1 << last)){
                int newMask = i - (1 << last);
                if(dpMask[newMask] < n){
                    int str = latest[dpMask[newMask]][last];
                    dpMask[i] = min(dpMask[i], str + x);
                }
            }
        }
    }
    return (dpMask[(1 << k) - 1] <= n);
}
int binSearch(int l, int r){
    int m = (l + r + 1)/2;
    if(l == r){
        return l;
    }
    if(isValid(m)){
        return binSearch(m, r);
    }else{
        return binSearch(l, m - 1);
    }
}
 
int main() {
    cin >> n >> k;
    cin >> s;
    //cout << isValid(3) << endl;
    cout << binSearch(0, s.length()) << endl;
}
