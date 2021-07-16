#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;
 
int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, int> oc;
    for (int i = 0; i < s.length(); i++) {
        oc[s[i]]++;
    }
    string ans = "No";
    if(s.length() == 1) {
        ans = "Yes";
    }
    for (pair<char, int> p: oc) {
        if (p.second >= 2) {
            ans = "Yes";
        }
    }
    cout << ans << '\n';
}
