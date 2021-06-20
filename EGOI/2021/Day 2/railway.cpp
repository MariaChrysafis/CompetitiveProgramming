#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const long long INF = 1000000000000000000;
vector<pair<long long,long long>> tunnels;
vector<long long> z, l;
long long s, t, m, n;
long long distance(long long t0, long long t1){
    /*
     * t0 - zurich
     * t1 - lugano
     */
    long long ans = (s + t1 - t0)/2;
    if(ans < 0 || ans > s) return -1;
    else return ans;
}
bool on_tunnel(long long x){
    for(pair<long long, long long> p: tunnels){
        if(x > p.first && x < p.second) return true;
    }
    return false;
}
bool inside(pair<long long, long long> p, long long x){
    return (x > p.first && x < p.second);
}
char lr(pair<long long, long long> p, long long x){
    if(x <= p.first) return 'L';
    else return 'R';
}
long long binSearch(long long left, long long right, long long x){
    //cout << left << " " << right << endl;
    if(left > right){
        return -1;
    }
    if(left == right) {
        return left;
    }
    long long mid = (left + right + 1)/2;
    if(2 * tunnels[mid].first >= x){
        return binSearch(left, mid - 1, x);
    }else{
        return binSearch(mid, right, x);
    }
}
int main(){
    cin >> s >> t >> m >> n;
    tunnels.resize(t);
    for(int i = 0; i < t; i++){
        cin >> tunnels[i].first;
    }
    for(int i = 0; i < t; i++){
        cin >> tunnels[i].second;
    }
    sort(tunnels.begin(), tunnels.end());
    z.resize(m), l.resize(n);
    for(int i = 0; i < m; i++){
        cin >> z[i];
    }
    for(int i = 0; i < n; i++){
        cin >> l[i];
    }
    bool b = false;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            long long zurich = z[i]; /* time at which they leave */
            long long lugano = l[j]; /* time at which they leave */
            int ans = lugano - zurich + s;
            if(ans == -1) continue;
            int x = binSearch(0, tunnels.size() - 1, ans);
            //cout << x << endl;
            if(x != -1 && ans < 2 * tunnels[x].second && ans > 2 * tunnels[x].first){
                //cout << x << endl;
                b = true;
                break;
            }
        }
    }
    if(b){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}
