#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define ll long long
using namespace std;
int query(int l, int r){
    if(l >= r) return -1;
    cout << "? " << l + 1 << " " << r + 1 << '\n';
    cout.flush();
    int x;
    cin >> x;
    x--;
    return x;
}
int rec(int l, int r, int ind){
    if(r < l) return -1;
    if(l == r){
        return l;
    }
    if(r - l == 1){
        if(ind == l) return r;
        else return l;
    }
    if(r - l == 2){
        int x = query(l, l + 1);
        int y = query(l + 1, l + 2);
        int z = query(l, l + 2);
        int a = rec(l, l + 1, x);
        int b = rec(l + 1, l + 2, y);
        if(a == b) return a;
        if(l != x && l != y && l != z){
            return l;
        }
        if(l + 1 != x && l + 1 != y && l + 1 != z){
            return l + 1;
        }
        return l + 2;
    }
    int m = (r + l - 1)/2;
    int ans1 = query(l , m);
    int  ans2 = query(m + 1, r);
    if(ind >= l && ind <= m){
        //ind lies in (l, m)
        if(ans1 == ind){
            return rec(l, m, ans1);
        }else{
            return rec(m + 1, r, ans2);
        }
    }else{
        if(ans2 == ind){
            return rec(m + 1, r, ans2);
        }else{
            return rec(l, m, ans1);
        }
    }
    return -1;
 
}
void solve(){
    int n;
    cin >> n;
    int x = rec(0, n - 1, query(0, n - 1));
    cout << "! " << x + 1 << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
