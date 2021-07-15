#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << ' ';
    }
    cout << endl;
}
int maxOfVector(vector<int> v){
    int myMax = 0;
    for(int i: v){
        myMax = max(myMax, i);
    }
    return myMax;
}
void solve(){
    string s;
    cin >> s;
    int m;
    cin >> m;
    int arr[m];
    for(int i = 0; i < m; i++){
        cin >> arr[i];
    }
    map<char,int> oc;
    for(int i = 0; i < s.length(); i++){
        oc[s[i]]++;
    }
    bool marked[m];
    vector<int> order(m);
    for(int i = 0; i < m; i++) marked[i] = false;
    for(int dum = 0; dum < m; dum++){
        int cntr = 0;
        vector<int> v;
        for(int i = 0; i < m; i++){
            if(arr[i] == 0){
                cntr++;
                v.push_back(i);
                order[i] = dum;
            }
        }
        for(int i: v){
            marked[i] = true;
        }
        for(int i = 0; i < m; i++){
            if(marked[i]) continue;
            for(int j: v){
                arr[i] -= abs(i - j);
            }
        }
        for(int j: v){
            arr[j] = -1;
        }
    }
    //print(order);
    map<int,int> myMap;
    int myMax = maxOfVector(order);
    for(int i = 0; i < order.size(); i++){
        order[i] = myMax - order[i];
        myMap[order[i]]++;
    }
    vector<pair<int,int>> v;
    for(pair<int,int> p: myMap){
        v.push_back(p);
    }
    //print(order);
    int ind = 0;
    map<int,char> mm;
    for(int i = 0; i < v.size(); i++){
        while(v[i].second > oc['a' + ind]){
            ind++;
        }
        //cout << ind << " ";
        mm[i] = 'a' + ind;
        ind++;
    }
    //cout << order.size() << endl;
    for(int i = 0; i < order.size(); i++){
        cout << mm[order[i]];
    }
    cout << endl;
    //print(order);
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
