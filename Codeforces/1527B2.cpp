#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool isPalindrome(string s){
    string str = s;
    reverse(s.begin(), s.end());
    return (str == s);
}
void solve(int x, int orig) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int zero = 0;
    for(auto it: s){
        zero += (it == '0');
    }
    if(isPalindrome(s)){
        if(zero == 1 || zero % 2 == 0){
            cout << "BOB \n";
        }else{
            cout << "ALICE \n";
        }
        return;
    }
    if(zero == 2 && s.length() % 2 == 1 && s[(s.length() - 1)/2] == '0'){
        cout << "DRAW\n";
    }else{
        cout << "ALICE\n";
    }
}
int main() {
    int t;
    cin >> t;
    int x = 1;
    int orig = t;
    while (t--) {
        solve(x, orig);
        x++;
    }
}
