#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;
long long largestPower(long long a, long long b, long long x){
    long long ans = 0;
    int cntr = 0;
    for(long long dum = 1; dum >= 0; dum *= x){
        bool valid = false;
        long long strt = a/dum * dum;
        cntr++;
        for(long long x = strt; x <= b; x += dum){
            if(x >= a && x <= b){
                valid = true;
                break;
            }
        }
        if(valid){
            ans = cntr;
        }else{
            break;
        }
    }
    return ans;
}
long long solve1(long long a, long long b){
    return min(largestPower(a, b, 2), largestPower(a,b, 5)) - 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a, b;
    cin >> a >> b;
    cout << solve1(a, b);
}
