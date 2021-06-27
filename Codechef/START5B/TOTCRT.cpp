#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        long long n;
        cin >> n;
        map<string,long long> myMap;
        for(int i = 0; i < n * 3; i++){
            string s;
            cin >> s;
            long long x;
            cin >> x;
            myMap[s] += x;
        }
        vector<long long> v;
        for(pair<string, long long> p: myMap){
            v.push_back(p.second);
        }
        sort(v.begin(), v.end());
        for(long long p: v){
            cout << p << " ";
        }
        cout << '\n';
    }
}
