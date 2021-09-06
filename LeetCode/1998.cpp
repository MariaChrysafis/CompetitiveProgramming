class Solution {
public:
    const static int MAX = 1e5 + 10;
    vector<int> oc[MAX];
    int connectedComponent[MAX];
    int comp;
    vector<int> adj[MAX];
    void dfs(int x){
        connectedComponent[x] = comp;
        for(int i: adj[x]){
            if(!connectedComponent[i]){
                dfs(i);
            }
        }
    }
    bool gcdSort(vector<int>& nums) {
        bool isPrime[(int)1e5 + 10];
        isPrime[0] = false;
        isPrime[1] = false;
        for(int i = 2; i < MAX; i++){
            isPrime[i] = true;
        }
        vector<int> primes;
        for(int i = 2; i < MAX; i++){
            if(isPrime[i]){
                for(int j = 2 * i; j < MAX; j += i){
                    isPrime[j] = false;
                }
            }
            if(isPrime[i]){
                primes.push_back(i);
            }
        }
    
        for(int i = 0; i < nums.size(); i++){
            connectedComponent[i] = 0;
            long long x = nums[i];
            int mx = sqrt(x);
            for(int j = 2; j <= mx; j++){
                if(x % j == 0){
                    oc[j].push_back(i);
                }
                while(x % j == 0){
                    x /= j;
                }
            }
            if(x != 1) oc[x].push_back(i);
        }
        for(int j: primes){
            for(int i = 1; i < oc[j].size(); i++){
                adj[oc[j][i]].push_back(oc[j][i - 1]);
                adj[oc[j][i - 1]].push_back(oc[j][i]);
            }
        }
        for(int i = 0; i < nums.size(); i++){
            if(!connectedComponent[i]){
                comp++;
                dfs(i);
            }
        }
        vector<int> orig = nums;
        sort(nums.begin(), nums.end());
        int oc[MAX];
        for(int i = 0; i < nums.size(); i++){
            oc[orig[i]] = i;
        }
        for(int i = 0; i < nums.size(); i++){
            if(connectedComponent[i] != connectedComponent[oc[nums[i]]]){
                return false;
            }
        }
        return true;
    }
};
