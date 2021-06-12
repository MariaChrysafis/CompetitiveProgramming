import java.util.*;
import java.lang.*;
import java.io.*;
import java.io.*;
public class Main {
    static int INF = 1000000000;
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        long []orig = new long[n];
        for(int i = 0; i < n; i++){
            orig[i] = scan.nextInt();
        }
        long printable = 0;
        for(int myMax = 1; myMax <= 30; myMax++){
            long[]arr = new long[n];
            for(int i = 0; i < n; i++) arr[i] = orig[i];
            for(int i = 0; i < n; i++){
                if(arr[i] > myMax) {
                    arr[i] = -INF;
                }
            }
            long cur = 0;
            long ans = 0;
            for(int i = 0; i < n; i++){
                cur = cur + arr[i];
                cur = Math.max(cur, 0);
                if(cur > ans){
                    ans = cur;
                }
            }
            printable = Math.max(ans - myMax, printable);
        }
        System.out.println(printable );
    }

}
