#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

std::string num2str(long num){
    long init = 1;  //init 变化范围: 26^0 -> 26^1 -> 26^2 -> 26^3 -> 26^2 -> 26^1 -> 26^0;
    int len = 0;  //len表示需要多少个位，来表示该伪26进制数
    while(num >= init){
        num -= init;
        init *= 26;
        len++;
    }
    std::vector<int> data(len, 1);
    std::string result;
    init /= 26;
    for(int i=0; i<len; i++){
        data[i] += num / init;
        num %= init;
        init /= 26;
        result.push_back(data[i] + 'A' -1);
    }
    return result;
}

long str2num(std::string str){
    int length = str.size();
    if(length == 0){
        return 0;
    }
    long result = 0;
    long init = 1;
    for(int i=length-1; i>=0; i--){
        result += (str[i]- 'A' + 1) * init;
        init *= 26;
    }
    return result;
}

int main(int argc, char const *argv[]){
    std::string str;
    for(int i=0; i<5000; i++){
        int len = rand()%10;
        for(int j=0; j<len; j++){
            str.push_back(rand()%26 + 'A');
        }
        long n = str2num(str);
        std::string res = num2str(n);
        if(res != str){
            std::cout << "error!" << std::endl;
            return -1;
        }
        str.clear();
    }
    std::cout << "seccess!" << std::endl;
    return 0;
}