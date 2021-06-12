import java.util.*;
import java.lang.*;
import java.io.*;
import java.io.*;
public class Main {
    static double abs(double x){
        if(x < 0) return -x;
        return x;
    }
    static int ceil(double d){
        return (int)Math.ceil(d);
    }
    static int floor(double d){
        return (int)Math.floor(d);
    }
    static long[] slv(long h, long c, long d, long moves){
        long num = (moves + 1) * h + moves * c;
        long denom = 2 * moves + 1;
        num -= d * denom;
        num = Math.abs(num);
        denom = Math.abs(denom);
        long[] arr = new long[2];
        arr[0] = num;
        arr[1] = denom;
        return arr;
    }
    static boolean lessThan(long[] a1, long[] a2){
        return (a1[0] * a2[1] <= a2[0] * a1[1]);
    }
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        for(int tc = 0; tc < t; tc++){
            long h = scan.nextInt();
            long c = scan.nextInt();
            long d = scan.nextInt();
            long val1 = 0;
            if(2 * d - h - c == 0) val1 = 0;
            else val1 = (h - d)/(2 * d - h - c);
            val1 = Math.max(val1, 0);
            long val2 = val1 + 1;
            long[] ans1 = slv(h, c, d, val1);
            long[] ans2 = slv(h, c, d, val2);
            long[] ansn = new long[2];
            ansn[0] = Math.abs(h + c - 2 * d);
            ansn[1] = Math.abs(2);
            if(lessThan(ans1, ans2) && lessThan(ans1, ansn)){
                System.out.println(val1 * 2 + 1);
            }else if(lessThan(ans2, ans1) && lessThan(ans2, ansn)){
                System.out.println(val2 * 2 + 1);
            }else if(lessThan(ansn, ans1) && lessThan(ansn, ans2)){
                System.out.println(2);
            }
 
        }
    }
 
}
