//自己实现一个求幂的函数

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cmath>

double powWithUnsignedExponent(double base, unsigned int exponent){
    if(exponent == 0)
        return 1;
    if(exponent == 1)
        return base;
    double result = powWithUnsignedExponent(base, exponent >> 1);
    result *= result;
    if(exponent & 0x1 == 1){
        result *= base;
    }
    return result;
}

bool equall(double a, double b){
    if((a - b > -0.0000001) && (a - b < 0.0000001)){
        return true;
    }
    else{
        return false;
    }
}

double mypow0(double base, int exponent){
    if(equall(base, 0.0)){
        return 0.0;
    }
    if(exponent == 0)
        return 1;
    double result;
    if(exponent < 0){
        result = powWithUnsignedExponent(base, (unsigned int)(-exponent));
        result = 1.0 / result;
    }
    else
        result = powWithUnsignedExponent(base, exponent);
    return result;
}


double mypow1(int base, int pow){
    if(pow == 0) return 1;
    if(base == 0) return 0;
    double res = 1;
    if(pow > 0){
        while(pow != 0){
            if(pow & 1 != 0){
                res *= base;
            }
            base *= base;
            pow >>= 1;
        }
    }else{ //pow < 0
        pow = -pow;
        while(pow != 0){
            if(pow & 1 != 0){
                res *= base;
            }
            base *= base;
            pow >>= 1;
        }
        res = 1 / res;
    }
    return res;
}

double mypow2(int base, int pow){
    if(pow == 0) return 1;
    // if(base == 0) return 0;  //这句话不需要,因为0^-1结果是inf,而不是0
    double res = 1;
    int temp = pow > 0 ? pow : -pow;
    while(temp != 0){
        if(temp & 1 != 0){
            res *= base;
        }
        base *= base;
        temp >>= 1;
    }
    return pow > 0 ? res : 1/res;
}




int main(){
    srand(time(0));
    for(int i=0; i<200; i++){
        int base = rand() % 10;
        int pow = (1) * rand() % 5;
        double result1 = mypow2(base, pow);
        double result2 = std::pow(base, pow);
        if(result1 != result2){
            std::cout << "error:" << base << "^" << pow << "=" << result1 << "\t";
            std::cout << "stand output:" << result2 << std::endl;
        }
    }
    return 0;
}