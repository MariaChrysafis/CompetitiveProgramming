#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--){
        long long x;
        cin >> x;
        if(x % 2050 != 0){
            cout << -1 << '\n';
        }else{
            string s = to_string(x/2050);
            int sum = 0;
            for(char c: s){
                sum += c - '0';
            }
            cout << sum << '\n';
        }
    }
}
