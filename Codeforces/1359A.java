import java.util.*;
import java.lang.*;
import java.io.*;
import java.io.*;
public class Main {
    static int ceil(int a, int b){
        //ceiling of a/b
        if(a % b == 0) return a/b;
        return a/b + 1;
    }
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        //int num = scan.nextInt();
        int t = scan.nextInt();
        for(int tc = 0; tc < t; tc++){
            int n = scan.nextInt();
            int m = scan.nextInt();
            int k = scan.nextInt();
            int weGet = Math.min(n/k, m);
            int ans = ceil(m - weGet, k - 1);
            System.out.println(weGet - ans);
        }
    }
 
}
