class Solution {
    public static class MergeSort1 {
        int[] arr;

        public MergeSort1(int[] arr) {
            this.arr = arr;
        }

        int[] merge(int l1, int r1, int l2, int r2) {
            //System.out.println(l1 +  " " + r1 + " " + l2 + " " + r2);
            int cur1 = l1;
            int cur2 = l2;
            int[] new_arr = new int[r2 - l1 + 1];
            int cntr = 0;
            while(!(cur1 == r1 + 1 && cur2 == r2 + 1)){
                if(cur1 == r1 + 1) {
                    new_arr[cntr] = arr[cur2];
                    cur2++;
                }else if(cur2 == r2 + 1) {
                    new_arr[cntr] = arr[cur1];
                    cur1++;
                }else if(arr[cur1] < arr[cur2]) {
                    new_arr[cntr] = arr[cur1];
                    cur1++;
                }else if(arr[cur2] <= arr[cur1]) {
                    new_arr[cntr] = arr[cur2];
                    cur2++;
                }
                cntr++;
            }
            for(int i = 0; i < new_arr.length; i++) {
                arr[l1 + i] = new_arr[i];
            }
            return new_arr;
        }

        int[] sort(int l, int r) {
            if(l == r) {
                int[] dummy = new int[1];
                dummy[0] = arr[l];
                return dummy;
            }
            int m = (l + r)/2;
            sort(l, m);
            sort(m + 1, r);
            return merge(l, m, m + 1, r);
        }

        public int[] getArr() {
            return arr;
        }

        public void setArr(int[] arr) {
            this.arr = arr;
        }
    }
    public int[] rearrangeArray(int[] nums) {
        MergeSort1 ms = new MergeSort1(nums); nums = ms.sort(0, nums.length - 1);
        int[] nums1 = new int[(nums.length + 1)/2];
        int[] nums2 = new int[nums.length/2];
        for(int i = 0; i < (nums.length + 1)/2; i++) {
            nums1[i] = nums[i];
        }
        for(int i = 0; i < nums.length/2; i++) {
            nums2[i] = nums[i + (nums.length + 1)/2];
        }
        for (int i = 0; i < nums.length; i++) {
            if (i % 2 == 0) {
                nums[i] = nums1[i / 2];
            } else {
                nums[i] = nums2[i / 2];
            }
        }
        return nums;
    }
}
