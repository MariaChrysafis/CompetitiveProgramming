#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cassert>
using namespace std;
int conv (string s) {
    return (s[0] - '0') * 10 + (s[1] - '0');
}
int convert (string s) {
    int hours = conv(s.substr(0, 2));
    int minutes = conv(s.substr(3, 2));
    return 60 * hours + minutes;
}
string toString (int x) {
    if (x >= 10) {
        return to_string(x);
    }
    else return "0" + to_string(x);
}
string converter (int x) {
    int hours = x/60;
    int minutes = x % 60;
    return toString(hours) + ":" +  toString(minutes);
}
int main() {
    string s, t;
    cin >> s >> t;
    //cout << convert("10:00");
    int x = convert(s);
    int y = convert(t);
    int mid = (x + y)/2;
    cout << converter(mid) << endl;
    
}
