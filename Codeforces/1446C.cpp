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
vector<int> v;
int rec(int l, int r, int k){
    if(l > r){
        return 0;
    }
    if(k == -1){
        return 0;
    }
    int boundary = r + 1;
    for(int i = l; i <= r; i++){
        if((1 << k) & v[i]){
            boundary = i;
            break;
        }
    }
    int a1 = rec(l, boundary - 1, k - 1);
    int a2 = rec(boundary, r, k - 1);
    int left = boundary - l;
    int right = r - boundary + 1;
    return min(a1 + max(right - 1, 0), a2 + max(left - 1, 0));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    cout << rec(0, v.size() - 1, 31);
 
}
