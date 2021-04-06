public class EldestSonSequence {

    private String sequence;

    private class Part{
        String s;
        int length;

        /**
         * 每一种子情况的最长子序列类
         * @param s 最长子序列
         * @param length 最长组序列长度
         */
        Part(String s,int length){
            this.s=s;
            this.length=length;
        }
    }

    /**
     * 构建一个包含一个字符序列的对象
     * @param s 该对象包含的字符序列
     */
    EldestSonSequence(String s){
        this.sequence=s;
    }

    /**
     * 找到最长子序列
     * @param s 需要进行比较的子序列
     * @return 返回最长子序列
     */
    String findEldestSonSequence(String s){
        String ESS="";
        int length1=sequence.length();
        int length2=s.length();


        char part1[]=sequence.toCharArray();
        char part2[]=s.toCharArray();

        Part partEES[][]=new Part[length1+1][length2+1];

        for(int i=0;i<=length1;i++)
            partEES[i][0]=new Part("",0);
        for(int i=0;i<=length2;i++)
            partEES[0][i]=new Part("",0);
        for(int i=1;i<=length1;i++){
            for(int j=1;j<=length2;j++){
                if(part1[i-1]==part2[j-1]){
                    partEES[i][j]=new Part(partEES[i-1][j-1].s+part1[i-1],partEES[i-1][j-1].length+1);
                }
                else {
                    partEES[i][j]=new Part(max(partEES[i-1][j],partEES[i][j-1]).s,max(partEES[i-1][j],partEES[i][j-1]).length);
                }
            }
        }
        return partEES[length1][length2].s;
    }

    /**
     * 返回两种情况中子序列最长的情况
     * @param one 情况一
     * @param two 情况二
     * @return 返回子序列最长的情况
     */
    Part max(Part one ,Part two){
        if(one.length>two.length)
            return one;
        else
            return two;
    }

    public static void main(String[] args){
        EldestSonSequence e1=new EldestSonSequence("ACCGGTCGAGATGCAG");
        System.out.print(e1.findEldestSonSequence(" GTCGTTCGGAATGCAT"));
    }
}
