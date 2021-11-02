#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    string s;
    cin >> s;
    sort(s.begin(),s.end());
    char arr[s.length()];
    for(int i = 0; i < s.length(); i++) arr[i] = s[i];
    vector<string> v;
    do {
        string str = "";
        for(char c: arr) str += c;
        v.push_back(str);
    } while ( std::next_permutation(arr,arr+s.length()) );
    cout << v.size() << endl;
    for(string i: v) cout << i << endl;
}
