#include <iostream>
#include <unordered_map>

//最长无重复子串问题
//动态规划，以str[i]结尾的子字符串的最长无重复字串
//最差时间复杂度O(N^2)
static int func(std::string str){
    int length = str.size();
    int *dp = new int[length]{1};
    for(int i=1; i<length; i++){
        int n = 1;
        for(; n<=dp[i-1]; n++){
            if(str[i-n] == str[i]){
                break;
            }
        }
        dp[i] = n;
    }
    //打印dp数组出来看看
    for(int i=0; i<length; i++){
        std::cout << dp[i] << "\t";
    }   std::cout << std::endl;
    //返回dp数组中最大值
    int maxLength = 0;
    for(int i=0; i<length; i++){
        maxLength = dp[i]>maxLength ? dp[i] : maxLength;
    }
    delete[] dp;
    dp = nullptr;
    return maxLength;
}

// 尝试使用哈希表将时间复杂度降到O(N)
static int func2(std::string str){
    int length = str.size();
    int *dp = new int[length]{1};
    // 哈希表保存字母str[i]最后一次出现的索引
    std::unordered_map<char, int> hash;
    hash[str[0]] = 0;
    int maxLength = 1;
    for(int i=1; i<length; i++){
        if(hash.count(str[i]) == 0){
            dp[i] = dp[i-1] + 1;
        }else{
            dp[i] = std::min(i - hash[str[i]], dp[i-1] + 1);
        }
        hash[str[i]] = i;
        maxLength = dp[i] > maxLength ? dp[i] : maxLength;
    }
    delete[] dp;
    dp = nullptr;
    return maxLength;
}

int main(int argc, char const *argv[]){
    std::string str("abcedefghi");
    std::cout << func(str) << std::endl;
    std::cout << func2(str) << std::endl;
    return 0;
}