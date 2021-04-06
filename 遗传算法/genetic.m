function [finalResults,SSAResults]=genetic(column,row,num,height,fire,weight,varargin)
%遗传算法求解无人机的配置问题result=genetic(column,row,num,height,fire,weight)
%	column：单个样本的一列数据量   row：单个样本的一行数据量   num：要生成的样本总数
%   height: 研究区域内每一单位区域的平均海拔高度  fire：研究区域内每一单位区域的火灾发生频率
%   weight：经济性和安全性权重序列。weight[1]为经济性权重;weight[2]为安全性权重
%   varargin:   为不定参数。当其为空时，说明不需要考虑无人机数目固定的条件；
%                           当其为1时，传递的参数为无人机总数，需要考虑无人机总数固定这一条件。
%   finalResults：返回值，为最终求得的中继器结果数组  
%   SSAResults：返回值，为最终求得的SSA无人机的部署及数量
    isDroneConstant=length(varargin);
    if isDroneConstant
        droneNum=varargin{1};
    end
    samples=makeSamples(column,row,num);
    while length(samples)>3*row
        if isDroneConstant
            samplesCost=droneConstantCountSamplesCost(column,row,samples,height,fire,weight,droneNum);
        else
            samplesCost=countSamplesCost(column,row,samples,height,fire,weight);
        end
        samples=select(samples,row,samplesCost);
        samples=cross(column,row,samples);
        samples=variation(column,row,samples);
    end
    sampalsCost=countSamplesCost(column,row,samples,height,fire,weight);
    index=find(sampalsCost==min(sampalsCost));
    finalResults=samples(:,(index-1)*row+1:index*row);
    SSAResults=countFinalSSA(row,column,finalResults,height,fire);
    finalResults=(SSAResults>0);
    SSAResults=countFinalSSA(row,column,finalResults,height,fire);
end

function samples=makeSamples(column,row,num)
%生成样本数据samples=makeSamples(column,row,num)，样本数据为二维数据
%   column：单个样本的一列数据量   row：单个样本的一行数据量   num：要生成的样本总数
%   samples：返回值，返回所有样本数据的集合，为一个二维矩阵，其大小为column*(row*num)，所有的样本数据排为一列，每间隔row列数据为一个样本
    samples=[];
    for i=1:num
        sample=round(rand(column,row));
        samples=[samples sample];
    end
end

function samplesCost=countSamplesCost(column,row,samples,height,fire,weight)
%计算每一个方案的花费
    len=length(samples)/row;
    samplesCost=zeros(1,len);
    for i=1:len
        samplesCost(1,i)=singleSampleCost(column,row,samples,height,fire,weight,i);
    end
end

function s=singleSampleCost(column,row,samples,height,fire,weight,index)
    weightRate=weight(1,1)/sum(weight);
    left=row*(index-1)+1;
    right=row*index;
    s=0;
    for i=left:right
        for j=1:column
            part_area=samples(max(1,j-2):min(column,j+2),max(left,i-1):min(right,i+1));
            %统计该区域中中继器的个数
            repeaters=sum(sum(part_area));
            %该单位区域没有中继器监测
            if repeaters<1  
                s=-1;
                return;
            end
            %该区域中至少有一个中继器监测
            
            %该位置为中继器
            if samples(j,i)         
                if(max(max(height(max(1,j-2):min(column,j+2),max(1,i-left):min(row,i-left+2))))-min(min(height(max(1,j-2):min(column,j+2),max(1,i-left):min(row,i-left+2))))<=300)
                            %该区域为非山地地形
                    SSA=countSSA(column,row,fire,j,i-left+1,0);
                    otherRepeatersRate=countOtherRepeatersRate(column,left,right,samples,j,i,0,weightRate);
                else
                    SSA=countSSA(column,row,fire,j,i-left+1,1);
                    otherRepeatersRate=countOtherRepeatersRate(column,left,right,samples,j,i,1,weightRate);
                end
                %该地区存在发生火灾的可能性
                if SSA~=0
                    s=s+SSA+otherRepeatersRate;
                end
            end
        end
    end

end

function samplesCost=droneConstantCountSamplesCost(column,row,samples,height,fire,weight,droneNum)
%在需要考虑无人机总数固定时计算所有样本的预计花费
    len=length(samples)/row;
    samplesCost=zeros(1,len);
    for i=1:len
        samplesCost(1,i)=droneConstantSingleSampleCost(column,row,samples,height,fire,weight,i,droneNum);
    end
end

function s=droneConstantSingleSampleCost(column,row,samples,height,fire,weight,index,droneNum)
%在需要考虑无人机总数固定时，单个样本的预计花费
    weightRate=weight(1,1)/sum(weight);
    left=row*(index-1)+1;
    right=row*index;
    s=0;
    SSASamples=zeros(column,row);
    for i=left:right
        for j=1:column
            part_area=samples(max(1,j-2):min(column,j+2),max(left,i-1):min(right,i+1));
            %统计该区域中中继器的个数
            repeaters=sum(sum(part_area));
            %该单位区域没有中继器监测
            if repeaters<1  
                s=-1;
                return;
            end
            %该区域中至少有一个中继器监测
            
            %该位置为中继器
            if samples(j,i)         
                if(max(max(height(max(1,j-2):min(column,j+2),max(1,i-left):min(row,i-left+2))))-min(min(height(max(1,j-2):min(column,j+2),max(1,i-left):min(row,i-left+2))))<=300)
                            %该区域为非山地地形
                    SSA=countSSA(column,row,fire,j,i-left+1,0);
                    otherRepeatersRate=countOtherRepeatersRate(column,left,right,samples,j,i,0,weightRate);
                else
                    SSA=countSSA(column,row,fire,j,i-left+1,1);
                    otherRepeatersRate=countOtherRepeatersRate(column,left,right,samples,j,i,1,weightRate);
                end
                SSASamples(j,i-left+1)=SSA;
                 %该地区存在发生火灾的可能性
                if SSA~=0
                    s=s+SSA+otherRepeatersRate;
                end
            end
        end
    end
    %保证无人机的总数量不变
    nowDroneNum=sum(sum(samples(:,left:right)))+sum(sum(SSASamples));
    if abs(nowDroneNum-droneNum)>0.5*droneNum
        s=-1;
    end
