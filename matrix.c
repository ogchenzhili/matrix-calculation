#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "function.h"
int main()
{
    float**a,**b,**div,**mul,**inv,**tra;//建立输入与结果双重指针
    int i,j;
    char ad[100],bd[100],jgd[100];
    float x[2],y[2];//维数数组
    FILE*pt1;//文件指针
    FILE*pt2;
    FILE*pt3;

    printf("choose your first document:");//文件地址
    scanf("%s",ad);
    printf("choose your sceond document:");
    scanf("%s",bd);
    printf("choose your third document:");
    scanf("%s",jgd);

    pt1=fopen(ad,"r");//指向文件
    pt2=fopen(bd,"r");
    pt3=fopen(jgd,"w");

    for(i=0;i<2;i++)//读取维数
    {
        fscanf(pt1,"%f",&x[i]);
    }
    for(i=0;i<2;i++)
    {
        fscanf(pt2,"%f",&y[i]);
    }

    a=mal(x[0],x[1]);//建立动态二维数组
    b=mal(y[0],y[1]);
    div=mal(x[0],x[1]);
    mul=mal(x[0],y[1]);
    inv=mal(x[0],x[0]);
    tra=mal(x[1],x[0]);
//----------------------------------------------
    for(i=0;i<x[0];i++)//读取矩阵
    {
        for(j=0;j<x[1];j++)
        {
            fscanf(pt1,"%f",&a[i][j]);
        }
    }
    for(i=0;i<y[0];i++)
    {
        for(j=0;j<y[1];j++)
        {
            fscanf(pt2,"%f",&b[i][j]);
        }
    }
//****************************************************************************************************************************
//****************************************************************************************************************************
//--------------------------------------------------------------------
    tra=transport(a,x[0],x[1]);//矩阵转置
    fprintf(pt3,"transport matrix:\n");
    printf("transport finished!\n");
    for(i=0;i<x[1];i++)
    {
        for(j=0;j<x[0];j++)
        {
            fprintf(pt3,"%f\t",tra[i][j]);
        }
        fprintf(pt3,"\n");
     }
//------------------------------------------------------------------
    if(x[1]==y[0])//矩阵乘法
    {
        mul=multiplication1(a,b,x[0],x[1],y[1]);
        fprintf(pt3,"multiplication matrix:\n");
        printf("multiplication finished!\n");
        for(i=0;i<x[0];i++)
        {
            for(j=0;j<y[1];j++)
            {
                fprintf(pt3,"%f\t",mul[i][j]);
            }
                fprintf(pt3,"\n");
        }
            fprintf(pt3,"\n");
    }
    else
    {
        printf("can't multiplication1\n");
    }
//--------------------------------------------------------------------
    if((x[0]==x[1])&&evaluation(a,x[0])!=0)//逆矩阵
    {
        inv=inverse(a,x[0]);
        fprintf(pt3,"inverse matrix:\n");
        printf("inverse finished!\n");
        for(i=0;i<x[0];i++)
        {
            for(j=0;j<x[0];j++)
            {
                fprintf(pt3,"%f\t",inv[i][j]);
            }
            fprintf(pt3,"\n");
        }
        fprintf(pt3,"\n");
    }
    else
    {
        printf("can't inverse\n");
    }
//---------------------------------------------------------------
    if((x[1]==y[0])&&y[0]==y[1]&&evaluation(b,y[0])!=0)//矩阵除法
    {
    div=division(a,b,x[0],x[1]);
    fprintf(pt3,"division matrix:\n");
    printf("division finished!\n");
    for(i=0;i<x[0];i++)
    {
        for(j=0;j<x[1];j++)
        {
            fprintf(pt3,"%f\t",div[i][j]);
        }
        fprintf(pt3,"\n");
    }
    fprintf(pt3,"\n");
    }
    else
    {
        printf("can't division\n");
    }


//------------------------------------------------------------------
    for(i=0;i<x[0];i++)//动态数组释放
    {
        free(inv[i]);
        free(tra[i]);
    }
    for(i=0;i<y[1];i++)
    {
        free(b[i]);
        free(mul[i]);
    }
    for(i=0;i<x[1];i++)
    {
        free(a[i]);
        free(div[i]);
    }

    fclose(pt1);//文件关闭
    fclose(pt2);
    fclose(pt1);
    return 0;
}



