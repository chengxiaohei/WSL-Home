#include <iostream>
#include <string>
#include <limits>

int ERRNO = 0; // -1 -> 输入数据格式错误; -2 -> 数值溢出

int strToInt(std::string str){
    ERRNO = 0;
    int length = str.size();
    //数据格式正确性检查
    if(length < 1){
        ERRNO = -1;
        return -1;
    }
    int flag = 0; // 0表示字符穿第一个字符不是符号，1表示正号，-1表示负号
    for(int i=0; i<length; i++){
        if(i == 0 && (str[i]=='+' || str[i]=='-')){
            if(length == 1){
                ERRNO = -1;
                return -1;
            }
            flag = str[i] == '+' ? 1 : -1;
            continue;
        }
        if(str[i] < '0' || str[i] > '9'){
            ERRNO = -1;
            return -1;
        }
    }
    long long result = 0;
    if(flag == 0){
        long long mul = 1;
        for(int i=length-1; i>=0; i--){
            result += (str[i]-'0') * mul;
            mul *= 10;
        }
    }else{
        long long mul = 1;
        for(int i=length-1; i>0; i--){
            result += (str[i]-'0') * mul;
            mul *= 10;
        }
        result *= flag;
    }
    // 检查数据溢出
    if(result >0x7FFFFFFF  || result < (signed int)0x80000000){
        ERRNO = -2;
        return -1;
    }
    return (int)result;
}

int main(int argc, char const *argv[]){
    std::string str = "-79587439857934";
    int result = strToInt(str);
    if(result == -1){
        if(ERRNO == -1){
            printf("%s\n","输入数据格式错误");
            return -1;
        }else if(ERRNO == -2){
            printf("%s\n","数据溢出");
            return -1;
        }
    }
    printf("%d\n", result);
    return 0;
}