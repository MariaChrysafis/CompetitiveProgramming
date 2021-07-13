#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
const int MAX = 2e5 + 7;
int main() {
    int n, k;
    cin >> n >> k;
    map<int,vector<pair<int,int>>> myMap;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        myMap[l].push_back(make_pair(r, i));
    }
    set<pair<int,int>> s;
    vector<int> v;
    for(int i = 0; i < MAX; i++){
        while(!s.empty() && s.begin()->first < i){
            s.erase(s.begin());
        }
        for(pair<int,int> q: myMap[i]){
            s.insert(q);
        }
        while(s.size() > k){
            auto it = s.end();
            it--;
            v.push_back((*it).second);
            s.erase(it);
        }
    }
    sort(v.begin(), v.end());
    cout << v.size() << endl;
    for(int i: v){
        cout << i + 1 << " ";
    }
    cout << endl;
}
