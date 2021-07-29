#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
 
#define ll long long
#define endl '\n'
 
using namespace std;
void solve(){
    set<string> s;
    string s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    s.insert(s1), s.insert(s2), s.insert(s3), s.insert(s4);
    if(s.count("H") && s.count("2B") && s.count("3B") && s.count("HR")){
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }
}
 
int main() {
    solve();
}
