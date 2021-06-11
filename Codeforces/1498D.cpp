#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define Integer int
#define ll long long
Integer main(){
    int n, m;
    cin >> n >> m;
    ll val[m + 1];
    for(int i = 0; i <= m; i++) val[i] = -1;
    val[0] = 0;
    for(int op = 1; op <= n; op++){
        ll t, x, y;
        cin >> t >> x >> y;
        for(int j = 0; j <= m; j++){
            if(val[j] == -1 || val[j] == op) continue;
            ll cur = j;
            for(int i = 1; i <= y; i++){
                if(t == 1) cur += (x + 99999)/100000;
                else cur = (cur * x + 99999)/100000;
                if(cur > m || val[cur] != - 1) break;
                val[cur] = op;
            }
        }
    }
    for(int i = 1; i <= m; i++) cout << val[i] << " ";
}
