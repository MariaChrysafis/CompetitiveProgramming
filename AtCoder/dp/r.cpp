#include <iostream>
#include <vector>
using namespace std;
const long long MOD = 1e9 + 7;
struct modInt{
    long long x;
    modInt operator*(modInt y) const{
        return {(x * y.x) % MOD};
    }
    modInt operator+(modInt y) const{
        return {(x + y.x) % MOD};
    }
};
struct Matrix{
    vector<vector<modInt>> v;
    void print(){
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
                cout << v[i][j].x << " ";
            }
            cout << endl;
        }
    }
    static Matrix identity(int n){
        Matrix m;
        m.v.resize(n);
        for(int i = 0; i < n; i++){
            m.v[i].resize(n);
            for(int j = 0; j < n; j++){
                m.v[i][j].x = 0;
                if(i == j) m.v[i][j].x = 1;
            }
        }
        return m;
    }
    Matrix operator+(const Matrix&m) const{
        Matrix a;
        a.v.resize(m.v.size());
        for(int i = 0; i < m.v.size(); i++){
            for(int j = 0; j < m.v[i].size(); j++){
                a.v[i].push_back(m.v[i][j] + v[i][j]);
            }
        }
        return a;
    }
    Matrix operator*(const Matrix&m) const{
        Matrix ans;
        ans.v.resize(v.size());
        for(int i = 0; i < v.size(); i++) ans.v[i].resize(m.v[0].size());
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < m.v[0].size(); j++){
                for(int k = 0; k < v[0].size(); k++){
                    ans.v[i][j] = ans.v[i][j] + v[i][k] * m.v[k][j];
                }
            }
        }
        return ans;
    }
    Matrix power(long long k){
        Matrix a = (Matrix){v};
        Matrix product = Matrix::identity(a.v.size());
        while(k > 0){
            if(k % 2 == 1){
                product = product * a;
            }
            a = a * a;
            k /= 2;
        }
        return product;
    }
};
int main(){
    Matrix mat;
    long long n, m;
    cin >> n >> m;
    mat.v.resize(n);
    for(int i = 0; i < n; i++){
        mat.v[i].resize(n);
        for(int j = 0; j < n; j++){
            cin >> mat.v[i][j].x;
        }
    }
    Matrix ans = mat.power(m);
    //ans.print();
    long long cnt = 0;
    for(int i = 0; i < ans.v.size(); i++){
        for(int j = 0; j < ans.v[i].size(); j++){
            cnt += ans.v[i][j].x;
            cnt %= MOD;
        }
    }
    cout << cnt << endl;
}
