#include <stdio.h>

// enum DAY
// {
//     MON = 1,
//     TUE,
//     WED,
//     THU, 
//     FRI, 
//     SAT, 
//     SUN
// };



int main(){
    enum DAY
    {
        MON = 1,
        TUE,
        WED,
        THU, 
        FRI, 
        SAT, 
        SUN
    };
    printf("%d\n", MON);
    printf("%d\n", TUE);
    printf("%d\n", WED);
    printf("%d\n", THU);
    printf("%d\n", FRI);
    printf("%d\n", SAT);
    printf("%d\n", SUN);

    // enum DAY day; //定义一个DAY类型变量day
    // int a = 1000;
    // day = a;
    // printf("%d\n", day);

    int a = 100;
    enum DAY weekend;
    weekend = ( enum DAY ) a;  //类型转换
    weekend = a; //错误
    printf("weekend:%d",weekend);
    return 0;
}