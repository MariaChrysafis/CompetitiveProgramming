#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;
#define P(x,y) make_pair(x,y)
using namespace std;
class Rectangle{
public:
    long long x1 , y1 , x2 , y2;
    static Rectangle empt;
    Rectangle(){
        x1=y1=x2=y2=0;
    }
    Rectangle(long long X1 , long long Y1 , long long X2 , long long Y2){
        x1 = X1; y1=Y1;
        x2 = X2; y2=Y2;
    }
    Rectangle intersect(Rectangle R){
        if(R.x1 >= x2 || R.x2 <= x1) return empt;
        if(R.y1 >= y2 || R.y2 <= y1) return empt;
        return Rectangle(max(x1 , R.x1) , max(y1 , R.y1) , min(x2 , R.x2) , min(y2 , R.y2));
    }
};
struct Event{
    long long x , y1 , y2 , type;
    Event(){}
    Event(long long x , long long y1 , long long y2 , long long type):x(x) , y1(y1) , y2(y2) , type(type){}
};
bool operator < (const Event&A , const Event&B){
    //if(A.x != B.x)
    return A.x < B.x;
    //if(A.y1 != B.y1) return A.y1 < B.y1;
    //if(A.y2 != B.y2()) A.y2 < B.y2;
}
const int MX=(1<<17);
struct Node{
    long long prob , sum , ans;
    Node(){}
    Node(long long prob , long long sum , long long ans):prob(prob) , sum(sum) , ans(ans){}
};
Node tree[MX*4];
long long interval[MX];
void build(long long x , long long a , long long b){
    tree[x] = Node(0 , 0 , 0);
    if(a==b){
        tree[x].sum+=interval[a];
        return;
    }
    build(x*2 , a , (a+b)/2);
    build(x*2+1 , (a+b)/2+1 , b);
    tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
}
long long ask(long long x){
    if(tree[x].prob) return tree[x].sum;
    return tree[x].ans;
}
long long st , en , V;
void update(long long x , long long a, long long b){
    if(st>b || en<a) return;
    if(a>=st && b<=en){
        tree[x].prob+=V;
        return;
    }
    update(x*2 , a , (a+b)/2);
    update(x*2+1 , (a+b)/2+1 , b);
    tree[x].ans = ask(x*2) + ask(x*2+1);
}
Rectangle Rectangle::empt = Rectangle();
vector < Rectangle > Rect;
vector < long long > sorted;
vector < Event > sweep;
void compressncalc(){
    sweep.clear();
    sorted.clear();
    for(auto R : Rect){
        sorted.push_back(R.y1);
        sorted.push_back(R.y2);
    }
    sort(sorted.begin() , sorted.end());
    sorted.erase(unique(sorted.begin() , sorted.end()) , sorted.end());
    int sz = sorted.size();
    for(int j=0;j<sorted.size() - 1;j++)
        interval[j+1] = sorted[j+1] - sorted[j];
    for(auto R : Rect){
        sweep.push_back(Event(R.x1 , R.y1 , R.y2 , 1));
        sweep.push_back(Event(R.x2 , R.y1 , R.y2 , -1));
    }
    sort(sweep.begin() , sweep.end());
    build(1,1,sz-1);
}
long long ans;
void Sweep(){
    ans=0;
    if(sorted.empty() || sweep.empty()) return;
    long long last = 0 , sz_ = sorted.size();
    for(int j=0;j<sweep.size();j++){
        ans+= 1ll * (sweep[j].x - last) * ask(1);
        last = sweep[j].x;
        V = sweep[j].type;
        st = lower_bound(sorted.begin() , sorted.end() , sweep[j].y1) - sorted.begin() + 1;
        en = lower_bound(sorted.begin() , sorted.end() , sweep[j].y2) - sorted.begin();
        update(1 , 1 , sz_-1);
    }
}
vector<Rectangle> orig;
long long n, m;
bool isValid(long long delta){
    vector<Rectangle> vec;
    for (int i = 0; i < m; i++) {
        long long x1 = max(Rect[i].x1 - delta, 0ll);
        long long x2 = min(Rect[i].x2 + delta, n);
        long long y1 = max(Rect[i].y1 - delta, 0ll);
        long long y2 = min(Rect[i].y2 + delta, n);
        vec.push_back(Rectangle(x1, y1, x2, y2));
    }
    Rect = vec;
    compressncalc();
    Sweep();
    Rect = orig;
    return (ans == n * n);
}
long long binSearch(long long l, long long r){
    long long mid = (l + r)/2;
    if(l == r) return mid;
    if(isValid(mid)){
        return binSearch(l, mid);
    }else{
        return binSearch(mid + 1, r);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    //orig.resize(m);
    cin >> m;
    for(int i = 0; i < m; i++){
        long long a, b;
        cin >> a >> b;
        a--, b--;
        Rect.push_back(Rectangle(a, b, a + 1, b + 1));
    }
    orig = Rect;
    cout << binSearch(0, n + m);
}
