#include <iostream>
#include <string>

//贪心算法
int putLight(std::string& str){
    int length = str.size();
    int light = 0;
    int index = 0;
    // 当你来到index位置，一定要保证之前的灯，彻底不会影响到index位置。
    while(index < length){
        if(str[index] == 'X'){
            index++;
        }else{  //str[index] == '.'
            light++;
            if(index == length - 1){
                break;
            }
            if(str[index+1] == 'X'){
                index += 2;
            }else{ //str[index+1] == '.'
                index += 3;
            }
        }
    }
    return light;
}

int main(int argc, char const *argv[]){
    std::string str("...");
    std::cout << putLight(str) << std::endl;
    return 0;
}