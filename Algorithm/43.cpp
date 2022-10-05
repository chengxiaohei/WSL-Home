#include <iostream>
#include <string.h>
#include <math.h>

// number为骰子总数,在n个骰子,目前已有点数和为already,往cache数组中写入值
void process(int number, int n, int already, int *cache){
    if(n < 1)
        return;
    if(n == 1){
        for(int i=1; i<=6; i++){
            cache[already + i - number]++;
        }
        return;
    }
    for(int i=1; i<=6; i++){
        process(number, n - 1, already + i, cache);
    }
    return;
}

//打印n个骰子和为s的概率
void prob(int n, int s){
    if(n < 1 || s > 6 * n || s < n){
        printf("%.20lf\n", 0.0f);
        return;
    }
    //申请一个数组用于保存每种和出现的次数
    int *data = new int[6*n-n+1];
    memset(data, 0, (6*n-n+1)*4);
    process(n, n, 0, data);
    printf("%.20lf\n", data[s-n] / std::pow(6,n));
    delete[] data;
}

// //动态规划
// void prob(int n, int s){

// }

int main(int argc, char const *argv[]){
    prob(11, 50);
    return 0;
}