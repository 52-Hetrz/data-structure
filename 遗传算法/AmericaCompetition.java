
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Random;

public class AmericaCompetition {

    /** 模拟退火
     * 在局部最大值的基础上，以一定几率继续向下搜索
     * @param a     需要进行检测的序列
     * @return      返回该算法检测的最大值
     */
    public int simulatedAnnealing(int[] a){
        int min=0;                          //能接受的最小值
        int max=-1000;                      //初始最大值
        double T=100;
        int difference=0;
        double r= 0.8;
        Random random=new Random(1);
        for(int i:a){
            if (i<min)
                break;
            difference=i-max;               //计算差值
            if(difference>0)                //当前值优于最大值
                max=i;
            else{                           //小于最大值
                if(Math.exp(difference/T)> random.nextDouble()) {
                    T=T*r;                  //按照一定几率继续往下走搜索，此时要降温退火
                }
                else{
                    break;
                }
            }
        }
        return max;
    }


    /** 遗传算法
     * 1、确定编码规则，一种映射关系
     * 2、初始化一个种群
     * 3、根据编码的适应度函数，
     *      对种群进行适应度评估，看是否符合最佳优化准则，符合则输出最佳个体，结束遗传；不符合则继续下一步
     * 4、按照一定的适应度规则对种群进行选择，适应度高的选择出来准备交叉产生后代，适应度低的被淘汰
     * 5、交叉产生后代，替换父代
     * 6、变异
     *  使用遗传算法
     * @param weight        每个宝藏对应的重量
     * @param value         每个宝藏的价值
     * @param bagMax        背包的最大容量
     * @param samplesNum    初始样本数量
     * @return  返回最佳选择的宝藏价值
     */
    public int genetic(int[] weight,int[] value,int bagMax,int samplesNum){
        int treasureNum=weight.length;
        ArrayList<int[]> samples=makeSample(treasureNum,samplesNum);
        int[] samplesValue;
        while(samples.size()<=3){
            samplesValue=countSamplesValue(samples,value,weight,bagMax);
            select(samples,samplesValue);
            System.out.println("自然选择：");
            for(int[] a:samples){
                System.out.println(Arrays.toString(a));
            }

            cross(samples,treasureNum);
            System.out.println("交叉：");
            for(int[] a:samples){
                System.out.println(Arrays.toString(a));
            }

            variation(samples,treasureNum);
            System.out.println("变异：");
            for(int[] a:samples){
                System.out.println(Arrays.toString(a));
            }
        }

        int max=0;
        int[] finalValues=countSamplesValue(samples,value,weight,bagMax);
        for (int a:finalValues){
            max=Math.max(max,a);
        }

        return max;
    }

    /** 产生样本
     * 使用二进制数字来表示样本，每个二进制数字用int[]来存储
     * @param digits   样本的二进制位数
     * @param num      产生样本的数目
     * @return         返回样本集合，类型为ArrayList
     */
    private ArrayList<int[]> makeSample(int digits,int num){
        Random random=new Random();
        ArrayList<int[]> samples=new ArrayList<>();
        for(int i=1;i<=num;i++){
            int[] temp=new int[digits];
            for(int j=0;j<digits;j++)
                temp[j]= random.nextInt(2);
            samples.add(temp);
        }
        return samples;
    }

    /** 计算当前样本的适应度值
     *  根据二进制数，计算样本的价值，以及重量，如果超过最大重量则令样本价值为负数
     * @param sample    样本
     * @param value     价值函数
     * @param weight    重量函数
     * @param bagMax    所能容纳的最大质量
     * @return  返回该样本的适应度
     */
    private int countSingleSampleValue(int[] sample,int[] value,int[] weight,int bagMax){
        int num=sample.length;
        int tempWeight=0;
        int tempValue=0;
        for(int i=0;i<num;i++){
            tempValue=sample[i]*value[i];
            tempWeight=sample[i]*weight[i];
        }
        if(tempWeight>bagMax)
            tempValue=-1;
        return tempValue;
    }

    /** 计算所有样本的适应度值
     *  根据二进制数，计算样本的价值，以及重量，如果超过最大重量则令样本价值为负数
     * @param samples   样本集合
     * @param value     价值函数
     * @param weight    重量函数
     * @param bagMax    背包最大容量
     * @return          每个样本对应的适应度值
     */
    private int[] countSamplesValue(ArrayList<int[]> samples,int[] value,int[] weight,int bagMax){
        int num=value.length;
        int[] values=new int[samples.size()];
        int tempWeight;
        int tempValue;
        for(int[] sample:samples){
            tempValue=0;
            tempWeight=0;
            for(int i=0;i<num;i++){
                tempValue=tempValue+sample[i]*value[i];
                tempWeight=tempWeight+sample[i]*weight[i];
            }
            if(tempWeight>bagMax)
                tempValue=-1;
            values[samples.indexOf(sample)]=tempValue;
        }
        return values;
    }

