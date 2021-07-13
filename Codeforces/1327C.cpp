#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
string reverse(string s){
    reverse(s.begin(), s.end());
    string str;
    for(char c: s){
        if(c == 'L') str += 'R';
        else if(c == 'R') str += 'L';
        else if(c == 'U') str += 'D';
        else str += 'U';
    }
    return str;
}
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    swap(n, m);
    string l;
    for(int i = 0; i < n - 1; i++){
        l += 'L';
    }
    string r;
    for(int i = 0; i < n - 1; i++){
        r += 'R';
    }
    string ans;
    for(int i = 0; i < m; i++){
        if(i % 2 == 0){
            ans += l;
        }else{
            ans += r;
        }
        ans += 'D';
    }
    ans += reverse(ans);
    cout << ans.size() << endl;
    cout << ans << endl;
}