end

function SSA=countSSA(column,row,fire,j,i,isMountain)
%计算当前中继器作用区域中需要配备的SSA无人机的数量
%   j:当前处理的中继器在该样本中的纵索引 
%   i:当前处理的中继器在该样本中的行索引
    if isMountain
        partArea=(max(1,j-2)-min(column,j+2)+1)*(max(1,i-1)-min(row,i+1)+1);
        totalFireFrequency=sum(sum(fire(max(1,j-2):min(column,j+2),max(1,i-1):min(row,i+1))));
        averageFireFrequency=totalFireFrequency/partArea;
        totalFireArea=sum(sum(fire(max(1,j-2):min(column,j+2),max(1,i-1):min(row,i+1))>=1));
        averageFireArea=totalFireArea./partArea;
    else
        partArea=(max(1,j-2)-min(column,j+3)+1)*(max(1,i-2)-min(row,i+2)+1);
        totalFireFrequency=sum(sum(fire(max(1,j-2):min(column,j+3),max(1,i-2):min(row,i+2))));
        averageFireFrequency=totalFireFrequency/partArea;
        totalFireArea=sum(sum(fire(max(1,j-2):min(column,j+3),max(1,i-2):min(row,i+2))>=30));
        averageFireArea=totalFireArea/partArea;
    end
    if averageFireFrequency<=10
        SSA=0;
    elseif averageFireFrequency>10 && ~isMountain
        SSA=1;
    elseif averageFireFrequency>10 && isMountain
        SSA=2;
    else
        SSA=3;
    end
    if averageFireArea>0.85
        SSA=SSA+1;
    end
    
end

function otherRepeatersRate=countOtherRepeatersRate(column,left,right,samples,j,i,isMountain,weightRate)
%计算当前中继器作用区域中有其他中继器的惩罚度
    otherRepeatersRate=0;
    if isMountain
        for c=max(1,j-2):min(column,j+2)
            for r=max(left,i-1):min(right,i+1)
                if samples(c,r)
                    d=sqrt((c-j).^2+(r-i).^2);
                    otherRepeatersRate=otherRepeatersRate+(1-d./6);
                end
            end
        end
    else
        for c=max(1,j-2):min(column,j+3)
            for r=max(left,i-2):min(right,i+2)
                if samples(c,r)
                    d=(c-j).^2+(r-i).^2;
                    otherRepeatersRate=otherRepeatersRate+(1-d./6);
                end
            end
        end
    end
    otherRepeatersRate=otherRepeatersRate*weightRate;
end

function selectedSamples=select(samples,row,samplesCost)
    selectedSamples=[];
%对样本进行自然选择
    len=length(samplesCost);
    effectSamples=0;
    totalCost=0;
%统计所有样本的总花费，并计算有效样本数
    for i=1:len
       if samplesCost(1,i)>0
           effectSamples=effectSamples+1;
           totalCost=totalCost+samplesCost(1,i);
       end
    end
%计算有效样本的平均花费
    averageCost=totalCost/effectSamples;
%进行淘汰
    for i=1:len
       if samplesCost(1,i)>0 && samplesCost(1,i)<=averageCost
           selectedSamples=[selectedSamples samples(:,(i-1)*row+1:i*row)];
       end
    end
end

function crossedSamples=cross(column,row,samples)
%模拟自然交配
    len=length(samples)/row;
    crossedSamples=[];
    for i=1:2:len-1
        mother=samples(:,(i-1)*row+1:i*row);
        father=samples(:,i*row+1:(i+1)*row);
        exchangeRow=round(rand(1,1)*(row-1))+1;
        exchangeColumn=round(rand(1,1)*(column-1))+1;
        middle=mother(exchangeColumn:column,exchangeRow:row);
        mother(exchangeColumn:column,exchangeRow:row)=father(exchangeColumn:column,exchangeRow:row);
        father(exchangeColumn:column,exchangeRow:row)=middle;
        crossedSamples=[crossedSamples mother father];
    end
end

function variationedSamples=variation(column,row,samples)
    len=length(samples)/row;
    variationedSamples=[];
    for i=1:len
        part=samples(:,(i-1)*row+1:i*row);
        if rand(1,1)>0.97
           variationRow=round(rand(1,1)*(row-1))+1;
           variationColumn=round(rand(1,1)*(column-1))+1;
           part(variationColumn,variationRow)=~part(variationColumn,variationRow);
        end
        variationedSamples=[variationedSamples part];
    end
end

function SSASamples=countFinalSSA(row,column,samples,height,fire)
%统计方案的SSA无人机数
    SSASamples=zeros(size(samples));
    len=length(samples)/row;
    for i=1:len
       left=(i-1)*row+1;
       right=i*row;
       for c=1:column
          for r=left:right
             if samples(c,r)
                 if (max(max(height(max(1,c-2):min(column,c+2),max(1,r-left):min(row,r-left+2))))-min(min(height(max(1,c-2):min(column,c+2),max(1,r-left):min(row,r-left+2))))<=300)
                     SSASamples(c,r)=countSSA(column,row,fire,c,r-left+1,0);
                 else
                     SSASamples(c,r)=countSSA(column,row,fire,c,r-left+1,1);
                 end
             end
          end
       end    
    end
end