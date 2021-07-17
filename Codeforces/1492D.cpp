#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
vector<bool> addBinary(vector<bool> a, vector<bool> b){
    vector<bool> result;
    int s = 0;
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        if(i >= 0) s += a[i];
        if(j >= 0) s += b[j];
        result.push_back(s % 2);
        s /= 2;
        i--; j--;
    }
    reverse(result.begin(), result.end());
    return result;
}
bool same(vector<bool> s1, vector<bool> s2){
    if(s1.size() != s2.size()) return false;
    int a = 0;
    int b = 0;
    for(int i = 0; i < s1.size(); i++){
        if(s1[i] == 0) a++;
        if(s2[i] == 0) b++;
    }
    return (a == b);
}
void print(vector<bool> v){
    for(bool b: v) cout << b;
    cout << endl;
}
void solve(int a, int b, int k) {
    if(k >= a + b){
        cout << "No" << endl;
        return;
    }
    vector<bool> s1;
    if(b - k > 0) {
        for (int i = 0; i < b - k; i++) {
            s1.push_back(1);
        }
        for (int i = 0; i < a; i++) {
            s1.push_back(0);
        }
        for (int i = 0; i < k; i++) {
            s1.push_back(1);
        }
    }else{
        s1.push_back(1);
        for(int i = 0; i < a; i++){
            s1.push_back(0);
        }
        for(int i = 0; i < b - 1; i++){
            s1.push_back(1);
        }
    }
    vector<bool> s2;
    for(int i = 0; i < a + b - k; i++){
        s2.push_back(0);
    }
    for(int i = 0; i < k; i++){
        s2.push_back(1);
    }
    vector<bool> s3 = addBinary(s1, s2);
    //print(s1), print(s2);
    if(!same(s1, s3)){
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    print(s3), print(s1);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b, k;
    cin >> a >> b >> k;
    solve(a, b, k);
}
