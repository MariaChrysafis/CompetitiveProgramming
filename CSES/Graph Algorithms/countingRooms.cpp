#include <iostream>
#define maxN 1000
#define maxM 1000
using namespace std;
int n;
int m;
char arr[maxN][maxM];
bool hasVisited[maxN][maxM];
int d[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
bool inBounds(int x, int y){
    return (x >= 0 && y >= 0 && x < n && y < m);
}
void DFS(int x, int y){
    hasVisited[x][y] = true;
    for(int i = 0; i < 4; i++){
        int new_x = x + d[i][0];
        int new_y = y + d[i][1];
        if(new_x < 0 || new_y < 0 || new_x >= n || new_y >= m){
            continue;
        }
        if(hasVisited[new_x][new_y]){
            continue;
        }
        if(arr[new_x][new_y] == '#'){
            continue;
        }
        DFS(new_x,new_y);
    }
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }
    int cntr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(hasVisited[i][j] || arr[i][j] == '#') continue;
            DFS(i,j);
            cntr++;
        }
    }
    cout << cntr << endl;
}
