#include <iostream>
#include <string>

bool isCorrect(std::string& str){
    int count = 0;
    for(int i=0; i<str.size(); i++){
        if(count < 0) return false;
        if(str[i] == '('){
            count++;
        }else{
            count--;
        }
    }
    return count == 0;
}

//左程云的做法
int addNtoCorrect(std::string& str){
    int count = 0;
    int ans = 0;
    for(int i=0; i<str.size(); i++){
        if(str[i] == '('){
            count++;
        }else{ //str[i] == ')'
            if(count == 0){
                ans++;
            }else{
                count--;
            }
        }
    }
    return count + ans;
}

//我的做法，我觉得思路更清晰，
int addNtoCorrect2(std::string& str){
    int count = 0;
    int ans = 0;
    for(int i=0; i<str.size(); i++){
        if(count < 0){
            ans++;
            count++;
        }
        if(str[i] == '('){
            count++;
        }else{ //str[i] == ')'
            count--;
        }
    }
    return ans + count;
}

int main(int argc, char const *argv[]){
    std::string str("))()())((((");
    std::cout << std::boolalpha << "完整括号对:" << isCorrect(str) << std::endl;
    std::cout  << "添加:" << addNtoCorrect(str) << std::endl;
    std::cout  << "添加:" << addNtoCorrect2(str) << std::endl;
}