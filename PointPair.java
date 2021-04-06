import java.util.ArrayList;
import java.util.TreeSet;

public class PointPair {

    ArrayList<Point> pointArrayList=new ArrayList<>();  //盛放点对集合

    /**
     * 向点对容器中添加点对
     * @param x 点对的横坐标
     * @param y 点对的纵坐标
     */
    void addPoint(int x,int y){
        pointArrayList.add(new Point(x,y));
    }

    /**
     * 找到容器中最近的点对
     * @param start 在该次计算的点对集合中，最左边点对在容器中的索引
     * @param end 在该次计算的点对集合中，最右边点对在容器中的索引
     * @return 最短的距离
     */
    double findClosestPointPair(int start,int end){
        int length=end-start+1;
        if(length<=0)
            return -1;
        else if(length==1)
            return 1000;
        else if(length==2){
            return countDistance(pointArrayList.get(start),pointArrayList.get(end));
        }

        else{
            TreeSet<Point> compare=new TreeSet<>();
            int middleIndex=(start+end)/2;
            Point dividePoint=pointArrayList.get(middleIndex);
            compare.add(dividePoint);
            double min=Math.min(findClosestPointPair(start,middleIndex-1),findClosestPointPair(middleIndex+1,end));

            for(int i=middleIndex+1;i<=end;i++){
                if(Math.abs(pointArrayList.get(i).x-dividePoint.x)<min)
                    compare.add(pointArrayList.get(i));
                else
                    break;
            }
            for(int i=middleIndex-1;i>=start;i--){
                if(Math.abs(dividePoint.x-pointArrayList.get(i).x)<min)
                    compare.add(pointArrayList.get(i));
                else
                    break;
            }

            int size=compare.size();

            for(int i=0;i<size;i++){
                Point P=compare.first();
                compare.remove(P);
                for(Point p:compare){
                    if(Math.abs(P.x-p.x)<min&&Math.abs(P.y-p.y)<min)
                        min=Math.min(min,countDistance(P,p));
                    else if(Math.abs(P.x-p.x)>=min&&Math.abs(P.y-p.y)>=min)
                        break;
                }
            }
            return min;
        }
    }

   double countDistance(Point a,Point b){
        return Math.sqrt(Math.pow(a.x-b.x,2)+Math.pow(a.y-b.y,2));
    }

    public static void main(String[] args){
       PointPair p=new PointPair();
       p.addPoint(1,1);
       p.addPoint(2,3);
       p.addPoint(3,2);
       p.addPoint(5,5);
       p.addPoint(6,2);
       p.addPoint(7,9);
       System.out.println(p.findClosestPointPair(0,5));
    }
}
class Point implements Comparable<Point>{
    int x;
    int y;
    Point(int x,int y){
        this.x=x;
        this.y=y;
    }
    @Override
    public int compareTo(Point b) {
        return this.x-b.x;
    }
}
