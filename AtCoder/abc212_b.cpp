#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#define ll long long
using namespace std;
int main() {
    string s;
    cin >> s;
    set<char> mySet;
    for(int i = 0; i < s.length(); i++){
        mySet.insert(s[i]);
    }
    if(mySet.size() == 1){
        cout << "Weak";
        return 0;
    }
    int cntr = 0;
    for(int i = 1; i < s.length(); i++){
        if(s[i] - '0' == (s[i - 1] - '0' + 1) % 10){
            cntr++;
        }
    }
    if(cntr == 3){
        cout << "Weak";
    }else{
        cout << "Strong";
    }
}