    /** 自然选择
     *  将那些适应度低于全部有效样本平均值的样本淘汰
     * @param samples       样本集合
     * @param samplesValue  样本对应的价值
     */
    private void select(ArrayList<int[]> samples,int[] samplesValue){
        int samplesNum=samples.size();
        double totalValues=0;           //所有有效样本的总价值
        int effectiveSample=0;
        System.out.println("初始样本:");
        for(int i=0;i<samplesNum;i++){  //计算所有样本的总价值，不统计负数价值的样本
            System.out.println(Arrays.toString(samples.get(i))+" Value:"+samplesValue[i]);
            if(samplesValue[i]>=0){
                totalValues=totalValues+samplesValue[i];
                effectiveSample++;
            }
        }
        double ave=totalValues/effectiveSample;
        Iterator<int[]> samplesIterator=samples.iterator();
        int j=0;
        while(samplesIterator.hasNext()){
            samplesIterator.next();
            if(samplesValue[j]<=ave)
                samplesIterator.remove();
            j++;
        }
    }

    /** 样本随机交配
     *  在选择之后的种群内进行随机交配，交配完之后即刻修改在samples中的值
     * @param samples   种群中存留的样本。
     * @param digits    二进制表示样本的位数
     */
    private void cross(ArrayList<int[]> samples,int digits){
        int num=samples.size();
        int[] mother,father;                //交叉的父母双方
        int node,middle;
        Random random=new Random();
        for(int i=0;i<num-1;){
           mother=samples.get(i);
           father=samples.get(i+1);
           node= random.nextInt(digits);
           for(int j=0;j<node;j++){
               middle=father[j];
               father[j]=mother[j];
               mother[j]=middle;
           }
           i+=2;
        }
    }

    /** 个体变异
     *  个体内部某个基因发生突变
     * @param samples   样本集合
     * @param digits    二进制位数
     */
    private void variation(ArrayList<int[]> samples,int digits){
        Random random=new Random();
        for(int[] sample:samples){
            if(random.nextDouble()>0.9){
                System.out.println(samples.indexOf(sample)+" variate");
                sample[random.nextInt(digits)]=Math.abs(sample[random.nextInt(digits)]-1);
            }
        }
    }


    /** 十进制转二进制
     *
     * @param num   需要转换的十进制数字
     * @param digits  转换成二进制的位数
     * @return  返回转换的结果，将结果存储在一个int[]数组中
     */
    private int[] decToBin(int num,int digits){
        if(num<0)
            return null;
        int temp=num;
        int[] result=new int[digits];
        for(int i=1;i<=digits;i++){
            result[digits-i]=temp%2;
            temp=temp/2;
        }
        return result;
    }


    /** 动态规划解决0-1背包问题
     *
     * @param weight 每个宝藏对应的重量
     * @param value 每个宝藏的价值
     * @param bagMax 背包的最大容量
     * @return  返回最佳选择的宝藏价值
     */
    public int bagProblem(int[] weight,int[] value,int bagMax){
        int maxValue=0;
        int partValue=0;
        int treasureNum=weight.length;
        int[][] partResult=new int[bagMax+1][treasureNum+1];
        for(int i=0;i<=treasureNum;i++)
            partResult[0][i]=0;
        for(int i=0;i<=bagMax;i++)
            partResult[i][0]=0;

        for(int i=1;i<=bagMax;i++){
            for(int j=1;j<=treasureNum;j++){
                if(weight[j-1]<=i){              //当前背包容量可以装下新增的宝藏
                    partValue=Math.max(value[j-1]+partResult[i-weight[j-1]][j-1],partResult[i][j-1]);
                    if(partValue>maxValue){
                        maxValue=partValue;
                        partResult[i][j]=partValue;
                    }else{
                        partResult[i][j]=maxValue;
                    }
                }else{
                    partResult[i][j]=maxValue;
                }
            }
        }
        return partResult[bagMax][treasureNum];
    }


    public static void main(String args[]){
        AmericaCompetition americaCompetition=new AmericaCompetition();
        //int[] simulatedAnnealing={1,2,3,4,5,4,3,2,6,7,4,3,8,9,14,16,4,3};
        //System.out.println(new AmericaCompetition().simulatedAnnealing(simulatedAnnealing));
        int[] weight={4,2,1,5,3,7,6,3};
        int[] value={6,1,1,4,2,10,5,2};
        System.out.println(americaCompetition.bagProblem(weight,value,18));
        System.out.println(americaCompetition.genetic(weight,value,18,200));
        //System.out.println(Arrays.toString(americaCompetition.decToBin(12, 8)));
    }
}
