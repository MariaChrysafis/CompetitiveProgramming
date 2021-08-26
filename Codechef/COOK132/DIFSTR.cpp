#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

#define ll long long
using namespace std;
#define P(x, y) make_pair(x,y)
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
vector<string> v;
void rec1(string s, int des){
    if(v.size() >= des + 1){
        return;
    }
    if(s.length() == des){
        v.push_back(s);
        return;
    }
    rec1(s + '1', des), rec1(s + '0', des);
}
string solve(){
    v.clear();
    int n;
    cin >> n;
    vector<string> inp(n);
    map<string,bool> oc;
    for(int i = 0; i < n; i++) {
        cin >> inp[i];
        oc[inp[i]] = true;
    }
        rec1("", n);
        for(string s: v){
            if(!oc[s]){
                return s;
            }
        }

}
int main() {
    int t;
    cin >> t;
    while(t--){
        string s = solve();
        cout << s << endl;
    }
}
