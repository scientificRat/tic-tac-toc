//
//  main.cpp
//  tic-tac-toc(test)
//
//  Created by 黄正跃 on 16/3/12.
//  Copyright © 2016年 黄正跃. All rights reserved.
//

#include <iostream>
using namespace std;


//打印棋谱
void displayMap(int **map,int width,int height);
//计算棋局值
int calcValue(int **map,int width,int height);

void inputStep(int **map);

int maxValue(int **map,int width,int height,int steps);
int minValue(int **map,int width,int height,int steps);

int main(int argc, const char * argv[]) {
    const int width=3;
    const int height=3;
    int max_num=-100000;
    int temp;
    int step=1;
    int x,y;
    //initial
    int **map=new int*[height];
    for(int i=0;i<height;i++){
        map[i]=new int[width];
        for(int j=0;j<width;j++){
            map[i][j]=0;
        }
    }

    
    displayMap(map, width, height);

   
    while(true){
        x=0;
        y=0;
        max_num=-100000;
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                //if unvisited
                if(map[i][j]==0){
                    map[i][j]=5;
                    temp=minValue(map,width,height,step);
                    if(max_num<temp){
                        max_num=temp;
                        x=i;
                        y=j;
                    }
                    map[i][j]=0;
                }
                
            }
        }
        
        map[x][y]=5;
        step++;
        displayMap(map, width, height);
        if(calcValue(map, width, height)!=0 ||step>9){
            break;
        }
        cout<<"------\n>>>";
        inputStep(map);
        step++;
        cout<<"------\n";
        displayMap(map, width, height);
        cout<<"------\n";
        if(calcValue(map, width, height)!=0 ||step>9){
            break;
        }
        
    }
    

    return 0;
}


void displayMap(int **map,int width,int height){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            switch (map[i][j]) {
                case 5:
                    cout<<"O";
                    break;
                case 7:
                    cout<<"X";
                    break;
                default:
                    cout<<" ";
                    break;
            }
        }
        cout<<"\n";
    }
    
}
void inputStep(int **map){
    int a,b;
    cin>>a>>b;
    map[a][b]=7;

}

//三个返回值 1胜 －1负 0没有胜负（不一定是平）
int calcValue(int **map,int width,int height){
    int i,j,sum;
    //目前这个函数只能用于三子棋
    //检查行列 对角线
    //行
    for(i=0;i<height;i++){
        sum=0;
        for(j=0;j<width;j++){
            sum+=map[i][j];
        }
        if(sum==15){
            return 1;
        }
        else if(sum==21){
            return -1;
        }
    }
    //列
    for(j=0;j<width;j++){
        sum=0;
        for(i=0;i<height;i++){
            sum+=map[i][j];
        }
        if(sum==15){
            return 1;
        }
        else if(sum==21){
            return -1;
        }
    }
    //主对角线
    sum=0;
    for(i=0;i<width;i++){
        sum+=map[i][i];
    }
    if(sum==15){
        return 1;
    }
    else if(sum==21){
        return -1;
    }
    //副对角线
    sum=0;
    for(i=0;i<width;i++){
        sum+=map[i][2-i];
    }
    if(sum==15){
        return 1;
    }
    else if(sum==21){
        return -1;
    }
    
    return 0;
}
int min(int a,int b){
    if(a<b){
        return a;
    }
    else {
        return b;
    }
}
int max(int a,int b){
    if(a>b){
        return a;
    }
    else {
        return b;
    }
}
//min-max

int maxValue(int **map,int width,int height,int steps){
    int mapValue=calcValue(map, width, height);
    if(steps<9&&mapValue==0){
        
    }
    else{
        return mapValue;
    }
    int maxValue=-100000;
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            //if visited
            if(map[i][j]==0){
                map[i][j]=5;
                maxValue=max(maxValue,minValue(map, width, height, steps++)-1);
                map[i][j]=0;

            }
        }
    }
    return maxValue;
}

int minValue(int **map,int width,int height,int steps){
    int mapValue=calcValue(map, width, height);
    if(steps<9&&mapValue==0){
        
    }
    else{
        return mapValue;
    }
    int minValue=100000;
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            //if unvisited
            if(map[i][j]==0){
                map[i][j]=7;
                minValue=min(minValue,maxValue(map, width, height, steps++)-1);
                map[i][j]=0;
            }
        }
    }
    return minValue;
}


