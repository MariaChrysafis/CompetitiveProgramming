#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <map>
#define ll long long
using namespace std;
 
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int prefA[s.length() + 1];
    int prefB[s.length() + 1];
    prefA[0] = prefB[0] = 0;
    for(int i = 0; i < s.length(); i++){
        prefA[i + 1] = prefA[i] + (s[i] == 'a');
        prefB[i + 1] = prefB[i] + (s[i] == 'b');
    }
    for(int i = 0; i < s.length(); i++){
        for(int j = i + 1; j < s.length(); j++){
            if(prefA[j + 1] - prefA[i] == prefB[j + 1] - prefB[i]){
                cout << i + 1 << " " << j + 1 << endl;
                return;
            }
        }
    }
    cout << "-1 -1\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto start = std::chrono::high_resolution_clock::now();
    int T;
    cin >> T;
    while(T--){
        solve();
    }
 
}
