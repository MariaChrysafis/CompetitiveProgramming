#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
vector<long long> v;
long long binSearch(long long target){
    //find the index of the first element than is greater target 
    long long l = 0;
    long long r = v.size() - 1;
    long long ans = -1;
    while(l <= r){
        //cout << l << " " << r << endl;
        long long mid = (l + r)/2;
        if(v[mid] <= target){
            l = mid + 1;
        }else{
            ans = mid;
            r = mid - 1;
        }
    }
    return ans;
}
long long find_ans(long long ind){
    //find the number of elements that sum to something less than or equal to ind
    long long x = 0;
    long long n = v.size();
    //cout << v.size() << endl;
    for(int i = 0; i < v.size(); i++){
        long long j = binSearch(ind - v[i]);
        if(j == -1){
            x += n - 1;
            continue;
        }
        x += j - (i < j);
    }
    return x;
}
void solve(){
    long long n;
    cin >> n;
    long long l, r;
    cin >> l >> r;
    v.resize(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    long long x = 0;
    //return;
    cout << (find_ans(r) - find_ans(l - 1))/2 << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while(q--){
        solve();
        //cout << x << endl;
    }
}
