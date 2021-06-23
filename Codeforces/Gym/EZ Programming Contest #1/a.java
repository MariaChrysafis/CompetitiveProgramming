import java.lang.*;
import java.math.BigInteger;
import java.util.Scanner;
 
public class Main {
    static void print(int[] arr){
        for(int i = 0; i < arr.length; i++){
            System.out.print(arr[i] + " ");
        }
        System.out.println();
        return;
    }
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        for(int i = 0; i < t; i++){
            int n = scan.nextInt();
            int k = scan.nextInt();
            int [] arr = new int[n];
            int myMin = 1000000000;
            int myMax = 0;
            for(int j = 0; j < n; j++){
                arr[j] = scan.nextInt();
                myMin = Math.min(myMin, arr[j]);
                myMax = Math.max(myMax, arr[j]);
            }
            System.out.println(myMax - myMin);
        }
    }
}
