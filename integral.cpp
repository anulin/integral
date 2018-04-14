#include <iostream>
#include <stdio.h>
#include<thread>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;



double integr(double a, double b, double *rs)
{
    /*if (b-a>0.001)
    {
        *rs=integr(a,(a+b)/2,rs)+integr((a+b)/2,b,rs);
        return (*rs);
    }
    else
    {
        *rs=(b-a) *((a+b)/2)*((a+b)/2);
        return(*rs);
    }*/
    double c;
    for(c=a+0,001;a+c<b;c+=0,001)
    {
        *rs+=0,001*((a+c)/2)*((a+c)/2);
    }
    *rs+=(b-c)*((c+b)/2)*((c+b)/2);
    return(*rs);
}
int main(int argc, char** argv)
{
    int a1 = atoi(argv[2]);
    int b1 = atoi(argv[3]);
    int number=atoi(argv[1]);
    double a, b;
    a=a1;
    b=b1;
    vector<thread> thr;
    vector<double> cc(number);
    int i;

    for(i=0;i<number;i++)
    {
        //cc.push_back(0);
        thr.push_back( thread(integr, (i)*(b-a)/number+a, (i+1)*(b-a)/number+a, &cc[i]));
    }
    for(i=0;i<number;i++)
    {
        thr[i].join();
    }
    a=0;
    for(i=0;i<number;i++)
    {
        a+=cc[i];
    }
    cout << a;
    return 0;
}
