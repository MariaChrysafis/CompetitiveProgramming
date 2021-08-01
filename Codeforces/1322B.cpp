#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <set>
#include <stack>
#include <map>
 
#define ll long long
using namespace std;
vector<int> vec;
multiset<int> ms;
void print(){
    for(int i: vec) cout << i << ' ';
    cout << endl;
}
int binSearch(int l, int r, int x){
    if(l == r){
        return l;
    }
    //find last occurence of something less than x
    int m = (l + r + 1)/2;
    if(vec[m] < x){
        return binSearch(m, r, x);
    }else{
        return binSearch(l, m - 1, x);
    }
}
 
int numOc(int r, int x, int y) {
    int a1 = binSearch(0, r, y + 1) - binSearch(0, r, x);
    return a1;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    ll ans = 0;
    for (int i = 0; i <= 24; i++) {
        vec.clear();
        ms.clear();
        vec.push_back(-INT_MAX);
        for (int j = 0; j < n; j++) {
            vec.push_back(v[j] % (1 << (i + 1)));
        }
        vec.push_back(INT_MAX);
        sort(vec.begin(), vec.end());
        int x = 0;
        ll pwr1 = (1 << i);
        for (int j = 0; j < n; j++) {
            x += numOc(j, pwr1 - vec[j + 1], pwr1 * 2 - 1 - vec[j + 1]);
            x += numOc(j, pwr1 * 3 - vec[j + 1], pwr1 * 4 - 2 - vec[j + 1]);
            if(x >= 1e9){
                x = x % 2;
            }
        }
        x %= 2;
        ans += x * (1 << i);
    }
    cout << ans << endl;
 
}
