#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
struct solve{
    void read(){
        vector<pair<long long, long long>> v;
        long long n, p;
        cin >> n >> p;
        vector<long long> inp(n);
        for(int i = 0; i < n; i++){
            cin >> inp[i];
            v.push_back({inp[i], i});
        }
        sort(v.begin(), v.end());
        vector<bool> isConnected(n); //is i and i + 1 connected
        for(int i = 0; i < n; i++){
            isConnected[i] = false;
        }
        long long cntr = p * (n - 1);
        for(int i = 0; i < n; i++){
            int ind = v[i].second;
            long long val = v[i].first;
            if(val >= p) break;
            if(isConnected[ind]) continue;
            isConnected[ind] = true;
            for(int j = ind - 1; j >= 0; j--){
                if(inp[j] % val != 0){
                    break;
                }
                cntr -= p - val;
                if(isConnected[j]){
                    break;
                }
                isConnected[j] = true;
            }
            for(int j = ind + 1; j < n; j++){
                if(inp[j] % val != 0){
                    break;
                }
                cntr -= p - val;
                if(isConnected[j]){
                    break;
                }
                isConnected[j] = true;
            }
 
        }
        cout << cntr << endl;
    }
};
 
int main(){
    int t;
    cin >> t;
    while(t--){
        solve s;
        s.read();
    }
}
