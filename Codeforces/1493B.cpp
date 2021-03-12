#include <iostream>
#include <string>
using namespace std;
int stoi(char c){
    return c - '0';
}
int valid(char c){
    //what digit will it reflect?
    if(c == '0'){
        return 0;
    }
    if(c == '1'){
        return 1;
    }
    if(c == '2'){
        return 5;
    }
    if(c == '3'){
        return -1;
    }
    if(c == '4'){
        return -1;
    }
    if(c == '5'){
        return 2;
    }
    if(c == '6'){
        return -1;
    }
    if(c == '7'){
        return -1;
    }
    if(c == '8'){
        return 8;
    }
    if(c == '9'){
        return 9;
    }
    return -1;
}
bool valid(string s, int h, int m){
    int d1, d2, d3, d4;
    d1 = valid(s[0]), d2 = valid(s[1]), d3 = valid(s[3]), d4 = valid(s[4]);
    if(d1 < 0 || d2 < 0 || d3 < 0 || d4 < 0){
        return false;
    }
    int x = d4 * 10 + d3;
    int y = d2 * 10 + d1;
    //swap(x, y);
    if(x >= h){
        return false;
    }
    if(y >= m){
        return false;
    }
    return true;
}
string tostring(int x){
    if(x >= 10){
        return to_string(x);
    }else{
        return "0" + to_string(x);
    }
}
string nxt(string s, int h, int m){
    int d1, d2, d3, d4;
    d1 = stoi(s[0]), d2 = stoi(s[1]);
    d3 = stoi(s[3]), d4 = stoi(s[4]);
    int x = 10 * d1 + d2;
    int y = 10 * d3 + d4;
    if(x + 1 == h && y + 1 == m){
        return "00:00";
    }
    if(y + 1 == m){
        return tostring(x + 1) + ":00";
    }
    return tostring(x) + ":" + tostring(y + 1);
}
void solve(){
    int h, m;
    cin >> h >> m;
    string s;
    cin >> s;
    //cout << nxt("12:59", 24, 60) << endl;
    //cout << valid("00:00", 24, 60) << endl;
    //return;
    int large = 10000;
    int cntr = 0;
    while(large--){
        if(valid(s, h, m)){
            cout << s << endl;
            return;
        }
        s = nxt(s, h , m);
        //cout << s << endl;
    }
    //cout << "NOT FOUND" << endl;
    return;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
