#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
 
string yesNo(bool b){
    if(b) return "Yes";
    else return "No";
}
 
void print(vector<int> v) {
    for (int i: v) cout << i << ' ';
    cout << endl;
}
bool valid(vector<int> me, vector<int> ilya, int added){
    long long il = 0;
    long long cur = 0;
    int new_sz = ilya.size() + added;
    while(ilya.size() != new_sz){
        ilya.push_back(0);
    }
    reverse(me.begin(), me.end());
    while(me.size() != new_sz){
        me.push_back(100);
    }
    reverse(me.begin(), me.end());
    int pref = new_sz - new_sz/4;
    for(int i = 0; i < pref; i++){
        il += ilya[i];
        cur += me[i];
    }
    return (cur >= il);
}
vector<int> v1, v2;
int binSearch(int left, int right){
    int mid = (left + right)/2;
    if(left == right){
        return left;
    }
    if(valid(v1, v2, mid)){
        return binSearch(left, mid);
    }else{
        return binSearch(mid + 1, right);
    }
}
 
void solve(){
    int n;
    cin >> n;
    v1.resize(n), v2.resize(n);
    for(int i = 0; i < n; i++) cin >> v1[i];
    for(int i = 0; i < n; i++) cin >> v2[i];
    sort(v1.begin(), v1.end());
    reverse(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    reverse(v2.begin(), v2.end());
    cout << binSearch(0, 10 * n) << endl;
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
