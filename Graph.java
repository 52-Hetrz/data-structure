package SSE;

import java.util.ArrayList;

public class Graph {

    private int[][] V;
    private int[][] W;
    private int n;

    private class PointCup{
        int from;
        int to;

        PointCup(int from,int to){
            this.from=from;
            this.to=to;
        }
    }

    Graph(int[][] V,int[][] W, int n){
        this.V=V;
        this.W=W;
        this.n=n;
    }

    Graph(int[][] W, int n){
        this.W=W;
        this.n=n;
    }

    /**
     * 寻找最短路径和
     * @param start 起点
     * @param destination 终点
     */
    void findShortestPath(int start,int destination) {

        int flag=0;
        int[] length = new int[n];
        int[] father = new int[n];
        ArrayList<PointCup> pointCupArrayList = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (W[i][j] != 0)
                    pointCupArrayList.add(new PointCup(i, j));
            }
        }
        for (int i = 0; i < n; i++) {
            length[i] = 1000;
        }
        length[start]=0;
        for (int i = 0; i < n; i++) {
            father[i] = -1;
        }

        for (int i = 1; i <= n - 1; i++) {
            for (PointCup p : pointCupArrayList) {
                int f = p.from;
                int t = p.to;
                if (length[f] + W[f][t] < length[t]) {
                    father[t] = f;
                    length[t] = length[f] + W[f][t];
                }
            }
        }

        for (PointCup p : pointCupArrayList) {
            int f = p.from;
            int t = p.to;
            if (length[f] + W[f][t] < length[t]) {
               System.out.print("Has negative-cycle");
               flag=1;
            }
        }

        if(flag==0){
            for(int i=0;i<n;i++){
                System.out.println(i+"'s father is "+father[i]);
            }

            System.out.println("最短路径长度： "+length[destination]);
        }
    }

    void findAllPointCup(int[][] W,int n){

        ArrayList<int[][]> D=new ArrayList<>();

        D.add(W);

        for(int k=1;k<=n;k++){
            int[][] a=new int[n][n];
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    a[i-1][j-1]=Math.min(D.get(k-1)[i-1][j-1],D.get(k-1)[i-1][k-1]+D.get(k-1)[k-1][j-1]);
                }
            }
            D.add(a);
        }
        int[][] b=D.get(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                System.out.print(b[i][j]+"   ");
            }
            System.out.println(" ");
        }
    }

    public static void main(String[] args){
        int[][] w=new int[5][5];
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
               w[i][j]=10000;
            }
        }
        w[0][1]=6;
        w[0][3]=7;
        w[1][2]=5;
        w[1][3]=8;
        w[1][4]=-4;
        w[2][1]=-2;
        w[3][2]=-3;
        w[3][4]=9;
        w[4][0]=2;
        w[4][2]=7;

        Graph g=new Graph(w,5);
        g.findShortestPath(0,4);
        g.findAllPointCup(w,5);
    }


}
