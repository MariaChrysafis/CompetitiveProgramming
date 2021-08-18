#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> v;
    for(int i = 0; i < 2000; i++){
        if(i % 3 == 0) continue;
        string s = to_string(i);
        if(s[s.length() - 1] == '3') continue;
        v.push_back(i);
    }
    int t;
    cin >> t;
    while(t--){
        int x;
        cin >> x;
        cout << v[x - 1] << endl;
    }
}
