class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int oc[2 * limit + 2];
        for(int i = 0; i < 2 * limit + 2; i++){
            oc[i] = 0;
        }
        for(int i = 0; i < nums.size()/2; i++){
            oc[nums[i] + nums[nums.size() - i - 1]]++;
        }
        int arr1[2 * limit + 2]; /* how many will need 1 */
        int arr2[2 * limit + 2]; /* how many will need 2*/
        for(int i = 0; i < 2 * limit + 1; i++) arr1[i] = arr2[i] = 0;
        for(int i = 0; i < nums.size()/2; i++){
            long long x = nums[i];
            long long y = nums[nums.size() - i - 1];
            arr1[min(x,y) + 1] ++;
            arr2[max(x,y) + limit + 1]++;
        }
        int x = 0;
        int myMax = 1000000;
        int need1 = 0;
        for(int i = 0; i < 2 * limit + 1; i++){
            need1 += arr1[i] - arr2[i];
            int need2 = nums.size()/2 - need1;
            long long a = need1 + 2 * need2 - oc[i];
            if(myMax > a) myMax = a;
        }
        return myMax;
    }
};
