#include <iostream>
#include <vector>
#include <algorithm>
 
using ll = long long;
const int N = 2e6 + 5;
using namespace std;
 
struct info
{
    int minimum=0 ;
    int lazy=0;
};
info t[N*4];
struct lazy_segtree
{
    int n;
    lazy_segtree(int n)
    {
        this->n = n;
    }
    void Merge(info &node, info &l, info &r)
    {
        node.minimum = min(l.minimum,r.minimum);
    }
    void push_down(int node, int  l, int r)
    {
        if(t[node].lazy)
        {
            t[l].minimum+= t[node].lazy;
            t[r].minimum += t[node].lazy;
            t[l].lazy+= t[node].lazy;
            t[r].lazy+= t[node].lazy;
            t[node].lazy =0;
        }
    }
    void update(int node, int l,int r, int i, int j, int add)
    {
        if(l>j || r<i)
        {
            return;
        }
        if(l>=i && r<=j)
        {
            t[node].minimum+= add;
            t[node].lazy+=add;
            return;
        }
        push_down(node, node*2, node*2+1);
        int mid = (l+r)/2;
        update(node *2, l,mid, i, j, add);
        update(node *2 +1, mid+1, r, i, j, add);
        Merge(t[node], t[node *2], t[node*2+1]);
    }
    void update(int l,int r, int add)
    {
        if(l>r)
            return;
        update(1,1,n,l,r,add);
    }
    int query(int node, int l, int r, int i, int j)
    {
        if(l>j || r<i)
        {
            return 2e9;
        }
        if(l>=i && r<=j)
        {
            return t[node].minimum;
        }
        push_down(node, node*2, node*2+1);
        int mid = (l+r)/2;
        return min( query(node *2, l,mid, i, j),query(node *2 +1, mid+1, r, i, j)) ;
    }
    int query(int l, int r)
    {
        return query(1,1,n,l,r);
    }
};
 
struct segment {
    int l, r, weight;
};
vector<segment> v;
 
bool comp(segment s1, segment s2) {
    return (s1.weight < s2.weight);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    lazy_segtree st(2 * m + 4);
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].l >> v[i].r >> v[i].weight;
        v[i].l *= 2;
        v[i].r *= 2;
    }
    sort(v.begin(), v.end(), comp);
    int myMin = 1e9;
    int l = 0;
    int r = -1;
    while(l < n){
        bool valid = true;
        while(st.query(2, 2 * m) == 0){
            r++;
            if(r == n){
                valid = false;
                break;
            }
            st.update(v[r].l, v[r].r,1);
        }
        if(!valid){
            break;
        }
        st.update(v[l].l, v[l].r,-1);
        myMin = min(myMin, v[r].weight - v[l].weight);
        l++;
    }
    cout << myMin << endl;
    return 0;
}
