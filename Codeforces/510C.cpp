#include <iostream>
#define maxN 101
using namespace std;
string arr[maxN];
bool adj[26][26];
int n;
int deg[maxN];
bool flag[maxN];
void init_adj(){
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            adj[i][j] = false;
        }
    }
}
int char_to_int(char c){
    return (int)c - 97;
}
char int_to_char(int x){
    for(char c = 'a'; c <= 'z'; c++){
        if(char_to_int(c) == x) return c;
    }
    return 0;
}
bool flagger = false;
void comp(string s, string s1){
    for(int i = 0; i < min(s.length(),s1.length()); i++){
        if(s[i] != s1[i]){
            int x = char_to_int(s[i]);
            int y = char_to_int(s1[i]);
            adj[x][y] = true;
            return;
        }
    }
    if(s != s1 && s.length() > s1.length()) flagger = true;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            comp(arr[i],arr[j]);
        }
    }
    for(int i = 0; i < 26; i++){
        deg[i] = 0;
        for(int j = 0; j < 26; j++){
            deg[i] += adj[j][i];
        }
    }
    if(flagger){ cout << "Impossible" << endl; return 0;}
    int cntr = 0;
    int cntr2 = 0;
    string s = "";
    while(cntr < 26){
        for(int i = 0; i < 26; i++){
            if(deg[i] == 0 && flag[i] == false){
                flag[i] = true;
                for(int j = 0; j < 26; j++){
                    if(adj[i][j]){
                        deg[j]--;
                    }
                }
                s += int_to_char(i);
                cntr++;
                continue;
            }
        }
        cntr2++;
        if(cntr2 == 50){
            cout << "Impossible" << endl;
            return 0;
        }
    }
    cout << s << endl;
}
