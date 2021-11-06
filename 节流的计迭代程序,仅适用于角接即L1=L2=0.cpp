#include <stdio.h>
#include<math.h>

#define D 0.2335658//直径
#define pi acos(-1)//π
#define rou 862.7979//密度
#define miu 0.00012988//粘度
#define qmcom 111.111//质量流量qmcom
#define pcom 256000//压强pcom

double lei()//计算雷诺数
{
    double Re=4*qmcom/(pi*miu*D);
    return Re;
}

double demi()//计算面积A2
{
    double S=4*qmcom/(pi*D*D*sqrt(2 * pcom*rou));
    return S;
}

double beita(double cei)//计算beita
{
    double S=demi();
    double beita;
    return beita=pow(1+pow((cei/S),2),-0.25);
}

double cei(double beita)//计算C
{
    double cei;
    return cei=0.5961+0.0261 *pow(beita,2)-0.216*pow(beita,8)+0.000521*pow(pow(10,6)*beita/lei(),0.7)+(0.0188+0.0063*pow((19000*beita/lei()),0.8))*pow(beita,3.5)*pow(pow(10, 6)/lei(),0.3);
}

double recalculate(double key,int n)//迭代公式
{
    double bei,bei_de,c;//bei_de保存上一次的beita计算结果
    bei=beita(key);
    c=cei(bei);
    for(int i=0;i<n;i++)
    {
        bei_de=bei;
        bei=beita(c);
        c=cei(bei);
        if(fabs(bei-bei_de)<0.0001)
        return c;
    }
    return 0;
}

int main()
{
    double key;
    int n;

    printf("请设定C的初始值\n");
    scanf("%lf",&key);
    printf("请输入允许的迭代次数\n");
    scanf("%d",&n);

    if(n<=0)
    return printf("错误，迭代次数必须为正整数!");
    if(recalculate(key,n))
    return printf("当C0的初始值为%lf时,迭代收敛!\n确定C等于%lf,beita等于%lf",key,recalculate(key,n),beita(recalculate(key,n)));
    else
    return printf("当C0的初始值为%lf时,迭代发散!",key);
}
