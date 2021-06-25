#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int j, len = 1;
    for(int i = 1; i < n; i++){
        if(s[j] < s[i]){
            break;
        }
        if(s[j] > s[i]){
            len = i + 1;
            j = 0;
            continue;
        }
        j++;
        j %= len;
    }
    for(int i = 0; i < k; i++){
        cout << s[i % len];
    }
}
