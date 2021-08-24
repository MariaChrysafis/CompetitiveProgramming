import java.util.*;
import java.util.Iterator;
import java.io.*;
 
 
public class Main {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
 
        public FastReader() {
            br = new BufferedReader(new
                    InputStreamReader(System.in));
        }
 
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
 
        long nextLong() {
            return Long.parseLong(next());
        }
 
        double nextDouble() {
            return Double.parseDouble(next());
        }
 
        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
    public static class Graph{
        ArrayList<ArrayList<Integer>> adj;
        ArrayList<Boolean> hasVisited;
        ArrayList<Integer> color;
 
        public Graph(ArrayList<ArrayList<Integer>> adj, ArrayList<Boolean> hasVisited, ArrayList<Integer> color) {
            this.adj = adj;
            this.hasVisited = hasVisited;
            this.color = color;
        }
 
 
        void dfs (int cur, int col){
            hasVisited.set(cur, true);
            color.set(cur, col);
            for(int i: adj.get(cur)){
                if(!hasVisited.get(i)){
                    dfs(i, col);
                }
            }
        }
 
        public int connectedComponents(){
            while(hasVisited.size() != adj.size()){
                hasVisited.add(false);
            }
            while(color.size() != adj.size()){
                color.add(-1);
            }
            int cc = 0;
            for(int i = 0; i < adj.size(); i++){
                if(!hasVisited.get(i)){
                    dfs(i, cc);
                    cc++;
                }
            }
            return cc;
        }
    }
    static ArrayList<ArrayList<Integer>> adj = new ArrayList<ArrayList<Integer>> ();
    static int n;
    static int m;
    static int q;
    public static void main(String[] args) {
        OutputStream outputStream = System.out;
        PrintWriter out = new PrintWriter(outputStream);
        FastReader in = new FastReader();
        n = in.nextInt();
        m = in.nextInt();
        q = in.nextInt();
        while(adj.size() != n + m + 2){
            adj.add(new ArrayList<>());
        }
        for(int i = 0; i < q; i++){
            int u = in.nextInt() - 1;
            int v = in.nextInt() - 1;
            v += n;
            adj.get(u).add(v);
            adj.get(v).add(u);
        }
        Graph g = new Graph (adj, new ArrayList<>(), new ArrayList<>());
        System.out.println(g.connectedComponents() - 3);
 
    }
}
