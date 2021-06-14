#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
#include <set>
using namespace std;
const int INF = 1000000000;
void print(char c){
    cout << c << '\n';
}
void solve(int a, int b){
    if(a > b){
        print('>');
    }else if(a == b){
        print('=');
    }else if(a < b){
        print('<');
    }
}
int main(){
    int a, b, c;
    cin >> a >> b >> c;
    if(c % 2 == 0){
        a = abs(a);
        b = abs(b);
        solve(a,b);
    }else{
        solve(a,b);
    }
}
