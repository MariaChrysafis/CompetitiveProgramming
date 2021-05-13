#include <iostream>
#include <vector>
#define ll long long
using namespace std;
ll find_sum(vector<ll> v){
    ll sum = 0;
    for(ll x: v){
        sum += x;
        sum %= 200;
    }
    return sum;
}
int n;
vector<ll> arr;
vector<string> vec;
void rec(string s, int len){
    if(s.length() == len){
        vec.push_back(s);
        return;
    }
    rec(s + '1', len);
    rec(s + '2', len);
    rec(s + '0', len);
}
bool valid(string s){
    vector<ll> v1, v2;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '1'){
            v1.push_back(arr[i]);
        }else if(s[i] == '2'){
            v2.push_back(arr[i]);
        }
    }
    if(v1.size() == 0 || v2.size() == 0) return false;
    return (find_sum(v1) == find_sum(v2));
}
void print(string s){
    vector<ll> v1, v2;
    for(int i = 0; i < s.length(); i++){
        char c = s[i];
        if(c == '1') v1.push_back(i + 1);
        else if(c == '2') v2.push_back(i + 1);
    }
    cout << "YES" << endl;
    cout << v1.size() << " ";
    for(int i: v1) cout << i << " ";
    cout << endl;
    cout << v2.size() << " ";
    for(int i: v2) cout << i << " ";
    cout << endl;
}
int main(){
    int n;
    cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        arr[i] %= 200;
    }
    rec("", min(n, 15));
    for(string s: vec){
        if(valid(s)){
            //cout << "YES" << endl;
            print(s);
            return 0;
        }
    }
    cout << "NO" << endl;
}
