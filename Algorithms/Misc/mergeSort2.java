package com.company;

import java.lang.*;

public class Main {
    public static<T> void print (char[] arr) {
        for(int i = 0; i < arr.length; i++){
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
    public static class MergeSort1 {
        char[] arr;

        public MergeSort1(char[] arr) {
            this.arr = arr;
        }

        char[] merge(int l1, int r1, int l2, int r2) {
            //System.out.println(l1 +  " " + r1 + " " + l2 + " " + r2);
            int cur1 = l1;
            int cur2 = l2;
            char[] new_arr = new char[r2 - l1 + 1];
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

        char[] sort(int l, int r) {
            if(l == r) {
                char[] dummy = new char[1];
                dummy[0] = arr[l];
                return dummy;
            }
            int m = (l + r)/2;
            sort(l, m);
            sort(m + 1, r);
            return merge(l, m, m + 1, r);
        }

        public char[] getArr() {
            return arr;
        }

        public void setArr(char[] arr) {
            this.arr = arr;
        }
    }

    public static class MergeSort2 {
        char[] arr;

        public MergeSort2(char[] arr) {
            this.arr = arr;
        }

        char[] merge(int l1, int r1, int l2, int r2) {
            //System.out.println(l1 +  " " + r1 + " " + l2 + " " + r2);
            int cur1 = l1;
            int cur2 = l2;
            //System.out.println(arr[cur1] + " " + arr[cur2]);
            char[] new_arr = new char[r2 - l1 + 1];
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

        char[] sort() {
            //print(arr);
            for(int i = 0; i < arr.length - 1; i += 2) {
                if(arr[i] > arr[i + 1]) {
                    char temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
            for(int len = 2; len < arr.length; len *= 2) {
                //print(arr);
                for(int i = 0; i + len < arr.length; i += 2 * len) {
                    //System.out.println(i + " " + (i + len - 1) + " " + (i + len) + " " + Math.min(i + 2 * len - 1, arr.length - 1));
                    merge(i, i + len - 1, i + len, Math.min(i + 2 * len - 1, arr.length - 1));
                    //print(arr);
                }
            }
            return arr;
        }

        public char[] getArr() {
            return arr;
        }

        public void setArr(char[] arr) {
            this.arr = arr;
        }
    }

    public static void main(String[] args) {
        char []arr = {'I', 'L', 'O', 'V', 'E', 'A', 'L', 'G', 'O', 'R', 'I', 'T', 'H', 'M', 'S'};
        MergeSort1 ms = new MergeSort1(arr);
        print(ms.sort(0, arr.length - 1));
        char []arr1 = {'I', 'L', 'O', 'V', 'E', 'A', 'L', 'G', 'O', 'R', 'I', 'T', 'H', 'M', 'S'};
        MergeSort2 ms2 = new MergeSort2(arr1);
        print(ms2.sort());
    }
}
