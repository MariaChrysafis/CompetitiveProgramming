#include<bits/stdc++.h>
 
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <random>
using namespace std;
mt19937 rnd(time(0));
struct solve{
    void read(){
        int n;
        cin >> n;
        int q;
        cin >> q;
        vector<long long> v(n);
        vector<int> s[300005];
        for(int i = 0; i < n; i++) cin >> v[i], s[v[i]].push_back(i);
        while(q--){
            int l, r;
            cin >> l >> r;
            l--, r--;
            int myMax = 0;
            for(int i = 0; i < 30; i++){
                int x = rnd() % (r - l + 1) + l;
                x = v[x];
                int pos = upper_bound(s[x].begin(), s[x].end(), r) - lower_bound(s[x].begin(), s[x].end(), l);
                myMax = max(myMax, pos);
            }
            cout << max(1, 2 * myMax - r + l - 1) << '\n';
        }
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve s;
    s.read();
}
