#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define ll unsigned long long int
void solve(bool b){
    vector<long long> v;
    long long n, w;
    cin >> n >> w;
    v.resize(n);
    map<int,int> oc;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        oc[v[i]]++;
    }
    for(int x = 0; x < n * n * 2; x++){
        long long cur = 0;
        for(long long i = 524288; i >= 1; i /= 2){
            while(cur + i <= w && oc[i] >= 1){
                cur += i;
                oc[i]--;
                //cout << i << " ";
            }
        }
        //cout << endl;
        if(cur == 0){
            cout << x << endl;
            break;
        }
        //cout << cur << endl;
    }
}
int main(){
    int t;
    cin >> t;
    int x = 0;
    while(t--){
        x++;
        bool b = false;
        //if(x == 133) b = true;
        solve(b);
    }
}
