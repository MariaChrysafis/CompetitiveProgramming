    //package com.MARIAAAA;
    import java.util.*;
    import java.lang.*;
    import java.io.*;
    import java.io.*;
    public class Main {
        static void print(int[] arr){
            for(int i = 0; i < arr.length; i++){
                System.out.print(arr[i] );
            }
            System.out.println();
        }
        public static void main(String[] args) throws IOException {
            Scanner scan = new Scanner(System.in);
            int t = 1;
            for(int tc = 0; tc < t; tc++) {
                int n = scan.nextInt();
                int m = scan.nextInt();
                if(n == 0){
                    if(m == 1) System.out.print(0);
                    else System.out.println(-1);
                    return;
                }
                if (n > 9 * m) {
                    System.out.print(-1);
                    return;
                }
                int avg = n / m;
                int[] arr = new int[m];
                int sum = 0;
                for (int i = 0; i < m; i++) {
                    arr[i] = avg;
                    sum += avg;
                }
                int x = 0;
                while (sum < n) {
                    arr[x]++;
                    x++;
                    sum++;
                }
                print(arr);
            }
     
        }
     
    }
