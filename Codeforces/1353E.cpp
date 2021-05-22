#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int specCase(string s){
   int sum = 0;
   for(char c: s) sum += (c == '1');
   int cur = 0;
   int ans = 1e9;
   for(char c: s){
       if(c == '1') cur++;
       else cur--;
       if(cur < 0) cur = 0;
       ans = min(ans, sum - cur);
   }
   return ans;
}
void solve(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<string> v(k);
    vector<int> O(k);
    vector<int> Z(k);
    int o = 0;
    int z = 0;
    for(int i = 0; i < n; i++){
        v[i % k] += s[i];
        if(s[i] == '1') o++, O[i % k]++;
        else z++, Z[i % k]++;
    }
    int myMin = 1e9;
    for(int i = 0; i < k; i++){
        int ans = specCase(v[i]);
        ans += o - O[i % k]; 
        myMin = min(ans, myMin);
    }
    cout << myMin << endl;
}
int main(){
    int t;
    cin >> t;
    int tc = 0;
    while(t--){
         solve();
    }
}
