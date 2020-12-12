class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> v;
        int n = nums1.size();
        int m = nums2.size();
        int loc1 = 0;
        int loc2 = 0;
        int spec1 = -1;
        int spec2 = -1;
        if((n + m) % 2 == 0){
            spec1 = (n + m)/2;
            spec2 = (n + m)/2 - 1;
        }else{
            spec1 = (n + m - 1)/2;
        }
        double sum = 0;
        for(int i = 0; i < n + m; i++){
            bool l1 = false;
            if(loc2 == m){
                v.push_back(nums1[loc1]);
                loc1++;
                l1 = true;
            }
            else if(loc1 == n){
                v.push_back(nums2[loc2]);
                loc2++;
            }
            else if(nums1[loc1] < nums2[loc2]){
                v.push_back(nums1[loc1]);
                loc1++;
                l1 = true;
            }else{
                v.push_back(nums2[loc2]);
                loc2++;
            }
            if(i == spec1 || i == spec2){
                if(l1) sum += nums1[loc1 - 1];
                else sum += nums2[loc2 - 1];
            }
        }
        if((n + m) % 2 == 0){
            return sum/2.0;
        }else{
            return sum;
        }
    }
    
};
