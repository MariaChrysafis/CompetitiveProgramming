import java.util.*;
import java.lang.*;
import java.io.*;
import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int []arr = new int[n];
        int dist = 0;
        for(int i = 0; i < n; i++){
            arr[i] = scan.nextInt();
            if(i == 0) dist += arr[i];
            else dist += Math.abs(arr[i] - arr[i - 1]);
        }
        dist += arr[n - 1];
        System.out.println(dist + n);
    }
 
}
