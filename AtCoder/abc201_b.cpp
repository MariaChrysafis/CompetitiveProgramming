#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<pair<int,string>> v;
    for(int i = 0; i < n; i++){
        string s1;
        cin >> s1;
        int n1;
        cin >> n1;
        v.push_back(make_pair(n1,s1));
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    cout << v[1].second << endl;
}
