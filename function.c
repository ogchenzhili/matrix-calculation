#include "function.h"
float**mal(int a,int b)
{
    float**a1;
    int i;
    a1=(float**)malloc(a*sizeof(float*));
    for(i=0;i<a;i++)
    {
        a1[i]=(float*)malloc(b*sizeof(float));
    }
    return a1;
}
//---------------------------------------------------------------------------
float evaluation(float**a,int x)                           //高斯求行列式
{
    int i,j,k,mm,index,m=0,max;
    float gaosi[x][x],flag,other=1,place;
    for(i=0;i<x;i++)
    {
        for(j=0;j<x;j++)
        {
            gaosi[i][j]=a[i][j];
        }
    }
    float det;
    float ss=1;
    for(i=0;i<x-1;i++)                                  //减行
    {
        index=i;
        place=gaosi[i][i];
        for(max=i+1;max<x;max++)
        {
            if(fabs(place)<fabs(gaosi[max][i]))
            {
                place=gaosi[max][i];
                index=max;
            }
        }
        if(index!=i)
        {
            for(mm=0;mm<x;mm++)
            {
                flag=gaosi[i][mm];
                gaosi[i][mm]=gaosi[index][mm];
                gaosi[index][mm]=flag;
            }
            m++;
        }
        if(gaosi[i][i]==0)
        {
            other=0;
        }
        else
        {
            for(j=i+1;j<x;j++)                              //被减行
            {
                det=gaosi[j][i]/gaosi[i][i];
                for(k=i;k<x;k++)                          //运算的列项
                {
                    gaosi[j][k]=gaosi[j][k]-det*gaosi[i][k];
                }

            }
        }
    }
    if(other==1)
    {
        for(i=0;i<x;i++)
        {
            ss=ss*gaosi[i][i];
        }
        return pow(-1,m)*ss;
    }
    else
    {
        return 0;
    }
}
//--------------------------------------------------------------
float**companion(float**a,int x)  //伴随矩阵
{
    float**bansui2;
    float**bansui1;
    bansui1=mal(x-1,x-1);
    int k,z,m=0,n=0;
    int i,j;
    bansui2=mal(x,x);
    for(i=0;i<x;i++)
    {
        for(j=0;j<x;j++)
        {
            m=0;
            for(k=0;k<x;k++)
            {
                n=0;
                if(k==i)continue;
                for(z=0;z<x;z++)
                {
                    if(z==j)continue;
                    bansui1[m][n]=a[k][z];
                   // printf("\n%d %d",m,n);
                    n=n+1;
                }
                m=m+1;
            }
            bansui2[j][i]=pow(-1,i+j)*evaluation(bansui1,x-1);
        }
    }
    return bansui2;
}
//-----------------------------------------------------------------------------
float**inverse(float**a,int x)                                                    //逆矩阵
{
    float**nijuzhen1;
    nijuzhen1=mal(x,x);
    int i,j;
    float**nijuzhen2;
    nijuzhen2=mal(x,x);
    nijuzhen2=companion(a,x);
    for(i=0;i<x;i++)
    {
        for(j=0;j<x;j++)
        {
            nijuzhen1[i][j]=nijuzhen2[i][j]/evaluation(a,x);
        }
    }
    return nijuzhen1;
}
//----------------------------------------------------------------------------
float**division(float**a,float**b,int x,int y)                                      //矩阵除法
{
    float**c,**d;
    c=mal(y,y);
    d=mal(x,y);
    c=inverse(b,y);
    d=multiplication1(a,c,x,y,y);
    return d;
}
//---------------------------------------------------------------
float **multiplication1(float **a,float **b,int x,int y,int z)//矩阵乘法
{
    float**c,tem=0;
    int i,j,k;
    c=(float**)malloc(x*sizeof(float*));
    for(i=0;i<x;i++)
    {
        c[i]=malloc(z*sizeof(float));
    }
    for(i=0;i<x;i++)
    {
        for(j=0;j<z;j++)
        {
            tem=0;
            for(k=0;k<y;k++)
            {
                tem=tem+a[i][k]*b[k][j];
            }
            c[i][j]=tem;
        }
    }
    return c;
}
//------------------------------------------
float** transport(float**a,int x,int y)                         //矩阵转置
{
    float**zhuanzhi;
    int i,j;
    zhuanzhi=mal(y,x);
    for(i=0;i<y;i++)
    {
        for(j=0;j<x;j++)
        {
            zhuanzhi[i][j]=a[j][i];
        }
    }
    return zhuanzhi;
}
