#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
void printsp(vector<int> v){
    for(int i: v) cout << 1 << " " << i + 1 << '\n';
    cout << endl;
}
void print(vector<int> v){
    cout << v.size() << " ";
    for(int i: v) cout << i + 1 << " ";
    cout << '\n';
}
void solve(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    string cur = s;
    vector<vector<int>> v;
    int sz = 0;
    int cntr = 0;
    while(cur.find("RL") != std::string::npos){
        v.push_back({});
        for(int i = 0; i < cur.length() - 1; i++){
            if(cur[i] == 'R' && cur[i + 1] == 'L'){
                cur[i] = 'L', cur[i + 1] = 'R';
                v[sz].push_back(i);
                cntr++;
                i++;
            }
        }
        sz++;
    }
    if(k > cntr || k < v.size()){
        cout << "-1\n";
        return;
    }
    for(int i = 0; i < v.size(); i++){
        int rem = v.size() - i - 1;
        if(k - v[i].size() >= rem){
            k -= v[i].size();
            printsp(v[i]);
        }else{
            k--;
            print(v[i]);
        }
    }
    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
 
 
}
