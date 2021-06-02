#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <map>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
const int INT = 65;
int SHUFFLE = 4;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, p;
    cin >> n >> m >> p;
    vector<int64_t> arr(n);
    for (int i = 0; i < n; i++){
        arr[i] = 0;
    }
    vector<vector<char>> inp;
    inp.resize(n);
    cout << endl;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        inp[i].resize(m);
        for(int j = 0; j < m; j++){
            inp[i][j] = s[j];
        }
    }
    vector<int> del;
    for(int j = 0; j < m; j++){
        int cntr = 0;
        for(int p = 0; p < n; p++){
            if(inp[p][j] == '1') cntr++;
        }
        if(cntr >= (n + 1)/2){
            del.push_back(j);
        }
    }
    for (int i = 0; i < n; i++){
        for(int j: del){
            if(inp[i][j] == '1'){
                arr[i] ^= (1ll << j);
            }
        }
    }
    sort(arr.begin(), arr.end());
    bitset<INT> myMax = 0;
    bitset<INT> l, b;
    int r;
    while (SHUFFLE--) {
        random_shuffle(arr.begin(), arr.end());
        unordered_map <bitset<INT>, int> oc;
        unordered_map <bitset<INT>, int> oc1;
        for (int64_t x: arr){
            oc[x & arr[0]]++;
        }
        for (pair<bitset<INT>,int> p: oc){
            l = p.first;
            r = p.second;
            b = l;
            while (b != 0){
                oc1[b] += r;
                long long diff = b.to_ullong() - 1;
                std::bitset<INT> result( diff );
                b = result & l;
            }
        }
        for (pair<bitset<INT>,int> p: oc1){
            if(p.second >= (n + 1)/2){
                if(p.first.count() > myMax.count()){
                    myMax = p.first;
                }
            }
        }
    }
    for(int i = 0; i < m; i++){
        cout << myMax[i];
    }
}
