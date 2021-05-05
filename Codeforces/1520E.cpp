#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#define ll long long
using namespace std;
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> pos;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '*'){
            pos.push_back(i);
        }
    }
    for(int i = 0; i < pos.size(); i++){
        pos[i] -= i;
        //cout << pos[i] << " ";
    }
    //cout << endl;
    ll curSum = 0;
    map<int,int> myMap;
    for(int i = 0; i < pos.size(); i++){
        curSum += abs(pos[i] + 1);
        myMap[pos[i]]++;
    }
    int l = pos.size();
    int r = 0;
    //cout << curSum << endl;
    ll myMin = pow(10,12);
    for(int i = 0; i < n; i++){
        curSum += (r - l);
        l -= myMap[i];
        r += myMap[i];
        myMin = min(myMin, curSum);
    }
    cout << myMin << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
