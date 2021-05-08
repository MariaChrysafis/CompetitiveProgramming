struct tree{
    vector<vector<int>> adj;
    vector<int> dist(int src){
        vector<int> v(adj.size());
        for(int i = 0; i < adj.size(); i++){
            v[i] = -1;
        }
        v[src] = 0;
        queue<pair<int,int>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            pair<int,int> p = pq.front();
            pq.pop();
            for(int i: adj[p.second]){
                if(v[i] == -1){
                    pq.push(make_pair(p.first + 1, i));
                    v[i] = p.first + 1;
                }
            }
        }
        return v;
    }
    int pnt(int A){
        vector<int> v = dist(A);
        int myMax = 0;
        int ind = 0;
        for(int i = 0; i < v.size(); i++){
            if(v[i] > myMax){
                ind = i;
                myMax = v[i];
            }
        }
        return ind;
    }
    int diameter(){
        return dist(pnt(pnt(0)))[pnt(0)];
    }
};
