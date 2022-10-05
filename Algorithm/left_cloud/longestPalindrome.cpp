#include <iostream>
#include <string>
//最长回文字串

//判断str[i]~str[j]是否是回文字符串
bool process(std::string& str, int i, int j){
    if(str.size() == 0){
        return false;
    }
    if(str.size() == 1){
        return true;
    }
    if(str[i] != str[j]){
        return false;
    }
    if(i == j){
        return true;
    }else if(j - i == 1){
        
    }
}

int longestPalindrome(std::string str){
    
}

int main(){
    std::string str("fhioeshaogij");
    std::cout << longestPalindrome(str) << std::endl;
    return 0;
}